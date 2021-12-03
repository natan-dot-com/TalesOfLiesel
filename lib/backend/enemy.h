#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "./lib/backend/rng.h"
#include <string>
#include <QString>

#define BASE_ENEMY_HP 100

const QString adjectiveList[] = {
	"Mighty",
	"Fearsome",
	"Angry",
	"Robust",
	"Indomitable",
};

const QString specimenList[] = {
	"Skeleton",
	"Wolf",
	"Hyena",
	"Orc",
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
};

#endif
