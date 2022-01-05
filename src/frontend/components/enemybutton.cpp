#include <./lib/frontend/components/enemybutton.h>

QPushButton *EnemyButton::hitbox;

EnemyButton::EnemyButton(QWidget *parent) : QObject(parent) {

}

void EnemyButton::initButton(QPushButton *_hitbox) {
    this->hitbox = _hitbox;
}

void EnemyButton::updateEnemyIcon(QString *enemyName) {
    if (enemyName->contains(QString("Mage"))) {
        this->hitbox->setStyleSheet("background-image: url(:/imgs/src/assets/enemies/enemies_full/mage-1.png); \
                                    background-repeat: none; \
                                    background-position: bottom center; \
                                    background-attachment: fixed; \
                                    background-color: transparent;");
        // qDebug() << "Mage" << "\n";
        return;
    }

    if (enemyName->contains(QString("Elf"))) {
        this->hitbox->setStyleSheet("background-image: url(:/imgs/src/assets/enemies/enemies_full/elf-1.png); \
                                    background-repeat: none; \
                                    background-position: bottom center; \
                                    background-attachment: fixed; \
                                    background-color: transparent;");
        // qDebug() << "Elf" << "\n";
        return;
    }

    if (enemyName->contains(QString("Sorcerer"))) {
        this->hitbox->setStyleSheet("background-image: url(:/imgs/src/assets/enemies/enemies_full/sorcerer-1.png); \
                                    background-repeat: none; \
                                    background-position: bottom center; \
                                    background-attachment: fixed; \
                                    background-color: transparent;");
        // qDebug() << "Sorcerer" << "\n";
        return;
    }

    if (enemyName->contains(QString("Slayer"))) {
        this->hitbox->setStyleSheet("background-image: url(:/imgs/src/assets/enemies/enemies_full/slayer-1.png); \
                                    background-repeat: none; \
                                    background-position: bottom center; \
                                    background-attachment: fixed; \
                                    background-color: transparent;");
        // qDebug() << "Sorcerer" << "\n";
        return;
    }

    if (enemyName->contains(QString("Wolf"))) {
        this->hitbox->setStyleSheet("background-image: url(:/imgs/src/assets/enemies/enemies_full/wolf-1.png); \
                                    background-repeat: none; \
                                    background-position: bottom center; \
                                    background-attachment: fixed; \
                                    background-color: transparent;");
        // qDebug() << "Sorcerer" << "\n";
        return;
    }
}


