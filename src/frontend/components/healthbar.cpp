#include <./lib/frontend/components/healthbar.h>

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
}

void Healthbar::setupBar() {
    this->Bar->setValue(this->currentHP);
    this->Bar->setMaximum(this->maxHP);
}

void Healthbar::updateBar() {
    this->Bar->setValue(this->currentHP--);
}
