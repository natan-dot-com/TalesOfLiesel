#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "./lib/backend/rng.h"
#include <string>

#define BASE_ENEMY_HP 100

const std::string adjectiveList[] = {
	"Mighty",
	"Fearsome",
	"Angry",
	"Robust",
	"Indomitable",
};

const std::string specimenList[] = {
	"Skeleton",
	"Wolf",
	"Hyena",
	"Orc",
	"Elf",
};

class Enemy : private Rng {
private:
	int enemyFloor;
	std::string enemyAdjective;
	std::string enemySpecimen;
	int currHP;
	int maxHP;

	std::string getRandomAdjective();
	std::string getRandomSpecimen();
	int generateNewEnemy(int currFloor);

public:
	Enemy(int currFloor = 1);

	bool inflictDamage(int damageTaken);
	int getEnemyFloor();
	std::string getMobName();
	int getCurrHP();
	int getMaxHP();
};

#endif
