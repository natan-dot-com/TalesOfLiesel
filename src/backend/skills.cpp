#include "./lib/backend/skills.h"

#define BASE_DOT_DMG 3
#define BASE_DOT_MULTIPLIER 0.7
#define BASE_FIREBALL_DMG 15

#define BASE_SKILL_EXP 100

Skill::Skill() {
    skillLevel = 0;
	skillExp = 0;
}

// Getters
int Skill::getLevel() {
	return skillLevel;
}

int Skill::getExp() {
	return skillExp;
}

int Skill::getLevelUp() {
	return BASE_SKILL_EXP * (0.8 * pow(skillLevel+1, 1.25));
}

// Increase experience amount by a certain value, leveling it up if needed. 
// - Return value: true if the level grew up, false if not.
bool Skill::updateExp(int gainedExp) {
	skillExp += gainedExp;
	int currLevel = this->getLevel();

	while (skillExp >= this->getLevelUp()) {
		skillLevel++;
		skillExp -= this->getLevelUp();
	}

	if (this->getLevel() != currLevel) {
		return true;
	}
	return false;
}

// Fire Ball: Casts a fire ball, dealing heavy magic damage on contact.
double Fireball::skillEffect() {
	if (this->getLevel() > 0) {
		return std::round(BASE_FIREBALL_DMG * (0.8 * this->getLevel()) + 1.5 * this->generateRandom(3.0));
	}
	return 0;
}

// Destruction Aura: Enable DoT (Damage Over Time) per tick.
double DestructionAura::skillEffect() {
	return std::roundf(BASE_DOT_DMG + BASE_DOT_MULTIPLIER * pow(this->getLevel(), 1.25) * 10 / 10);
} 	

bool DestructionAura::updateExp(int gainedExp) {
	if (Skill::updateExp(gainedExp)) {
		currDoT = this->skillEffect();
		return true;
	}
	return false;
}

double DestructionAura::getCurrDoT() {
	return currDoT;
}
