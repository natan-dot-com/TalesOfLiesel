#ifndef ENEMYBUTTON_H
#define ENEMYBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QString>

class EnemyButton : public QObject {
    Q_OBJECT

private:
    static QPushButton *hitbox;

signals:
    void damaged();

public:
    EnemyButton(QWidget *parent = nullptr);
    virtual ~EnemyButton() {};

    void initButton(QPushButton *_hitbox);

public slots:
    // Changes the icon of the QPushButton
    // signal: enemyDead();
    // signal: enemySpawn();
    void updateEnemyIcon(QString *name);
};

#endif // ENEMYBUTTON_H
