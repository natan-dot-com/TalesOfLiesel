#include "./lib/backend/liesel.h"

#define BASE_CLICK_DMG 8

#define BASE_LEVEL_EXP 45

// Constructors
Liesel::Liesel() {
	currLevel = 1;
	currExp = 0;
	soulCoinsAmount = 0;
	fireSkill = Fireball();
	destructionSkill = DestructionAura();
}

// Setters
bool Liesel::updateExp(int gainedExp) {
	currExp += gainedExp;
	if (currExp >= this->getLevelUp()) {
		currExp %= this->getLevelUp();
		currLevel++;
		return true;	
	}
	return false;
}

void Liesel::updateGainedCoins(int gainedCoins) {
	soulCoinsAmount += gainedCoins;
}

bool Liesel::updateSpentCoins(int spentCoins) {
	if (soulCoinsAmount >= spentCoins) {
		soulCoinsAmount -= spentCoins;
		return true;	
	}
	return false;
}

// Getters
int Liesel::getLevelUp() {
	return BASE_LEVEL_EXP * std::round(0.8 * pow(currLevel, 1.75));
}

int Liesel::getLevel() {
	return currLevel;
}

int Liesel::getExp() {
	return currExp;
}

int Liesel::getSoulCoins() {
	return soulCoinsAmount;
}

// Generates a random click damage based on at most 2 standard deviations (normalized).
int Liesel::generateDamageOnClick() {
	return std::round(BASE_CLICK_DMG + (0.85 * currLevel) + 1.25 * Rng::generateRandom(2.0));
}
