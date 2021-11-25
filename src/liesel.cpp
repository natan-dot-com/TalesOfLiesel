
#include <random>
#include <chrono>
#include <cmath>

// Temporary busy file

#define BASE_DOT_DMG 0.3
#define BASE_LEVEL_EXP 45
#define BASE_CLICK_DMG 8
#define BASE_FIREBALL_DMG 15

#define RNG_MEAN 0
#define RNG_SD 1.5

// Liesel skills:
//	- Fire ball: Heavy magic damage (active).
//	- Chronomancy: Stop timer for a few sec (active)
//	- Destruction aura: DoT (passive)
//
// To-do:
//	- Enable exp on skills
class MagicSkills {
	protected:
		int fireBallLevel;
		int chronomancyLevel;
		int destructionAuraLevel;

	public:
		MagicSkills() {
			fireBallLevel = 0;
			chronomancyLevel = 0;
			destructionAuraLevel = 0;
		}

		// Setters
		void setUpdateFireball() {
			fireBallLevel++;
		}

		void setUpdateChronomancy() {
			chronomancyLevel++;
		}

		void setUpdateDestruction() {
			destructionAuraLevel++;
		}

		// Getters
		int getFireballLevel() {
			return fireBallLevel;
		}

		int getChronomancyLevel() {
			return chronomancyLevel;
		}

		int getDestructionLevel() {
			return destructionAuraLevel;
		}
};

class Liesel : public MagicSkills { 
	private:
		std::default_random_engine generator;
		std::normal_distribution<double> rng;

	protected:
		int currExp;
		int currLevel;
		int soulCoinsAmount;
		double currDoT;

	public:
		// Constructors
		Liesel() {
			this->currLevel = 1;
			this->currExp = 0;
			this->currDoT = 0.0;
			this->soulCoinsAmount = 0;
			this->generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
			this->rng = std::normal_distribution<double>(RNG_MEAN, RNG_SD);
		}

		// Setters
		bool setUpdateExp(int gainedExp) {
			this->currExp += gainedExp;
			if (this->currExp >= this->getExpLevelUp()) {
				this->currExp %= this->getExpLevelUp();
				this->currLevel++;
				return true;	
			}
			return false;
		}

		void setUpdateDoT() {
			this->setUpdateDestruction();
			this->currDoT = BASE_DOT_DMG * pow(this->getDestructionLevel(), 1.25);
		}

		void setGainedCoins(int gainedCoins) {
			this->soulCoinsAmount += gainedCoins;
		}

		bool setSpentCoins(int spentCoins) {
			if (this->soulCoinsAmount >= spentCoins) {
				this->soulCoinsAmount -= spentCoins;
				return true;	
			}
			return false;
			
		}

		// Getters
		int getExpLevelUp() {
			return BASE_LEVEL_EXP * std::round(0.8 * pow(this->currLevel, 1.75));
		}

		int getCurrLevel() {
			return this->currLevel;
		}

		double getCurrDoT() {
			return this->currDoT;
		}

		int getSoulCoins() {
			return this->soulCoinsAmount;
		}

		// Generators
		// Generates a random click damage based on at most 2 standard deviations (normalized).
		int generateDamageOnClick() {
			double offset;
			do {
				offset = this->rng(this->generator);
			} while (offset < (-2)*RNG_SD || offset > 2*RNG_SD);
			return std::round(BASE_CLICK_DMG * (0.8 * this->currLevel) + 1.25 * offset);
		}

		// Generates a random fireball damage based on at most 3 standard deviations (normalized).
		int generateFireballDamage() {
			double offset;
			do {
				offset = this->rng(this->generator);
			} while (offset < (-3)*RNG_SD || offset > 3*RNG_SD);
			return std::round(BASE_FIREBALL_DMG * (0.8 * this->getFireballLevel()) + 1.5 * offset);
		}
};