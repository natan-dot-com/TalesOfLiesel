#include "rng.h"
#include "skills.h"

#include <iostream>

#define BASE_CLICK_DMG 8

#define BASE_LEVEL_EXP 45

class Liesel : private Rng { 
	protected:
		// Main character stats
		int currExp;
		int currLevel;
		int soulCoinsAmount;

	public:
		// Main character skills
		Fireball fireSkill;
		DestructionAura destructionSkill;
		Chronomancy chronoSkill;

		// Constructors
		Liesel() {
			currLevel = 1;
			currExp = 0;
			soulCoinsAmount = 0;
			fireSkill = Fireball();
			destructionSkill = DestructionAura();
			chronoSkill = Chronomancy();
		}

		// Setters
		bool updateExp(int gainedExp) {
			currExp += gainedExp;
			if (currExp >= this->getLevelUp()) {
				currExp %= this->getLevelUp();
				currLevel++;
				return true;	
			}
			return false;
		}

		void updateGainedCoins(int gainedCoins) {
			soulCoinsAmount += gainedCoins;
		}

		bool updateSpentCoins(int spentCoins) {
			if (soulCoinsAmount >= spentCoins) {
				soulCoinsAmount -= spentCoins;
				return true;	
			}
			return false;
			
		}

		// Getters
		int getLevelUp() {
			return BASE_LEVEL_EXP * std::round(0.8 * pow(currLevel, 1.75));
		}

		int getLevel() {
			return currLevel;
		}

		int getExp() {
			return currExp;
		}

		int getSoulCoins() {
			return soulCoinsAmount;
		}

		// Generates a random click damage based on at most 2 standard deviations (normalized).
		int generateDamageOnClick() {
			return std::round(BASE_CLICK_DMG * (0.8 * currLevel) + 1.25 * Rng::generateRandom(2.0));
		}
};

int main() {
	Liesel newPlayer;
	
	newPlayer.updateExp(500);
	std::cout << "Player:" << std::endl;
	std::cout << newPlayer.getExp() << std::endl;
	std::cout << newPlayer.getLevel() << std::endl;

	newPlayer.fireSkill.updateExp(100);
	std::cout << "Fire ball:" << std::endl;
	std::cout << newPlayer.fireSkill.getLevelUp() << std::endl;
	std::cout << newPlayer.fireSkill.getLevel() << std::endl;
	std::cout << newPlayer.fireSkill.getExp() << std::endl;
	std::cout << newPlayer.fireSkill.skillEffect() << std::endl;

	std::cout << "Destruction aura:" << std::endl;
	newPlayer.destructionSkill.updateExp(100);
	std::cout << newPlayer.destructionSkill.getLevelUp() << std::endl;
	std::cout << newPlayer.destructionSkill.getLevel() << std::endl;
	std::cout << newPlayer.destructionSkill.getExp() << std::endl;
	std::cout << newPlayer.destructionSkill.getCurrDoT() << std::endl;

	return 0;
}