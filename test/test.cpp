#include <iostream>

#include "./lib/backend/enemy.h"
#include "./lib/backend/liesel.h"
#include "./lib/backend/rng.h"
#include "./lib/backend/skills.h"
#include "./lib/backend/ctx.h"

using namespace std;

void EnemyTest() {
	Enemy *newEnemy = new Enemy(20);
	cout << newEnemy->getMobName() << endl;
	cout << "HP: " << newEnemy->getCurrHP() << "/" << newEnemy->getMaxHP() << endl;
	cout << "Mob floor level: " << newEnemy->getEnemyFloor() << endl;
	cout << "Inflicted 5 damage!" << endl;
	newEnemy->inflictDamage(5);
	cout << "HP: " << newEnemy->getCurrHP() << "/" << newEnemy->getMaxHP() << endl;
}

void ThreadsTest() {
	Context newContext = Context();
	char ch;
	while (true) {
		cin >> ch;
		if (ch == 't') {
			newContext.evokeFireball();
		}
		else if (ch == 'p') {
			cout << newContext.currEnemyInstance->getMaxHP() << "/" << newContext.currEnemyInstance->getCurrHP() << endl;
		}
		else if (ch == 'm') {
			cout << "aaaaa" << endl;
		}
	}
}

int main(int argc, char const *argv[]) {
	ThreadsTest();
	return 0;
}