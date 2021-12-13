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
