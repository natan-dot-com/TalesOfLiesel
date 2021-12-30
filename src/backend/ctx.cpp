#include "./lib/backend/ctx.h"

#define MODE_SECS -10
#define MODE_MILIS -20

// Main constructor for context class
Context::Context() {
	currFloor = 1;

	playerInstance =  new Liesel();
	currEnemyInstance =  new Enemy(currFloor);
	errHandler = new Error();

	fireballExec = new ThreadInstance();
	clickExec = new ThreadInstance();
	destAuraExec = new ThreadInstance();
	destAuraDmg = new ThreadInstance();
}

// Start the current skill cooldown on its representative thread
// - Toggles the usage indicator of the predetermined thread (as 'cooldownThread')
// - Sleeps thread for 'timeAmount' seconds/milisseconds, depending of the used 'MODE'.
void Context::startCooldown(ThreadInstance *cooldownThread, const int timeAmount, const int MODE) {
	if (timeAmount > 0) {
		cooldownThread->toggleUsage();
		switch (MODE) {
			case MODE_SECS:
				std::this_thread::sleep_for(std::chrono::seconds(timeAmount));
				break;

			case MODE_MILIS:
				std::this_thread::sleep_for(std::chrono::milliseconds(timeAmount));
				break;
		}
		cooldownThread->toggleUsage();
	}
}

// Proccess and refresh the monster HP bar after an attack.
// - Also immediately evoke a new enemy if the current one is dead after the attack.
// - Returns bool indicating whether the current enemy is dead ('true') or not ('false').
bool Context::proccessMonsterDamage(const int dealtDamage, int &gainedExp, int &gainedCoins, bool &isLevelUp) {
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

// Proccess damage on click.
// - Cooldown between clicks: 0.5s (500ms) on 'clickExec' thread.
// - Returns all the details from the current action, such as the damage dealt,
// 	 the experience gained, if the player leveled up.
TurnResults *Context::evokeDamageOnClick() {
	if (!this->clickExec->isInUse()) {

		// Reset the functionality of previously used thread
		if (this->clickExec->currThread.joinable()) {
			this->clickExec->currThread.join();
		}

		// Proccess click damage system
		const int dealtDamage = this->playerInstance->generateDamageOnClick();
		int gainedExp = 0;
		int gainedCoins = 0;
		bool isLevelUp = false;

		// Proccess rewards and a new enemy if the current one dies
		this->proccessMonsterDamage(dealtDamage, gainedExp, gainedCoins, isLevelUp);

		// Cooldown: 0.5s delay for each damage dealt
		this->clickExec->currThread = std::thread(&Context::startCooldown, this, this->clickExec, CD_CLICK_MILIS, MODE_MILIS);

		return new TurnResults(dealtDamage, gainedExp, gainedCoins, isLevelUp);
	}
	return NULL;
}

// Casts a fireball, dealing extra damage.
// - Cooldown between fireball casts: 10s on 'fireballExec' thread.
// - Returns all the details from the current action, such as the damage dealt,
// 	 the experience gained, if the player leveled up.
TurnResults *Context::evokeFireball() {
	if (!this->fireballExec->isInUse()) {

		// Reset the functionality of previously used thread
		if (this->fireballExec->currThread.joinable()) {
			this->fireballExec->currThread.join();
		}

		// Proccess fireball damage system
		const int dealtDamage = this->playerInstance->fireSkill.skillEffect();
		int gainedExp = 0;
		int gainedCoins = 0;
		bool isLevelUp = false;

		// Proccess rewards and a new enemy if the current one dies
		this->proccessMonsterDamage(dealtDamage, gainedExp, gainedCoins, isLevelUp);

		// Cooldown: 10s
		this->fireballExec->currThread = std::thread(&Context::startCooldown, this, this->fireballExec, CD_FIREBALL_SECS, MODE_SECS);

		return new TurnResults(dealtDamage, gainedExp, gainedCoins, isLevelUp);
	}
	return NULL;
}

// Auxiliary function which proccess the total damage dealt in 'destAuraDmg' thread.
// PROBLEM: referencing variables inside a thread call (think how to fix it)
void Context::damageDestructionAura(const int dealtDamage, int &gainedExp, int &gainedCoins, bool &isLevelUp) {
	int damageCounter = 0;

	this->destAuraDmg->toggleUsage();

	// Each second, a damage tick occurs. Max damage goes around 'DESTAURA_DOT_TICKS' ticks.
	while(damageCounter < DESTAURA_DOT_TICKS) {

		// Process rewards and a new enemy if the current one dies
		this->proccessMonsterDamage(dealtDamage, gainedExp, gainedCoins, isLevelUp);
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
TurnResults *Context::evokeDestructionAura() {
	if (!this->destAuraExec->isInUse()) {

		// Proccess destruction aura DoT-based damage system
		const int dealtDamage = this->playerInstance->destructionSkill.getCurrDoT();
		int gainedExp = 0;
		int gainedCoins = 0;
		bool isLevelUp = false;

		// Reset the functionality of previously used thread (destruction aura damage thread)
		if (this->destAuraDmg->currThread.joinable()) {
			this->destAuraDmg->currThread.join();
		}
		if (!this->destAuraDmg->isInUse()) {
			this->destAuraDmg->currThread = std::thread(&Context::damageDestructionAura, this, 
					dealtDamage, std::ref(gainedExp), std::ref(gainedCoins), std::ref(isLevelUp));	
		}

		// Reset the functionality of previously used thread (destruction aura cooldown thread)
		if (this->destAuraExec->currThread.joinable()) {
			this->destAuraExec->currThread.join();
		}
		// Cooldown: 15s
		this->destAuraExec->currThread = std::thread(&Context::startCooldown, this, this->destAuraExec, CD_FIREBALL_SECS, MODE_SECS);

		return new TurnResults(dealtDamage, gainedExp, gainedCoins, isLevelUp);
	}
	return NULL;
}

// Upgrade skills methods
bool Context::updateFireball() {
	const int currSoulCoins = this->playerInstance->getSoulCoins();
	this->playerInstance->updateSpentCoins(currSoulCoins);
	return this->playerInstance->fireSkill.updateExp(currSoulCoins);
}

bool Context::updateChronomancy() {
	const int currSoulCoins = this->playerInstance->getSoulCoins();
	this->playerInstance->updateSpentCoins(currSoulCoins);
	return this->playerInstance->chronoSkill.updateExp(currSoulCoins);
}

bool Context::updateDestructionAura() {
	const int currSoulCoins = this->playerInstance->getSoulCoins();
	this->playerInstance->updateSpentCoins(currSoulCoins);
	return this->playerInstance->destructionSkill.updateExp(currSoulCoins);
}

// Current floor management methods
void Context::nextFloor() {
	this->currFloor++;
	delete this->currEnemyInstance;
	this->currEnemyInstance = new Enemy(currFloor);
}

void Context::previousFloor() {
	if (this->currFloor > 1) {
		this->currFloor--;
		delete this->currEnemyInstance;
		this->currEnemyInstance = new Enemy(currFloor);
	}
}

int Context::getCurrentFloor() {
	return this->currFloor;
}
