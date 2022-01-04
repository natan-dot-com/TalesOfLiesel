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
	Context *newContext = new Context();
	TurnResults *test;
	char ch;
	while (true) {
		cin >> ch;
		if (ch == 't') {
			test = newContext->evokeDestructionAura();
		}
		else if (ch == 'k') {
			test = newContext->evokeFireball();
		}
		else if (ch == 'm') {
			test = newContext->evokeDamageOnClick();
		}
		else if (ch == 'z') {
			newContext->previousFloor();
		}
		else if (ch == 'x') {
			newContext->nextFloor();
		} 
		else if (ch == 'c') {
			cout << newContext->getCurrentFloor() << endl;
		}
		else if (ch == 'l') {
			newContext->playerInstance->destructionSkill.updateExp(10000);
			cout << newContext->playerInstance->destructionSkill.getLevel() << endl;
		}
		else if (ch == 'p') {
			cout << newContext->currEnemyInstance->getMaxHP() << "/" << newContext->currEnemyInstance->getCurrHP() << endl;
		}
	}
}

int main(int argc, char const *argv[]) {
	ThreadsTest();
	return 0;
}