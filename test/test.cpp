#include <iostream>

#include "./lib/enemy.h"
#include "./lib/liesel.h"
#include "./lib/rng.h"
#include "./lib/skills.h"

using namespace std;

void EnemyTest() {
	Enemy newEnemy;
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