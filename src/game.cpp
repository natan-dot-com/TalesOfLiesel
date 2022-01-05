#include <./lib/Game.h>
#include <iostream>

Game::Game(QWidget *parent) : QObject(parent){
    this->currFloor = 1;
    this->playerInstance = new Liesel();
    this->currEnemyInstance = new Enemy();

    this->clickExec = new ThreadInstance();
    this->fireballExec = new ThreadInstance();
    this->destAuraExec = new ThreadInstance();
    this->destAuraDmg = new ThreadInstance();
}

Game::~Game() {
    delete this->playerInstance;
    delete this->currEnemyInstance;
    delete this->clickExec;
}

// Proccess and refresh the monster HP bar after an attack.
// - Also immediately evoke a new enemy if the current one is dead after the attack.
// - Returns bool indicating whether the current enemy is dead ('true') or not ('false').
bool Game::proccessMonsterDamage(const int dealtDamage, int &gainedExp, int &gainedCoins, bool &isLevelUp) {
    if (currEnemyInstance->inflictDamage(dealtDamage)) {
        gainedExp = this->currEnemyInstance->dropExpOnDeath();
        gainedCoins = this->currEnemyInstance->dropCoinsOnDeath();

        // Spawn new enemy
        Enemy *newEnemy = new Enemy(currFloor);
        delete this->currEnemyInstance;
        this->currEnemyInstance = newEnemy;

        this->playerInstance->updateGainedCoins(gainedCoins);
        isLevelUp = this->playerInstance->updateExp(gainedExp);
        return true;
    }
    return false;
}

// Start the current skill cooldown on its representative thread
// - Toggles the usage indicator of the predetermined thread (as 'cooldownThread')
// - Sleeps thread for 'timeAmount' seconds/milisseconds, depending of the used 'MODE'.
void Game::startCooldown(ThreadInstance *cooldownThread, const int timeAmount) {
    cooldownThread->toggleUsage();
    if (timeAmount > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeAmount));
    }
    cooldownThread->toggleUsage();
}

// Proccess damage on click.
// - Cooldown between clicks: 0.5s (500ms) on 'clickExec' thread.
// - Returns all the details from the current action, such as the damage dealt,
// 	 the experience gained, if the player leveled up.
void Game::evokeDamageOnClick() {
    if (!this->clickExec->isInUse()) {

        // Re the functionality of previously used thread
        if (this->clickExec->currThread.joinable()) {
            this->clickExec->currThread.join();
        }

        // Proccess click damage system
        const int dealtDamage = this->playerInstance->generateDamageOnClick();
        int gainedExp = 0;
        int gainedCoins = 0;
        bool isLevelUp = false;

        // Proccess rewards and a new enemy if the current one dies
        {
            const std::lock_guard<std::mutex> lock(healthBarMut);
            this->proccessMonsterDamage(dealtDamage, gainedExp, gainedCoins, isLevelUp);
            //Game::updateEventFeed(dealtDamage, gainedExp, gainedCoins, isLevelUp);
            //Game::gameUpdate();
        }

        // Cooldown: 0.5s delay for each damage dealt
        this->clickExec->currThread = std::thread(&Game::startCooldown, this, this->clickExec, CD_CLICK_MILIS);
    }

    emit updateHealthBar(this->currEnemyInstance->getCurrHP(), this->currEnemyInstance->getMaxHP());
}

// Casts a fireball, dealing extra damage.
// - Cooldown between fireball casts: 10s on 'fireballExec' thread.
// - Returns all the details from the current action, such as the damage dealt,
// 	 the experience gained, if the player leveled up.
void Game::evokeFireball() {
    if (!this->fireballExec->isInUse()) {

        // Re the functionality of previously used thread
        if (this->fireballExec->currThread.joinable()) {
            this->fireballExec->currThread.join();
        }

        // Proccess fireball damage system
        const int dealtDamage = this->playerInstance->fireSkill.skillEffect();
        int gainedExp = 0;
        int gainedCoins = 0;
        bool isLevelUp = false;

        // Proccess rewards and a new enemy if the current one dies
        {
            const std::lock_guard<std::mutex> lock(healthBarMut);
            this->proccessMonsterDamage(dealtDamage, gainedExp, gainedCoins, isLevelUp);
            // Game::updateEventFeed(dealtDamage, gainedExp, gainedCoins, isLevelUp);
            // Game::gameUpdate();
        }

        // Cooldown: 10s
        this->fireballExec->currThread = std::thread(&Game::startCooldown, this, this->fireballExec, CD_FIREBALL_MILIS);
    }

    emit updateHealthBar(this->currEnemyInstance->getCurrHP(), this->currEnemyInstance->getMaxHP());
}

// Auxiliary function which proccess the total damage dealt in 'destAuraDmg' thread.
// PROBLEM: referencing variables inside a thread call (think how to fix it)
void Game::damageDestructionAura() {
    int damageCounter = 0;

    this->destAuraDmg->toggleUsage();

    // Each second, a damage tick occurs. Max damage goes around 'DESTAURA_DOT_TICKS' ticks.
    while(damageCounter < DESTAURA_DOT_TICKS) {
        // Proccess destruction aura DoT-based damage system
        const int dealtDamage = this->playerInstance->destructionSkill.getCurrDoT();
        int gainedExp = 0;
        int gainedCoins = 0;
        bool isLevelUp = false;

        // Process rewards and a new enemy if the current one dies
        {
            const std::lock_guard<std::mutex> lock(healthBarMut);
            this->proccessMonsterDamage(dealtDamage, gainedExp, gainedCoins, isLevelUp);
            emit updateHealthBar(this->currEnemyInstance->getCurrHP(), this->currEnemyInstance->getMaxHP());
            // Game::updateEventFeed(dealtDamage, gainedExp, gainedCoins, isLevelUp);
            // Game::gameUpdate();
        }
        damageCounter++;

        // Delay between ticks (1 second)
        std::this_thread::sleep_for(std::chrono::seconds(DELAY_DESTAURA_DOT_SECS));
    }
    this->destAuraDmg->toggleUsage();
}

// Casts destruction aura, dealing its equivalente DoT damage over 'DESTAURA_DOT_TICKS' ticks.
// - Cooldown between destruction aura casts: 15s on 'destAuraExec' thread.
// - Cooldown between destruction aura damage ticks: 1s on 'destAuraDmg' thread.
// - Returns all the details from the current action, such as the damage dealt,
// 	 the experience gained, if the player leveled up.
void Game::evokeDestructionAura() {
    if (!this->destAuraExec->isInUse()) {
        // Re the functionality of previously used thread (destruction aura damage thread)
        if (this->destAuraDmg->currThread.joinable()) {
            this->destAuraDmg->currThread.join();
        }
        if (!this->destAuraDmg->isInUse()) {
            this->destAuraDmg->currThread = std::thread(&Game::damageDestructionAura, this);
        }

        // Re the functionality of previously used thread (destruction aura cooldown thread)
        if (this->destAuraExec->currThread.joinable()) {
            this->destAuraExec->currThread.join();
        }
        // Cooldown: 20s
        this->destAuraExec->currThread = std::thread(&Game::startCooldown, this, this->destAuraExec, CD_DESTAURA_MILIS);
    }
}

void Game::generateEnemy(QString *name) {
    emit spawnEnemy(name);
}

void Game::onDefaultDamage(int current, int max) {
    emit defaultDamage(current, max);
}

void Game::onFireballDamage(int current, int max) {
    emit fireballDamage(current, max);
}

void Game::onDestructionAuraDamage(int current, int max) {
    emit destructionAuraDamage(current, max);
}
