#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "./lib/backend/rng.h"
#include <string>
#include <mutex>

#define BASE_ENEMY_HP 100
#define BASE_COIN_DROP 15
#define BASE_EXP_DROP 30

std::string adjectiveList[] = {
	"Mighty",
	"Fearsome",
	"Angry",
	"Robust",
	"Indomitable",
};

std::string specimenList[] = {
    "Mage",
	"Wolf",
    "Sorcerer",
    "Slayer",
	"Elf",
};

class Enemy : private Rng {
private:
	int enemyFloor;
    std::string enemyAdjective;
    std::string enemySpecimen;
	int currHP;
	int maxHP;

	std::mutex hpMutex;

    std::string getRandomAdjective();
    std::string getRandomSpecimen();
	int generateNewEnemy(int currFloor);

public:
	Enemy(int currFloor=1);

	bool inflictDamage(int damageTaken);
	int getEnemyFloor();
    std::string getMobName();
	int getCurrHP();
	int getMaxHP();
	int dropCoinsOnDeath();
	int dropExpOnDeath();
};

#endif
