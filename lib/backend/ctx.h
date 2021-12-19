#ifndef _CTX_H_
#define _CTX_H_

#include "./lib/backend/liesel.h"
#include "./lib/backend/enemy.h"
#include "./lib/backend/error_handling.h"
#include <thread>
#include <chrono>
#include <atomic>

typedef struct _threadInstance {
	std::thread currThread;
	std::atomic<bool> executionFlag;
} ThreadInstance;

class Context {
private:
	ThreadInstance *fireballExec;
	ThreadInstance *clickExec;
	ThreadInstance *destAuraExec;

	int currFloor;

	void damageFireball();
	void damageDestructionAura();
	void damageOnClick();

public:
	Liesel *playerInstance;
	Enemy *currEnemyInstance;
	Error *errHandler;

	Context();

	// Read/write save file methods
	Context(std::string loadFile);
	bool saveGame(std::string targetFilename);

	// Damage/skills related methods
	void evokeDamageOnClick();
	void evokeFireball();
	void evokeDestructionAura();

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