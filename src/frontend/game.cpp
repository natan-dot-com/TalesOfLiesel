#include <./lib/frontend/game.h>
#include <QPoint>
#include <QCursor>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <ui_mainwindow.h>

Game::Game(QObject *_ui, ActiveComponents *_activeComponents) {
    this->parent = _ui;
    this->activeComponents = _activeComponents;
    this->context = new Context(); // Entire game backend
    this->parent = _ui;

    // Game frontend
    this->eButton = new EnemyButton(activeComponents->enemyButton);
    this->eInfo = new EnemyInformation(activeComponents->mobName);
    this->lInfo = new LieselInformation(activeComponents->soulCoinsValue, activeComponents->floorValue, activeComponents->currentXP, activeComponents->maxXP);
    this->healthBar = new Healthbar(activeComponents->Bar->styleSheet(), activeComponents->Bar);
    this->context->playerInstance->fireSkill.updateExp(10000);
}

void Game::setupGameStart() {
    this->updateEnemyInfo();
    // this->updateLieselInfo();
    this->updateEnemyButton();
}

void Game::onDefaultDamage() {
    TurnResults *dmg = this->context->evokeDamageOnClick();

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

    this->updateEnemyInfo();
    this->updateEnemyButton();
    this->updateLieselInfo();
}

void Game::onFireballDamage() {
    this->context->evokeFireball();
    this->updateEnemyInfo();
    this->updateEnemyButton();
    this->updateLieselInfo();
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
    this->healthBar->setupBar(this->context->currEnemyInstance);
    this->healthBar->updateBar(this->context->currEnemyInstance);
    this->eInfo->updateEnemyInfo(QString::fromStdString(this->context->currEnemyInstance->getMobName()));
}

void Game::updateEnemyButton() {
    this->eButton->updateEnemyIcon(this->context->currEnemyInstance);
}
