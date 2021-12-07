#include <iostream>

#include "./lib/backend/enemy.h"
#include "./lib/backend/liesel.h"
#include "./lib/backend/rng.h"
#include "./lib/backend/skills.h"

using namespace std;

void EnemyTest() {
	Enemy newEnemy = Enemy(20);
	cout << newEnemy.getMobName() << endl;
	cout << "HP: " << newEnemy.getCurrHP() << "/" << newEnemy.getMaxHP() << endl;
	cout << "Mob floor level: " << newEnemy.getEnemyFloor() << endl;
	cout << "Inflicted 5 damage!" << endl;
	newEnemy.inflictDamage(5);
	cout << "HP: " << newEnemy.getCurrHP() << "/" << newEnemy.getMaxHP() << endl;
}

int main(int argc, char const *argv[]) {
	EnemyTest();
	return 0;
}