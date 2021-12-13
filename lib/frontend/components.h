#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <QGraphicsItem>
#include <QLabel>
#include <QIcon>
#include <QPushButton>
#include <./lib/backend/enemy.h>

struct Healthbar {
    int barWidth;
    QString defaultStyle;
    QLabel *Bar;

    Healthbar() {

    }

    Healthbar(int _barWidth, QString _defaultStyle) {
        barWidth = _barWidth;
        defaultStyle = _defaultStyle;
    }

    float getDamagedRatio(float current, float max) {
        return current/max;
    }

    void updateBar(QLabel *_Bar, Enemy *e) {
        switch(e->getCurrHP()) {
            case 51 ... 75:
                _Bar->setStyleSheet(
                    "border-radius: \
                        3px; \
                     background-color: \
                        QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #bee25b, stop: .5 #a1d54f, stop: .51 #729818, stop: 1 #7cbc0a);"
                );
            break;

            case 26 ... 50:
                _Bar->setStyleSheet(
                    "border-radius: \
                        3px; \
                     background-color: \
                        QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dea801, stop: .5 #ffcf3b, stop: .51 #957107, stop: 1 #715e28);"
                );
             break;

            case 0 ... 25:
                _Bar->setStyleSheet(
                    "border-radius: \
                        3px; \
                     background-color: \
                        QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #bb5107, stop: .5 #f5873b, stop: .51 #973b00, stop: 1 #553521);"
                );
             break;
        }
    }

    void resetBar(QLabel *_Bar) {
        _Bar->setStyleSheet(defaultStyle);
        _Bar->setFixedWidth(barWidth);
    }
};

struct EnemyButton {
    QIcon enemyIcon;

    EnemyButton() {

    }

    // "Mage",
    // "Wolf",
    // "Sorcerer",
    // "Slayer",
    // "Elf",
    void updateEnemyIcon(Enemy *e, QPushButton *p) {
        QString enemyName = QString::fromStdString(e->getMobName());

        if (enemyName.contains(QString("Mage"))) {
            p->setIcon(QIcon(":/imgs/src/assets/enemies/enemies_full/mage-1.png"));
            p->setIconSize(QSize(600, 600));
            // qDebug() << "Mage" << "\n";
            return;
        }

        if (enemyName.contains(QString("Elf"))) {
            p->setIcon(QIcon(":/imgs/src/assets/enemies/enemies_full/elf-1.png"));
            p->setIconSize(QSize(600, 600));
            // qDebug() << "Elf" << "\n";
            return;
        }

        if (enemyName.contains(QString("Sorcerer"))) {
            p->setIcon(QIcon(":/imgs/src/assets/enemies/enemies_full/sorcerer-1.png"));
            p->setIconSize(QSize(600, 600));
            // qDebug() << "Sorcerer" << "\n";
            return;
        }

        if (enemyName.contains(QString("Slayer"))) {
            p->setIcon(QIcon(":/imgs/src/assets/enemies/enemies_full/slayer-1.png"));
            p->setIconSize(QSize(600, 600));
            // qDebug() << "Sorcerer" << "\n";
            return;
        }

        if (enemyName.contains(QString("Wolf"))) {
            p->setIcon(QIcon(":/imgs/src/assets/enemies/enemies_full/wolf-1.png"));
            p->setIconSize(QSize(600, 600));
            // qDebug() << "Sorcerer" << "\n";
            return;
        }
    }
};

#endif // COMPONENTS_H
