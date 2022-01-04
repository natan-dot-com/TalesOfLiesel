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
    static std::mutex mutex;

public:
    // TODO: Remember to 'delete'/dealocate those.
    Context *context;
    ActiveComponents *activeComponents;
    EnemyInformation *eInfo;
    EnemyButton *eButton;
    LieselInformation *lInfo;
    Healthbar *healthBar;
    QObject *parent;

    Game(QObject *, ActiveComponents *_activeComponents);

    void setupGameStart();
    void onDefaultDamage();
    void onFireballDamage();
    void onChronomancy();
    void updateLieselInfo();
    void updateEnemyInfo();
    void updateEnemyButton();
};

#endif // GAME_H
