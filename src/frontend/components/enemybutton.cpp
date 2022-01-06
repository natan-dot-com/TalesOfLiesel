#include <./lib/frontend/components/enemybutton.h>
#include <./lib/backend/enemy.h>
QPushButton *EnemyButton::hitbox;

QString getEnemyIconVersion(QString enemyName) {
    QString enemyAdjectIndex;
    for (int i = 0; i < 5; i++) {
        if (enemyName.contains(QString::fromStdString(adjectiveList[i]))) {
            enemyAdjectIndex = QString::number(i+1);
        }
    }

    QString enemyIconName = enemyAdjectIndex;

    srand(time(0));

    int version = rand() % 2 + 1;

    if (version == 2) {
        enemyIconName += "v2";
    }

    return enemyIconName;
}

EnemyButton::EnemyButton(QWidget *parent) : QObject(parent) {

}

void EnemyButton::initButton(QPushButton *_hitbox) {
    this->hitbox = _hitbox;
}

void EnemyButton::updateEnemyIcon(QString enemyName) {
    if (enemyName.contains(QString("Mage"))) {
        QString style = "background-image: url(:/imgs/src/assets/enemies/enemies_full/mage-" + getEnemyIconVersion(enemyName) + ".png);\n" +
                        "background-repeat: none; \
                        background-position: bottom center; \
                        background-attachment: fixed; \
                        background-color: transparent;";
        this->hitbox->setStyleSheet(style);
        // qDebug() << "Mage" << "\n";
        qDebug() << style << "\n";
        return;
    }

    if (enemyName.contains(QString("Elf"))) {
        QString style = "background-image: url(:/imgs/src/assets/enemies/enemies_full/elf-" + getEnemyIconVersion(enemyName) + ".png);\n" +
                        "background-repeat: none; \
                        background-position: bottom center; \
                        background-attachment: fixed; \
                        background-color: transparent;";
        this->hitbox->setStyleSheet(style);
        // qDebug() << "Elf" << "\n";
        qDebug() << style << "\n";
        return;
    }

    if (enemyName.contains(QString("Sorcerer"))) {
        QString style = "background-image: url(:/imgs/src/assets/enemies/enemies_full/sorcerer-" + getEnemyIconVersion(enemyName) + ".png);\n" +
                        "background-repeat: none; \
                        background-position: bottom center; \
                        background-attachment: fixed; \
                        background-color: transparent;";
        this->hitbox->setStyleSheet(style);
        // qDebug() << "Sorcerer" << "\n";
        qDebug() << style << "\n";
        return;
    }

    if (enemyName.contains(QString("Slayer"))) {
        QString style = "background-image: url(:/imgs/src/assets/enemies/enemies_full/slayer-" + getEnemyIconVersion(enemyName) + ".png);\n" +
                        "background-repeat: none; \
                        background-position: bottom center; \
                        background-attachment: fixed; \
                        background-color: transparent;";
        this->hitbox->setStyleSheet(style);
        // qDebug() << "Sorcerer" << "\n";
        qDebug() << style << "\n";
        return;
    }

    if (enemyName.contains(QString("Wolf"))) {
        QString style = "background-image: url(:/imgs/src/assets/enemies/enemies_full/wolf-" + getEnemyIconVersion(enemyName) + ".png);\n" +
                        "background-repeat: none; \
                        background-position: bottom center; \
                        background-attachment: fixed; \
                        background-color: transparent;";
        this->hitbox->setStyleSheet(style);
        // qDebug() << "Sorcerer" << "\n";
        qDebug() << style << "\n";
        return;
    }
}


