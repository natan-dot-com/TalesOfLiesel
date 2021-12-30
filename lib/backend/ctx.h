#ifndef _CTX_H_
#define _CTX_H_

#include "./lib/backend/liesel.h"
#include "./lib/backend/enemy.h"
#include "./lib/backend/error_handling.h"
#include <thread>
#include <chrono>
#include <atomic>

#include <iostream>

#define CD_CLICK_MILIS 500
#define CD_FIREBALL_SECS 10
#define CD_DESTAURA_SECS 15
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

	void printResults() {
		std::cout << "Damage: " << this->damageDealt << '\n'
  		   		  << "Exp: " << this->gainedExp << '\n'
		 		  << "Coins: " << this->gainedCoins << '\n'
		 		  << "Level Up: " << this->isLevelUp << '\n';
	}
} TurnResults;

typedef struct _ThreadInstance {
	std::thread currThread;
	std::atomic<bool> executionFlag;

	_ThreadInstance() {
		this->executionFlag = false;
	}

	void toggleUsage() {
		this->executionFlag = !this->executionFlag;
	}

	bool isInUse() {
		return this->executionFlag;
	}
} ThreadInstance;

class Context {
private:
	ThreadInstance *fireballExec;
	ThreadInstance *clickExec;
	ThreadInstance *destAuraExec;
	ThreadInstance *destAuraDmg;

	int currFloor;

	void startCooldown(ThreadInstance *cooldownThread, int timeAmount, const int MODE);
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