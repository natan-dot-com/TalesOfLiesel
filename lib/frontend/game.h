#ifndef GAME_H
#define GAME_H

#include <mutex>
#include <QMovie>
#include <./lib/backend/ctx.h>
#include <./lib/frontend/components.h>

class Game {
private:
    bool isDefaultDamage = true;
    bool isFireballCasted = false;
    bool isChronomancyActive = false;

public:
    // TODO: Remember to 'delete'/dealocate those.
    static Context *context;
    static ActiveComponents *activeComponents;
    static EnemyInformation *eInfo;
    static EnemyButton *eButton;
    static LieselInformation *lInfo;
    static Healthbar *healthBar;
    static QObject *parent;

    Game(QObject *, ActiveComponents *_activeComponents);

    static void setupGameStart();
    static void updateGame();
    static void updateLieselInfo();
    static void updateEnemyInfo();
    static void updateEnemyButton();
};

#endif // GAME_H
