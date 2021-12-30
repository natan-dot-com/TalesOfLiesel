#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <QGraphicsItem>
#include <QLabel>
#include <QIcon>
#include <QPushButton>
#include <./lib/backend/enemy.h>

struct ActiveComponents {
    // Actively changed components.
    QLabel *currentXP;
    QLabel *maxXP;
    QLabel *mobName;
    QLabel *currentHP;
    QLabel *maxHP;
    QLabel *Bar;
    QLabel *floorValue;
    QLabel *soulCoinsValue;
    QLabel *fireballCost;
    QLabel *chronomancyCost;
    QLabel *destructionAuraCost;
    QLabel *damageIndicator;
    QPushButton *enemyButton;
    QPushButton *upgradeFireball;
    QPushButton *upgradeChronomancy;
    QPushButton *upgradeDestructionAura;

    ActiveComponents(QLabel *_currentXP,
               QLabel *_maxXP,
               QLabel *_mobName,
               QLabel *_currentHP,
               QLabel *_maxHP,
               QLabel *_Bar,
               QLabel *_floorValue,
               QLabel *_soulCoinsValue,
               QLabel *_fireballCost,
               QLabel *_chronomancyCost,
               QLabel *_destructionAuraCost,
               QLabel *_damageIndicator,
               QPushButton *_enemyButton,
               QPushButton *_upgradeFireball,
               QPushButton *_upgradeChronomancy,
               QPushButton *_upgradeDestructionAura) {
        this->currentXP = _currentXP;
        this->maxXP = _maxXP;
        this->mobName = _mobName;
        this->currentHP = _currentHP;
        this->maxHP = _maxHP;
        this->Bar = _Bar;
        this->floorValue = _floorValue;
        this->soulCoinsValue = _soulCoinsValue;
        this->fireballCost = _fireballCost;
        this->chronomancyCost = _chronomancyCost;
        this->destructionAuraCost = _destructionAuraCost;
        this->damageIndicator = _damageIndicator;
        this->enemyButton = _enemyButton;
        this->upgradeFireball = _upgradeFireball;
        this->upgradeChronomancy = _upgradeChronomancy;
        this->upgradeDestructionAura = _upgradeDestructionAura;
    }
};

struct LieselInformation {
    // Pointers to the Qt Components
    QLabel *currentXP;
    QLabel *maxXP;
    QLabel *floorValue;
    QLabel *soulCoins;

    LieselInformation(QLabel *_soulCoins, QLabel *_floorValue, QLabel *_currentXP, QLabel *_maxXP) {
        this->soulCoins = _soulCoins;
        this->floorValue = _floorValue;
        this->currentXP = _currentXP;
        this->maxXP = _maxXP;
    }

    void updateLieselInfo(int soulCoins, int floor, int curr, int max) {
        this->floorValue->setText(QString::number(floor));
        this->currentXP->setText(QString::number(curr));
        this->maxXP->setText(QString::number(max));
        this->soulCoins->setText(QString::number(soulCoins));
    }
};

struct EnemyInformation {
    // Pointers to the Qt Components
    QLabel *currentHP;
    QLabel *maxHP;
    QLabel *mobName;

    EnemyInformation(QLabel *_mobName, QLabel *_currentHP, QLabel *_maxHP) {
        this->mobName = _mobName;
        this->currentHP = _currentHP;
        this->maxHP = _maxHP;
    }

    void updateEnemyInfo(QString _mobName, int curr, int max) {
        this->mobName->setText(_mobName);
        this->currentHP->setText(QString::number(curr));
        this->maxHP->setText(QString::number(max));
    }
};

struct Healthbar {
    int barWidth;
    QString defaultStyle;

    // Pointer to the Qt Component
    QLabel *Bar;

    Healthbar(int _barWidth, QString _defaultStyle, QLabel *_Bar) {
        this->barWidth = _barWidth;
        this->defaultStyle = _defaultStyle;
        this->Bar = _Bar;
    }

    float getDamagedRatio(float current, float max) {
        return current/max;
    }

    void updateBar(Enemy *e) {
        this->Bar->setFixedWidth(getDamagedRatio(e->getCurrHP(), e->getMaxHP()) * barWidth);

        switch(e->getCurrHP()) {
            case 51 ... 75:
                this->Bar->setStyleSheet(
                    "border-radius: \
                        3px; \
                     background-color: \
                        QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #bee25b, stop: .5 #a1d54f, stop: .51 #729818, stop: 1 #7cbc0a);"
                );
            break;

            case 26 ... 50:
                this->Bar->setStyleSheet(
                    "border-radius: \
                        3px; \
                     background-color: \
                        QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dea801, stop: .5 #ffcf3b, stop: .51 #957107, stop: 1 #715e28);"
                );
             break;

            case 0 ... 25:
                this->Bar->setStyleSheet(
                    "border-radius: \
                        3px; \
                     background-color: \
                        QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #bb5107, stop: .5 #f5873b, stop: .51 #973b00, stop: 1 #553521);"
                );
             break;
        }

        if (e->getCurrHP() <= 0 or e->getCurrHP() == e->getMaxHP()) {
            resetBar();
        }
    }

    void resetBar() {
        this->Bar->setStyleSheet(defaultStyle);
        this->Bar->setFixedWidth(barWidth);
    }
};

struct EnemyButton {
    QIcon enemyIcon;

    // Pointer to the Qt Component
    QPushButton *button;

    EnemyButton(QPushButton *_button) {
        this->button = _button;
    }

    void updateEnemyIcon(Enemy *e) {
        if (e->getCurrHP() == e->getMaxHP() or e->getCurrHP() == 0) {
            QString enemyName = QString::fromStdString(e->getMobName());

            if (enemyName.contains(QString("Mage"))) {
                this->button->setIcon(QIcon(":/imgs/src/assets/enemies/enemies_full/mage-1.png"));
                this->button->setIconSize(QSize(600, 600));
                // qDebug() << "Mage" << "\n";
                return;
            }

            if (enemyName.contains(QString("Elf"))) {
                this->button->setIcon(QIcon(":/imgs/src/assets/enemies/enemies_full/elf-1.png"));
                this->button->setIconSize(QSize(600, 600));
                // qDebug() << "Elf" << "\n";
                return;
            }

            if (enemyName.contains(QString("Sorcerer"))) {
                this->button->setIcon(QIcon(":/imgs/src/assets/enemies/enemies_full/sorcerer-1.png"));
                this->button->setIconSize(QSize(600, 600));
                // qDebug() << "Sorcerer" << "\n";
                return;
            }

            if (enemyName.contains(QString("Slayer"))) {
                this->button->setIcon(QIcon(":/imgs/src/assets/enemies/enemies_full/slayer-1.png"));
                this->button->setIconSize(QSize(600, 600));
                // qDebug() << "Sorcerer" << "\n";
                return;
            }

            if (enemyName.contains(QString("Wolf"))) {
                this->button->setIcon(QIcon(":/imgs/src/assets/enemies/enemies_full/wolf-1.png"));
                this->button->setIconSize(QSize(600, 600));
                // qDebug() << "Sorcerer" << "\n";
                return;
            }
        }

    }
};

#endif // COMPONENTS_H
