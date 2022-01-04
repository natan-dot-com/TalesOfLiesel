#ifndef _CTX_H_
#define _CTX_H_

#include "./lib/backend/liesel.h"
#include "./lib/backend/enemy.h"
#include "./lib/backend/error_handling.h"
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>

#include <iostream>

#define FIREBALL_THREAD_ID 1001
#define DESTAURA_THREAD_ID 1002

#define CD_CLICK_MILIS 500
#define CD_FIREBALL_SECS 10
#define CD_DESTAURA_SECS 20
#define DELAY_DESTAURA_DOT_SECS 1

#define DESTAURA_DOT_TICKS 6

typedef struct _TurnResults {
	int damageDealt;
	int gainedExp;
	int gainedCoins;
	bool isLevelUp;

	_TurnResults(int _damageDealt, int _gainedExp, int _gainedCoins, bool _isLevelUp) {
		this->damageDealt = _damageDealt;
		this->gainedExp = _gainedExp;
		this->gainedCoins = _gainedCoins;
		this->isLevelUp = _isLevelUp;
	}
} TurnResults;

typedef struct _ThreadInstance {
	std::thread currThread;
	std::atomic<bool> executionFlag;
	int maxCooldown;
	int cooldownProgress;
    int threadID;

    _ThreadInstance(int _cooldownProgress = 0, int threadID = -1) {
		this->executionFlag = false;
		this->cooldownProgress = _cooldownProgress;
		this->maxCooldown = _cooldownProgress;
		this->threadID = threadID;
	}

	void toggleUsage() {
		this->executionFlag = !this->executionFlag;
	}

	bool isInUse() {
		return this->executionFlag;
	}

	void decreaseCooldown() {
		if (this->cooldownProgress == 0) {
			this->cooldownProgress = this->maxCooldown;
		}
		else {
			this->cooldownProgress--;
		}
	}
} ThreadInstance;

class Context {
private:
	ThreadInstance *fireballExec;
	ThreadInstance *clickExec;
	ThreadInstance *destAuraExec;
	ThreadInstance *destAuraDmg;

	std::mutex healthBarMut;
	int currFloor;

	void startCooldown(ThreadInstance *cooldownThread);
	void clickCooldown();
	bool proccessMonsterDamage(const int dealtDamage, int &gainedExp, int &gainedCoins, bool &isLevelUp);
	void damageDestructionAura(const int dealtDamage, int &gainedExp, int &gainedCoins, bool &isLevelUp);

public:
	Liesel *playerInstance;
	Enemy *currEnemyInstance;
	Error *errHandler;

	Context();

	// Read/write save file methods
	Context(std::string loadFile);
	bool saveGame(std::string targetFilename);

	// Damage/skills related methods
	TurnResults *evokeDamageOnClick();
	TurnResults *evokeFireball();
	TurnResults *evokeDestructionAura();

	// Skills management
	bool updateFireball();
	bool updateChronomancy();
	bool updateDestructionAura();

	// Floor management
	void nextFloor();
	void previousFloor();
	int getCurrentFloor();
};

#endif
