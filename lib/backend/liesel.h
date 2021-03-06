#ifndef _LIESEL_H_
#define _LIESEL_H_

#include "./lib/backend/rng.h"
#include "./lib/backend/skills.h"
#include <mutex>

class Liesel : private Rng { 
private:
	// Main character stats
	int currExp;
	int currLevel;
	int soulCoinsAmount;

	std::mutex coinsMutex;

public:
	// Main character skills
	Fireball fireSkill;
	DestructionAura destructionSkill;
	
	Liesel();
	bool updateExp(int gainedExp);
	void updateGainedCoins(int gainedCoins);
	bool updateSpentCoins(int spentCoins);
	int getLevelUp();
	int getLevel();
	int getExp();
	int getSoulCoins();
	int generateDamageOnClick();
};

#endif
