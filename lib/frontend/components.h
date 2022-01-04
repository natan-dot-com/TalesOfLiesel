#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <QGraphicsItem>
#include <QLabel>
#include <QIcon>
#include <QPushButton>
#include <QProgressBar>
#include <./lib/backend/enemy.h>

struct ActiveComponents {
    // Actively changed components.
    QLabel *currentXP;
    QLabel *maxXP;
    QLabel *mobName;
    QProgressBar *Bar;
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
               QProgressBar *_Bar,
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
    QLabel *mobName;

    EnemyInformation(QLabel *_mobName) {
        this->mobName = _mobName;
    }

    void updateEnemyInfo(QString _mobName) {
        this->mobName->setText(_mobName);
    }
};

struct Healthbar {
    int barWidth;
    QString defaultStyle;

    // Pointer to the Qt Component
    QProgressBar *Bar;

    Healthbar(QString _defaultStyle, QProgressBar *_Bar) {
        this->Bar = _Bar;
        this->defaultStyle = _defaultStyle;
    }

    float getDamagedRatio(float current, float max) {
        return current/max;
    }

    void setupBar(Enemy *e) {
        this->Bar->setValue(e->getCurrHP());
        this->Bar->setMaximum(e->getMaxHP());
    }

    void updateBar(Enemy *e) {
        this->Bar->setValue(e->getCurrHP());
        this->Bar->setMaximum(e->getMaxHP());
        this->Bar->setFormat(QString::number(e->getCurrHP()) + "/" + QString::number(e->getMaxHP()));

        switch(e->getCurrHP()) {
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
             break;
        }

        if (e->getCurrHP() <= 0 or e->getCurrHP() == e->getMaxHP()) {
            resetBar();
        }
    }

    void resetBar() {
        this->Bar->setStyleSheet(defaultStyle);
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
                this->button->setStyleSheet("background-image: url(:/imgs/src/assets/enemies/enemies_full/mage-1.png); \
                                            background-repeat: none; \
                                            background-position: bottom center; \
                                            background-attachment: fixed; \
                                            background-color: transparent;");
                // qDebug() << "Mage" << "\n";
                return;
            }

            if (enemyName.contains(QString("Elf"))) {
                this->button->setStyleSheet("background-image: url(:/imgs/src/assets/enemies/enemies_full/elf-1.png); \
                                            background-repeat: none; \
                                            background-position: bottom center; \
                                            background-attachment: fixed; \
                                            background-color: transparent;");
                // qDebug() << "Elf" << "\n";
                return;
            }

            if (enemyName.contains(QString("Sorcerer"))) {
                this->button->setStyleSheet("background-image: url(:/imgs/src/assets/enemies/enemies_full/sorcerer-1.png); \
                                            background-repeat: none; \
                                            background-position: bottom center; \
                                            background-attachment: fixed; \
                                            background-color: transparent;");
                // qDebug() << "Sorcerer" << "\n";
                return;
            }

            if (enemyName.contains(QString("Slayer"))) {
                this->button->setStyleSheet("background-image: url(:/imgs/src/assets/enemies/enemies_full/slayer-1.png); \
                                            background-repeat: none; \
                                            background-position: bottom center; \
                                            background-attachment: fixed; \
                                            background-color: transparent;");
                // qDebug() << "Sorcerer" << "\n";
                return;
            }

            if (enemyName.contains(QString("Wolf"))) {
                this->button->setStyleSheet("background-image: url(:/imgs/src/assets/enemies/enemies_full/wolf-1.png); \
                                            background-repeat: none; \
                                            background-position: bottom center; \
                                            background-attachment: fixed; \
                                            background-color: transparent;");
                // qDebug() << "Sorcerer" << "\n";
                return;
            }
        }

    }
};

#endif // COMPONENTS_H
