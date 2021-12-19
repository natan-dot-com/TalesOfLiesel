#include "./lib/backend/ctx.h"

#include <iostream>

#define DOT_TICKS 6

Context::Context() {
	currFloor = 1;

	playerInstance =  new Liesel();
	currEnemyInstance =  new Enemy(currFloor);
	errHandler =  new Error();
	fireballExec = new ThreadInstance();
	clickExec = new ThreadInstance();
	destAuraExec = new ThreadInstance();

	fireballExec->executionFlag = false;
	clickExec->executionFlag = false;
	destAuraExec->executionFlag = false;
}

// Thread dependant: Deals damage to enemy based on player's level
void Context::damageOnClick() {
	int dealtDamage = playerInstance->generateDamageOnClick();

	// Process rewards and a new enemy if the current one dies
	if (currEnemyInstance->inflictDamage(dealtDamage)) {
		int gainedExp = currEnemyInstance->dropExpOnDeath();
		int gainedCoins = currEnemyInstance->dropCoinsOnDeath();

		Enemy *newEnemy = new Enemy(currFloor);
		delete currEnemyInstance;
		currEnemyInstance = newEnemy;

		playerInstance->updateGainedCoins(gainedCoins);
	}
	// 0.5s delay for each damage dealt
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	this->clickExec->executionFlag = false;
}

// Calls click damage thread
void Context::evokeDamageOnClick() {
	if (!this->clickExec->executionFlag) {
		if (this->clickExec->currThread.joinable()) {
			this->clickExec->currThread.join();
		}
		this->clickExec->executionFlag = true;
		this->clickExec->currThread = std::thread(&Context::damageOnClick, this);
	}
}

// Thread dependant: Casts an fireball at the enemy. Damage's dealt based on the current skill level
void Context::damageFireball() {
	int dealtDamage = playerInstance->fireSkill.skillEffect();
	if (dealtDamage != 0) {

		// Process rewards and a new enemy if the current one dies
		if (currEnemyInstance->inflictDamage(dealtDamage)) {
			int gainedExp = currEnemyInstance->dropExpOnDeath();
			int gainedCoins = currEnemyInstance->dropCoinsOnDeath();

			Enemy *newEnemy = new Enemy(currFloor);
			delete currEnemyInstance;
			currEnemyInstance = newEnemy;

			playerInstance->updateGainedCoins(gainedCoins);
		}

		// 10s cooldown for each cast
		std::this_thread::sleep_for(std::chrono::seconds(10));
	}
	this->fireballExec->executionFlag = false;
}

// Calls fireball thread
void Context::evokeFireball() {
	if (!this->fireballExec->executionFlag) {
		if (this->fireballExec->currThread.joinable()) {
			this->fireballExec->currThread.join();
		}
		if (playerInstance->fireSkill.getLevel() > 0) {
			this->fireballExec->executionFlag = true;
			this->fireballExec->currThread = std::thread(&Context::damageFireball, this);
		}
	}
}


// Thread dependant: Casts a DoT (Damage Over Time) aura which deals damage based on skill's current level 
void Context::damageDestructionAura() {
	int damageCounter = 0;

	// Each 2 seconds, a damage tick occurs. Max damage goes around DOT_TICKS ticks.
	while(damageCounter < DOT_TICKS) {

		// Process rewards and a new enemy if the current one dies
		if (currEnemyInstance->inflictDamage(playerInstance->destructionSkill.getCurrDoT())) {
			int gainedExp = currEnemyInstance->dropExpOnDeath();
			int gainedCoins = currEnemyInstance->dropCoinsOnDeath();

			Enemy *newEnemy = new Enemy(currFloor);
			delete currEnemyInstance;
			currEnemyInstance = newEnemy;

			playerInstance->updateGainedCoins(gainedCoins);
		}
		damageCounter++;
		// Delay between ticks (2 seconds)
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	// 15s cooldown for each cast
	std::this_thread::sleep_for(std::chrono::seconds(15));
	this->destAuraExec->executionFlag = false;
}

// Calls destruction aura thread
void Context::evokeDestructionAura() {
	if (!this->destAuraExec->executionFlag) {
		if (this->destAuraExec->currThread.joinable()) {
			this->destAuraExec->currThread.join();
		}
		if (playerInstance->destructionSkill.getLevel() > 0) {
			this->destAuraExec->executionFlag = true;
			this->destAuraExec->currThread = std::thread(&Context::damageDestructionAura, this);
		}
	}
}

// Upgrade skills methods
bool Context::updateFireball() {
	int currSoulCoins = playerInstance->getSoulCoins();
	playerInstance->updateSpentCoins(currSoulCoins);
	return playerInstance->fireSkill.updateExp(currSoulCoins);
}

bool Context::updateChronomancy() {
	int currSoulCoins = playerInstance->getSoulCoins();
	playerInstance->updateSpentCoins(currSoulCoins);
	return playerInstance->chronoSkill.updateExp(currSoulCoins);
}

bool Context::updateDestructionAura() {
	int currSoulCoins = playerInstance->getSoulCoins();
	playerInstance->updateSpentCoins(currSoulCoins);
	return playerInstance->destructionSkill.updateExp(currSoulCoins);
}

// Current floor management methods
void Context::nextFloor() {
	currFloor++;
	delete currEnemyInstance;
	currEnemyInstance = new Enemy(currFloor);
}

void Context::previousFloor() {
	if (currFloor > 1) {
		currFloor--;
		delete currEnemyInstance;
		currEnemyInstance = new Enemy(currFloor);
	}
}

int Context::getCurrentFloor() {
	return currFloor;
}