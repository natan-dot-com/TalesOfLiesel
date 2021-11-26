#ifndef _SKILLS_H_
#define _SKILLS_H_

#include "rng.h"
#include <cmath>

// Base class for an in-game skill
class Skill : public Rng {
	protected:
		int skillLevel;
		int skillExp;

	public:
		Skill();
		int getLevel();
		int getExp();
		int getLevelUp();
		bool updateExp(int gainedExp);
		virtual double skillEffect() = 0;
		
};

class Fireball : public Skill {
	public:
		double skillEffect();
};

class Chronomancy : public Skill {
	public:
		double skillEffect();
};

class DestructionAura : public Skill {
	private:
		double skillEffect();

	protected:
		double currDoT;
	
	public:
		void updateExp(int gainedExp);
		double getCurrDoT();
};

#endif