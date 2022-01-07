#include <./lib/game.h>
#include <QDebug>
#include <QString>
#include <./lib/backend/gamephrases.h>
#include <./lib/gamemacros.h>

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
    delete this->fireballExec;
    delete this->destAuraExec;
    delete this->destAuraDmg;
}

// Proccess and refresh the monster HP bar after an attack.
// - Also immediately evoke a new enemy if the current one is dead after the attack.
// - Returns bool indicating whether the current enemy is dead ('true') or not ('false').
bool Game::proccessMonsterDamage(const double dealtDamage, int &gainedExp, int &gainedCoins, bool &isLevelUp) {
    if (currEnemyInstance->inflictDamage(dealtDamage)) {
        gainedExp = this->currEnemyInstance->dropExpOnDeath();
        gainedCoins = this->currEnemyInstance->dropCoinsOnDeath();

        // Spawn new enemy
        Enemy *newEnemy = new Enemy(currFloor);
        delete this->currEnemyInstance;
        this->currEnemyInstance = newEnemy;

        // Signal to spawn a new enemy.
        emit EMIT_SPAWN_NEW_ENEMY;

        // Signal to post a event on the feed of a new enemy.
        emit EMIT_TEMPLATE_PHRASE(NEW_ENEMY_PHRASE);

        this->playerInstance->updateGainedCoins(gainedCoins);
        isLevelUp = this->playerInstance->updateExp(gainedExp);

        if (isLevelUp) {
            emit EMIT_TEMPLATE_PHRASE(LEVEL_UP_PHRASE);
        }

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
        const double dealtDamage = this->playerInstance->generateDamageOnClick();
        int gainedExp = 0;
        int gainedCoins = 0;
        bool isLevelUp = false;

        // Proccess rewards and a new enemy if the current one dies
        {
            const std::lock_guard<std::mutex> lock(healthBarMut);
            this->proccessMonsterDamage(dealtDamage, gainedExp, gainedCoins, isLevelUp);

            emit EMIT_UPDATE_LIESEL_INFO;
        }

        // Cooldown: 0.5s delay for each damage dealt
        this->clickExec->currThread = std::thread(&Game::startCooldown, this, this->clickExec, CD_CLICK_MILIS);
        emit EMIT_UPDATE_HEALTHBAR;

        GENERATE_TYPE_DAMAGE_EVENT("[CLICK] Damage: ");
        emit EMIT_CLICK_DAMAGE_FEED;
    }


}

// Casts a fireball, dealing extra damage.
// - Cooldown between fireball casts: 10s on 'fireballExec' thread.
// - Returns all the details from the current action, such as the damage dealt,
// 	 the experience gained, if the player leveled up.
void Game::evokeFireball() {
    if (!this->fireballExec->isInUse() and this->playerInstance->fireSkill.getLevel()) {

        // Re the functionality of previously used thread
        if (this->fireballExec->currThread.joinable()) {
            this->fireballExec->currThread.join();
        }

        // Proccess fireball damage system
        const double dealtDamage = this->playerInstance->fireSkill.skillEffect();
        int gainedExp = 0;
        int gainedCoins = 0;
        bool isLevelUp = false;

        // Proccess rewards and a new enemy if the current one dies
        {
            const std::lock_guard<std::mutex> lock(healthBarMut);
            this->proccessMonsterDamage(dealtDamage, gainedExp, gainedCoins, isLevelUp);

            emit EMIT_UPDATE_LIESEL_INFO;
        }

        // Cooldown: 10s
        this->fireballExec->currThread = std::thread(&Game::startCooldown, this, this->fireballExec, CD_FIREBALL_MILIS);

        GENERATE_TYPE_DAMAGE_EVENT("[FIREBALL] Damage: ");
        emit EMIT_CLICK_DAMAGE_FEED;

        emit updateHealthBar(this->currEnemyInstance->getCurrHP(), this->currEnemyInstance->getMaxHP());
    }


}

// Auxiliary function which proccess the total damage dealt in 'destAuraDmg' thread.
// PROBLEM: referencing variables inside a thread call (think how to fix it)
void Game::damageDestructionAura() {
    int damageCounter = 0;

    this->destAuraDmg->toggleUsage();

    // Each second, a damage tick occurs. Max damage goes around 'DESTAURA_DOT_TICKS' ticks.
    while(damageCounter < DESTAURA_DOT_TICKS) {
        // Proccess destruction aura DoT-based damage system
        const double dealtDamage = this->playerInstance->destructionSkill.getCurrDoT();
        int gainedExp = 0;
        int gainedCoins = 0;
        bool isLevelUp = false;

        // Process rewards and a new enemy if the current one dies
        {
            const std::lock_guard<std::mutex> lock(healthBarMut);
            this->proccessMonsterDamage(dealtDamage, gainedExp, gainedCoins, isLevelUp);

            emit EMIT_UPDATE_LIESEL_INFO;
            emit EMIT_UPDATE_HEALTHBAR;
            qDebug() << dealtDamage;
            GENERATE_TYPE_DAMAGE_EVENT("[DESTRUCTION AURA] Damage: ");
            emit EMIT_CLICK_DAMAGE_FEED;
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
    if (!this->destAuraExec->isInUse() and this->playerInstance->destructionSkill.getLevel()) {
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

// Upgrade skills methods
bool Game::updateFireball() {
    const int currSoulCoins = this->playerInstance->getSoulCoins();
    this->playerInstance->updateSpentCoins(currSoulCoins);
    bool result = this->playerInstance->fireSkill.updateExp(currSoulCoins);

    GENERATE_FIREBALL_INFO_LABELS;
    emit EMIT_UPDATE_FIREBALL_INFO(FIREBALL);
    emit EMIT_UPDATE_LIESEL_INFO;
    return result;
}

bool Game::updateChronomancy() {
    const int currSoulCoins = this->playerInstance->getSoulCoins();
    this->playerInstance->updateSpentCoins(currSoulCoins);
    return this->playerInstance->chronoSkill.updateExp(currSoulCoins);
}

bool Game::updateDestructionAura() {
    const int currSoulCoins = this->playerInstance->getSoulCoins();
    this->playerInstance->updateSpentCoins(currSoulCoins);

    bool result = this->playerInstance->destructionSkill.updateExp(currSoulCoins);

    GENERATE_DESTAURA_INFO_LABELS;
    emit EMIT_UPDATE_DESTAURA_INFO(DESTAURA);
    emit EMIT_UPDATE_LIESEL_INFO;
    return result;
}

// Current floor management methods
void Game::nextFloor() {
    this->currFloor++;
    delete this->currEnemyInstance;
    this->currEnemyInstance = new Enemy(currFloor);

    // Signal to spawn a new enemy.
    emit EMIT_SPAWN_NEW_ENEMY;
    emit EMIT_UPDATE_LIESEL_INFO;
    emit EMIT_UPDATE_HEALTHBAR;
}

void Game::previousFloor() {
    if (this->currFloor > 1) {
        this->currFloor--;
        delete this->currEnemyInstance;
        this->currEnemyInstance = new Enemy(currFloor);

        // Signal to spawn a new enemy.
        emit EMIT_SPAWN_NEW_ENEMY;
        emit EMIT_UPDATE_LIESEL_INFO;
        emit EMIT_UPDATE_HEALTHBAR;
    }
}

int Game::getCurrentFloor() {
    return this->currFloor;
}

void Game::generateEnemy(QString name) {
    emit spawnEnemy(name);
}
