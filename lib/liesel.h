#ifndef _LIESEL_H_
#define _LIESEL_H_

#include "./lib/rng.h"
#include "./lib/skills.h"

class Liesel : private Rng { 
private:
	// Main character stats
	int currExp;
	int currLevel;
	int soulCoinsAmount;

public:
	// Main character skills
	Fireball fireSkill;
	DestructionAura destructionSkill;
	Chronomancy chronoSkill;
	
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
