#include <./lib/frontend/components/lieselinfo.h>

LieselInfo::LieselInfo(QWidget *parent) : QObject(parent) {

}

void LieselInfo::initLieselInfo(QPair<QLabel *, QString> _floorValue,
                                QPair<QLabel *, QString> _currentLevelValue,
                                QPair<QLabel *, QString> _currentLevelExp,
                                QPair<QLabel *, QString> _currentLevelMax,
                                QPair<QLabel *, QString> _soulCoinsValue) {
    this->floorValue.LABEL = _floorValue.LABEL;
    this->floorValue.STRING = _floorValue.STRING;
    this->currentLevelValue.LABEL = _currentLevelValue.LABEL;
    this->currentLevelValue.STRING = _currentLevelValue.STRING;
    this->currentLevelExp.LABEL = _currentLevelExp.LABEL;
    this->currentLevelExp.STRING = _currentLevelExp.STRING;
    this->currentLevelMax.LABEL = _currentLevelMax.LABEL;
    this->currentLevelMax.STRING = _currentLevelMax.STRING;
    this->soulCoinsValue.LABEL = _soulCoinsValue.LABEL;
    this->soulCoinsValue.STRING = _soulCoinsValue.second;
    setupLieselInfo();
}

/* QString::number(game->getCurrentFloor()),
                                 QString::number(game->playerInstance->getExp()),
                                 QString::number(game->playerInstance->getLevelUp()),
                                 QString::number(game->playerInstance->getSoulCoins()) */

void LieselInfo::setupLieselInfo() {
    this->floorValue.LABEL->setText(this->floorValue.STRING);
    this->currentLevelValue.LABEL->setText(this->currentLevelValue.STRING);
    this->currentLevelExp.LABEL->setText(this->currentLevelExp.STRING);
    this->currentLevelMax.LABEL->setText(this->currentLevelMax.STRING);
    this->soulCoinsValue.LABEL->setText(this->soulCoinsValue.STRING);
}

void LieselInfo::updateLieselInfoLabels(QString a, QString b, QString c, QString d, QString e) {
    this->floorValue.STRING = a;
    this->currentLevelValue.STRING = b;
    this->currentLevelExp.STRING = c;
    this->currentLevelMax.STRING = d;
    this->soulCoinsValue.STRING = e;
    setupLieselInfo();
}
