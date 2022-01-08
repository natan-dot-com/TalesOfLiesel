#ifndef _SKILLS_H_
#define _SKILLS_H_

#include "./lib/backend/rng.h"
#include <cmath>
#include <thread>

// Base class for an in-game skill
class Skill : public Rng {
private:
	int skillLevel;
	int skillExp;

public:
	Skill();
    int getLevel(); // How much time it was updated
    int getExp(); // How much coins were invested until now
    int getLevelUp(); // How much coins it's needed to upgrade the ability
	bool updateExp(int gainedExp);
	virtual double skillEffect() = 0;
};

class Fireball : public Skill {
public:
	double skillEffect();
};

class DestructionAura : public Skill {
private:
	double skillEffect();
	double currDoT;
	
public:
	bool updateExp(int gainedExp);
	double getCurrDoT();
};

#endif
