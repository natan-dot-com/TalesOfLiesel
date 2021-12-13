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

    void resetBar(QLabel *_Bar) {
        _Bar->setStyleSheet(defaultStyle);
        _Bar->setFixedWidth(barWidth);
    }
};

struct EnemyButton {
    QPixmap *enemyImage = NULL;
    QIcon *enemyIcon = NULL;

    EnemyButton() {

    }

    // "Mage",
    // "Wolf",
    // "Sorcerer",
    // "Slayer",
    // "Elf",
    void updateEnemyIcon(Enemy *e, QPushButton *p) {
        QString enemyName = e->getMobName();

        if (enemyImage != NULL) {
            delete enemyImage;
        }

        if (enemyName.contains(QString("Mage"))) {
//            enemyImage = new QPixmap(":/imgs/src/assets/enemies/enemies_full/mage-1.png");
//            p->setIcon(QIcon(*enemyImage));
            qDebug() << "Mage" << "\n";
            return;
        }

        if (enemyName.contains(QString("Elf"))) {
//            enemyImage = new QPixmap(":/imgs/src/assets/enemies/enemies_full/elf-1.png");
//            p->setIcon(QIcon(*enemyImage));
            qDebug() << "Elf" << "\n";
            return;
        }

        if (enemyName.contains(QString("Sorcerer"))) {
//            enemyImage = new QPixmap(":/imgs/src/assets/enemies/enemies_full/sorcerer-1.png");
//            p->setIcon(QIcon(*enemyImage));
            qDebug() << "Sorcerer" << "\n";
            return;
        }
    }
};

#endif // COMPONENTS_H
