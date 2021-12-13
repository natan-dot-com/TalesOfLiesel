#include "./lib/backend/enemy.h"

int Enemy::generateNewEnemy(int currFloor) {
	return BASE_ENEMY_HP * (1 + 0.25 * currFloor) + (15 * this->generateRandom(3.0));
}

QString Enemy::getRandomAdjective() {
	return adjectiveList[this->generateUniformRandom()];
}

QString Enemy::getRandomSpecimen() {
	return specimenList[this->generateUniformRandom()];
}

Enemy::Enemy(int currFloor) : Rng(0, (int) sizeof(adjectiveList)/sizeof(adjectiveList[0])-1) {
	enemyFloor = currFloor;
	enemyAdjective = this->getRandomAdjective();
	enemySpecimen = this->getRandomSpecimen();
	maxHP = this->generateNewEnemy(currFloor);
	currHP = maxHP;
}

bool Enemy::inflictDamage(int damageTaken) {
	const std::lock_guard<std::mutex> lock(hpMutex);
	if (damageTaken >= currHP) {
		currHP = 0;
		return true;
	}
	currHP -= damageTaken;
	return false;
}

int Enemy::getEnemyFloor() {
	return enemyFloor;
}

int Enemy::getCurrHP() {
	return currHP;
}

int Enemy::getMaxHP() {
	return maxHP;
}

QString Enemy::getMobName() {
	return enemyAdjective + " " + enemySpecimen;
}

int Enemy::dropCoinsOnDeath() {
	return BASE_COIN_DROP * (1 + 0.4 * enemyFloor);
}

int Enemy::dropExpOnDeath() {
	return BASE_EXP_DROP * (1 + 0.25 * pow(enemyFloor, 2)) + 1.5 * this->generateRandom(4.0);
}