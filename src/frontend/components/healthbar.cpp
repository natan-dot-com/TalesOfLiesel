#include <./lib/frontend/components/healthbar.h>

#include <QDebug>

QLabel *Healthbar::mobLabel;
QString *Healthbar::mobName;
QProgressBar *Healthbar::Bar;
int Healthbar::currentHP;
int Healthbar::maxHP;
QString Healthbar::defaultBarStyle;

Healthbar::Healthbar(QWidget *parent) : QObject(parent) {

}

Healthbar::~Healthbar() {

}

void Healthbar::initHealthbar(QLabel *_mobLabel, QString *_mobName, QProgressBar *_Bar, int _currentHP, int _maxHP) {
    this->mobLabel = _mobLabel;
    this->mobName = _mobName;
    this->Bar = _Bar;
    this->currentHP = _currentHP;
    this->maxHP = _maxHP;
    this->defaultBarStyle = this->Bar->styleSheet();
    this->setupName();
    this->setupBar();
}

void Healthbar::changeColorOnDamage() {
    float ratio = (float) this->currentHP / (float) this->maxHP;
    int relativeValue = 100 * ratio;

    switch (relativeValue) {
        case 76 ... 101:
            this->Bar->setStyleSheet(
                "QProgressBar { \
                    background-color: rgb(255, 255, 255); \
                    color: rgb(58, 58, 58); \
                    border-style: outset; \
                    text-align: center; \
                } \
                \
                QProgressBar::chunk { \
                    background-color: #A3BE8C; \
                }"
            );
        break;

        case 51 ... 75:
            this->Bar->setStyleSheet(
                "QProgressBar { \
                    background-color: rgb(255, 255, 255); \
                    color: rgb(58, 58, 58); \
                    border-style: outset; \
                    text-align: center; \
                } \
                \
                QProgressBar::chunk { \
                    background-color: #EBCB8B; \
                }"
            );
        break;

        case 26 ... 50:
            this->Bar->setStyleSheet(
                "QProgressBar { \
                    background-color: rgb(255, 255, 255); \
                    color: rgb(58, 58, 58); \
                    border-style: outset; \
                    text-align: center; \
                } \
                \
                QProgressBar::chunk { \
                    background-color: #D08770; \
                }"
            );
         break;

        case 0 ... 25:
            this->Bar->setStyleSheet(
                "QProgressBar { \
                    background-color: rgb(255, 255, 255); \
                    color: rgb(58, 58, 58); \
                    border-style: outset; \
                    text-align: center; \
                } \
                \
                QProgressBar::chunk { \
                    background-color: #BF616A; \
                }"
            );
    }
}

void Healthbar::setupName() {
    this->mobLabel->setText(*this->mobName);
}

void Healthbar::setupBar() {
    // Always remeber to setMaximum BEFORE setValue, please.
    this->Bar->setMaximum(maxHP);
    this->Bar->setValue(currentHP);
    this->Bar->setFormat(QString::number(currentHP) + "/" + QString::number(maxHP));
    this->changeColorOnDamage();
}

void Healthbar::updateEnemyLabel(QString name) {
    this->mobLabel->setText(name);
}

void Healthbar::updateBarOnDamage(int current, int max) {
    // Always remeber to setMaximum BEFORE setValue, please.
    this->currentHP = current;
    this->maxHP = max;
    setupBar();
}
