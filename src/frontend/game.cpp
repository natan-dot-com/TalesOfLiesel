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
}

void Game::setupGameStart() {
    Game::updateEnemyInfo();
    // this->updateLieselInfo();
    Game::updateEnemyButton();
}

void Game::onDefaultDamage() {
    TurnResults *dmg = context->evokeDamageOnClick();

    if (dmg) {
        // QPoint pos = QCursor::pos();
//        QGraphicsOpacityEffect a(activeComponents->damageIndicator);
//        activeComponents->damageIndicator->setGraphicsEffect(&a);
//        a.setOpacity(1);

//        QPropertyAnimation b(&a, "opacity", this->parent);
//        b.setStartValue(1);
//        b.setEndValue(0);
//        b.setDuration(200);
//        b.setEasingCurve(QEasingCurve::Linear);
//        b.start();

//        if(b.state() != QAbstractAnimation::Stopped) {
//            b.pause();
//        }

//        this->activeComponents->damageIndicator->setGeometry(pos.x()+25, pos.y()-10, 50, 50);
//        this->activeComponents->damageIndicator->setText(QString::number(dmg->damageDealt));
    }

    Game::updateEnemyInfo();
    Game::updateEnemyButton();
    Game::updateLieselInfo();
}

void Game::onFireballDamage() {
    Game::context->evokeFireball();
    Game::updateEnemyInfo();
    Game::updateEnemyButton();
    Game::updateLieselInfo();
}

void Game::onChronomancy() {

}

void Game::onDestructionAura() {
    Game::updateEnemyInfo();
    Game::updateEnemyButton();
    Game::updateLieselInfo();
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
