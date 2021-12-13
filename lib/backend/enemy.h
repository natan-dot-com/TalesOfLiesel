#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "./lib/backend/rng.h"
#include <string>
#include <QString>

#define BASE_ENEMY_HP 100
#define BASE_COIN_DROP 15
#define BASE_EXP_DROP 30

const QString adjectiveList[] = {
	"Mighty",
	"Fearsome",
	"Angry",
	"Robust",
	"Indomitable",
};

const QString specimenList[] = {
    "Mage",
	"Wolf",
    "Sorcerer",
    "Slayer",
	"Elf",
};

class Enemy : private Rng {
private:
	int enemyFloor;
    QString enemyAdjective;
    QString enemySpecimen;
	int currHP;
	int maxHP;

    QString getRandomAdjective();
    QString getRandomSpecimen();
	int generateNewEnemy(int currFloor);

public:
	Enemy(int currFloor = 1);

	bool inflictDamage(int damageTaken);
	int getEnemyFloor();
    QString getMobName();
	int getCurrHP();
	int getMaxHP();
	int dropCoinsOnDeath();
	int dropExpOnDeath();
};

#endif
