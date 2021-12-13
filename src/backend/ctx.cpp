#include "./lib/backend/ctx.h"

Context::Context() {
	playerInstance =  new Liesel();
	currEnemyInstance =  new Enemy();
	errHandler =  new Error();
}

pairResult Context::damageOnClick() {
	int dealtDamage = playerInstance->generateDamageOnClick();
	if (currEnemyInstance->inflictDamage(dealtDamage)) {
		int gainedExp = currEnemyInstance->dropExpOnDeath();
		int gainedCoins = currEnemyInstance->dropCoinsOnDeath();

		Enemy *newEnemy = new Enemy(currEnemyInstance->getEnemyFloor());
		delete currEnemyInstance;
		currEnemyInstance = newEnemy;

		playerInstance->updateGainedCoins(gainedCoins);
		return std::make_pair(TurnResult {
			dealtDamage,
			gainedExp,
			gainedCoins,
			playerInstance->updateExp(gainedExp),
		}, true);
	}
	return std::make_pair(TurnResult {
		dealtDamage,
		0,
		0,
		false,
	}, true);
}

void Context::damageFireball(TurnResult &currResult, bool &isError) {
	int dealtDamage = playerInstance->fireSkill.skillEffect();
	if (dealtDamage != 0) {
		if (currEnemyInstance->inflictDamage(dealtDamage)) {
			int gainedExp = currEnemyInstance->dropExpOnDeath();
			int gainedCoins = currEnemyInstance->dropCoinsOnDeath();

			Enemy *newEnemy = new Enemy(currEnemyInstance->getEnemyFloor());
			delete currEnemyInstance;
			currEnemyInstance = newEnemy;

			playerInstance->updateGainedCoins(gainedCoins);

			currResult = TurnResult {
				dealtDamage,
				gainedExp,
				gainedCoins,
				playerInstance->updateExp(gainedExp),
			};
			isError = false;
			std::this_thread::sleep_for(std::chrono::seconds(10));
		}
		else {
			currResult = TurnResult {
				dealtDamage,
				0,
				0,
				false,
			};
			isError = false;
			std::this_thread::sleep_for(std::chrono::seconds(10));
		}
	}
	else {
		currResult = TurnResult {
			0,
			0,
			0,
			false,
		};
		isError = true;
	}
}

pairResult Context::evokeFireball() {
	if (this->fireballExec.joinable()) {
		TurnResult currResult;
		bool isError;

		this->fireballExec = std::thread(this->damageFireball(currResult, isError), currResult, isError);
		this->fireballExec.join();
		return std::make_pair(currResult, isError);
	}
}

bool Context::updateFireball() {
	int currSoulCoins = playerInstance->getSoulCoins();
	playerInstance->updateSpentCoins(currSoulCoins);
	return playerInstance->fireSkill.updateExp(currSoulCoins);
}

bool Context::updateChronomancy() {
	int currSoulCoins = playerInstance->getSoulCoins();
	playerInstance->updateSpentCoins(currSoulCoins);
	return playerInstance->chronoSkill.updateExp(currSoulCoins);
}

bool Context::updateDestructionAura() {
	int currSoulCoins = playerInstance->getSoulCoins();
	playerInstance->updateSpentCoins(currSoulCoins);
	return playerInstance->destructionSkill.updateExp(currSoulCoins);
}