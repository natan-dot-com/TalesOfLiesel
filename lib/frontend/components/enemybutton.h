#ifndef ENEMYBUTTON_H
#define ENEMYBUTTON_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QString>

/*
 * Front end component that represents the QPushButton that represents
 * the hitbox where the enemy will be.
 *
 */

class EnemyButton : public QObject {
    Q_OBJECT

private:
    static QPushButton *hitbox;

public:
    EnemyButton(QWidget *parent = nullptr);
    virtual ~EnemyButton() {};

    void initButton(QPushButton *_hitbox);

public slots:
    // Changes the icon of the QPushButton
    // signal: enemyDead();
    // signal: enemySpawn();
    void updateEnemyIcon(QString name);
};

#endif // ENEMYBUTTON_H
