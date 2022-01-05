#include <./lib/frontend/components/healthbar.h>

#include <QDebug>

QProgressBar *Healthbar::Bar;
int Healthbar::currentHP;
int Healthbar::maxHP;

Healthbar::Healthbar(QWidget *parent) : QObject(parent) {

}

Healthbar::~Healthbar() {

}

void Healthbar::initHealthbar(QProgressBar *_Bar, int _currentHP, int _maxHP) {
    this->Bar = _Bar;
    this->currentHP = _currentHP;
    this->maxHP = _maxHP;
    this->setupBar();
}

void Healthbar::setupBar() {
    // Always remeber to setMaximum BEFORE setValue, please.
    this->Bar->setMaximum(maxHP);
    this->Bar->setValue(currentHP);
    this->Bar->setFormat(QString::number(currentHP) + "/" + QString::number(maxHP));
}

void Healthbar::updateBarOnDamage(int current, int max) {
    // Always remeber to setMaximum BEFORE setValue, please.
    this->currentHP = current;
    this->maxHP = max;
    setupBar();
}
