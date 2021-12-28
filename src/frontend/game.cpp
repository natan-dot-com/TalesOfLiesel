#include <./lib/frontend/game.h>

Game::Game(ActiveComponents *_activeComponents) {
    this->activeComponents = _activeComponents;
    this->context = new Context(); // Entire game backend

    // Game frontend
    this->eButton = new EnemyButton(activeComponents->enemyButton);
    this->eInfo = new EnemyInformation(activeComponents->mobName, activeComponents->currentHP, activeComponents->maxHP);
    this->lInfo = new LieselInformation(activeComponents->soulCoinsValue, activeComponents->floorValue, activeComponents->currentXP, activeComponents->maxXP);
    this->healthBar = new Healthbar(activeComponents->Bar->width(), activeComponents->Bar->styleSheet(), activeComponents->Bar);
}

void Game::setupGameStart() {
    this->updateEnemyInfo();
    this->updateLieselInfo();
    this->updateEnemyButton();
}

void Game::onDefaultDamage() {
    this->context->evokeDamageOnClick();
    this->updateEnemyInfo();
    this->updateEnemyButton();
    this->updateLieselInfo();
}

void Game::onFireballDamage() {

}

void Game::onChronomancy() {

}

void Game::updateLieselInfo() {
    this->lInfo->updateLieselInfo(this->context->playerInstance->getSoulCoins(),
                                  this->context->getCurrentFloor(),
                                  this->context->playerInstance->getExp(),
                                  this->context->playerInstance->getLevelUp());
}

void Game::updateEnemyInfo() {
    this->healthBar->updateBar(this->context->currEnemyInstance);
    this->eInfo->updateEnemyInfo(QString::fromStdString(this->context->currEnemyInstance->getMobName()),
                                 this->context->currEnemyInstance->getCurrHP(),
                                 this->context->currEnemyInstance->getMaxHP());
}

void Game::updateEnemyButton() {
    this->eButton->updateEnemyIcon(this->context->currEnemyInstance);
}
