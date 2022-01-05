#include <./lib/Game.h>

Game::Game(QWidget *parent) : QObject(parent){

}

void Game::generateEnemy(QString *name) {
    emit spawnEnemy(name);
}
