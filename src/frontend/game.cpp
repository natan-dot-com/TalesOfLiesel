#include <./lib/frontend/game.h>
#include <QPoint>
#include <QCursor>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <ui_mainwindow.h>

Healthbar *Game::healthBar;
ActiveComponents *Game::activeComponents;
Context *Game::context;
QObject *Game::parent;
EnemyInformation *Game::eInfo;
EnemyButton *Game::eButton;
LieselInformation *Game::lInfo;

Game::Game(QObject *_ui, ActiveComponents *_activeComponents) {
    Game::parent = _ui;
    Game::activeComponents = _activeComponents;
    Game::context = new Context(); // Entire game backend
    Game::parent = _ui;

    // Game frontend
    Game::eButton = new EnemyButton(activeComponents->enemyButton);
    Game::eInfo = new EnemyInformation(activeComponents->mobName);
    Game::lInfo = new LieselInformation(activeComponents->soulCoinsValue, activeComponents->floorValue, activeComponents->currentXP, activeComponents->maxXP);
    Game::healthBar = new Healthbar(activeComponents->Bar->styleSheet(), activeComponents->Bar);
    Game::context->playerInstance->fireSkill.updateExp(10000);
    Game::context->playerInstance->destructionSkill.updateExp(10000);
}

void Game::gameUpdate() {
    Game::updateEnemyInfo();
    Game::updateEnemyButton();
    Game::updateLieselInfo();
    // Game::updateSkillInfo();
    Game::activeComponents->fireballCost->setText(QString::number(Game::context->playerInstance->fireSkill.getLevelUp() - Game::context->playerInstance->fireSkill.getExp()) + " Soul Coins");
}

void Game::updateSkillButton(int THREAD_ID, int cooldownValue) {
    switch (THREAD_ID) {
        case FIREBALL_THREAD_ID:
            Game::activeComponents->fireballUseButton->setText(QString::number(cooldownValue));

            // If cooldown ends...
            if (cooldownValue == 0) {
                Game::activeComponents->fireballUseButton->setText("USE");
            }
        break;

        case DESTAURA_THREAD_ID:
            Game::activeComponents->destructionAuraUseButton->setText(QString::number(cooldownValue));

            // If cooldown ends...
            if (cooldownValue == 0) {
                Game::activeComponents->destructionAuraUseButton->setText("USE");
            }
        break;
    }
}

void Game::updateLieselInfo() {
    Game::lInfo->updateLieselInfo(context->playerInstance->getSoulCoins(),
                                  context->getCurrentFloor(),
                                  context->playerInstance->getExp(),
                                  context->playerInstance->getLevelUp());
}

void Game::updateEnemyInfo() {
    Game::healthBar->setupBar(context->currEnemyInstance);
    Game::healthBar->updateBar(context->currEnemyInstance);
    Game::eInfo->updateEnemyInfo(QString::fromStdString(context->currEnemyInstance->getMobName()));
}

void Game::updateEnemyButton() {
    Game::eButton->updateEnemyIcon(context->currEnemyInstance);
}
