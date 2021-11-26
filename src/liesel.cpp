
#include <random>
#include <chrono>
#include <cmath>

#include <iostream>

// Temporary busy file

#define BASE_DOT_DMG 0.3
#define BASE_LEVEL_EXP 45
#define BASE_CLICK_DMG 8
#define BASE_FIREBALL_DMG 15
#define BASE_SKILL_EXP 100

// Generates a default normal distribution based pseudorandom number generator
class Rng {
	private:
		std::default_random_engine generator;
		std::normal_distribution<double> rng;

	public:
		Rng() {
			generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
			rng = std::normal_distribution<double>(0, 1);
		}

		// Generates a random real number.
		// - Return value: a random number (double)
		double generateRandom() {
			return this->rng(generator);
		}

		// Generates a random real number bounded by a maximum standard deviation quantity.
		// - Return value: Random number bounded from both sides by maxSD (double)
		double generateRandom(double maxSD) {
			double rand;
			do {
				rand = this->rng(generator);
			} while (rand < (-1) * maxSD || rand > maxSD);
			return rand;
		}
};

// Base class for an in-game skill
class Skill : public Rng {
	protected:
		int skillLevel;
		int skillExp;

	public:
		Skill() {
			skillLevel = 0;
			skillExp = 0;
		}

		// Getters
		int getLevel() {
			return skillLevel;
		}

		int getExp() {
			return skillExp;
		}

		int getLevelUp() {
			return BASE_SKILL_EXP * (0.8 * pow(skillLevel+1, 1.25));
		}

		// Increase experience amount by a certain value, leveling it up if needed. 
		// - Return value: true if the level grew up, false if not.
		bool updateExp(int gainedExp) {
			skillExp += gainedExp;
			if (skillExp >= this->getLevelUp()) {
				skillExp %= this->getLevelUp();
				skillLevel++;
				return true;
			}
			return false;
		}

		// Abstract method in which defines the current skill effect.
		virtual double skillEffect() = 0;
		
};

// Fire Ball: Casts a fire ball, dealing heavy magic damage on contact.
class Fireball : public Skill {
	public:
		double skillEffect() {
			if (this->getLevel() != 0) {
				return std::round(BASE_FIREBALL_DMG * (0.8 * this->getLevel()) + 1.5 * this->generateRandom(3.0));
			}
			return 0;
		}
};

// Chronomancy: Stops the current monster watch for a few seconds.
class Chronomancy : public Skill {
	public:
		double skillEffect() {
			return 1;
			// WIP...
		}
};

// Destruction Aura: Enable DoT (Damage Over Time) per tick.
class DestructionAura : public Skill {
	private:
		double skillEffect() {
			return BASE_DOT_DMG * pow(this->getLevel(), 1.25);
		} 	

	protected:
		double currDoT;
	
	public:
		void updateExp(int gainedExp) {
			if (Skill::updateExp(gainedExp)) {
				currDoT = this->skillEffect();
			}
		}

		double getCurrDoT() {
			return currDoT;
		}
};

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