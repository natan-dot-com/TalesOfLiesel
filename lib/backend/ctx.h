#ifndef _CTX_H_
#define _CTX_H_

#include "./lib/backend/liesel.h"
#include "./lib/backend/enemy.h"
#include "./lib/backend/error_handling.h"
#include <thread>
#include <chrono>

typedef struct _turnResult {
	int expGained;
	int damageDealt;
	int coinsGained;
	bool isLevelUp;
} TurnResult;

typedef std::pair<TurnResult, bool> pairResult;

class Context {
private:
	Liesel *playerInstance;
	Enemy *currEnemyInstance;
	Error *errHandler;

	std::thread fireballExec;
	std::thread chronoExec;
	std::thread destAuraExec;

	void damageFireball(TurnResult &currResult, bool &isError);

public:
	Context();

	// Read/write save file methods
	Context(std::string loadFile);
	bool saveGame(std::string targetFilename);

	// Damage/skills related methods
	pairResult damageOnClick();
	pairResult evokeFireball();

	// Skills management
	bool updateFireball();
	bool updateChronomancy();
	bool updateDestructionAura();
};

#endif