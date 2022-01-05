#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QWidget>
#include <QString>

class Game : public QObject {
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    virtual ~Game() {};

    void generateEnemy(QString *name);
signals:
    void spawnEnemy(QString *name);
};

#endif // GAME_H
