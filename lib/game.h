#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <./lib/backend/liesel.h>
#include <./lib/backend/enemy.h>
#include <./lib/backend/error_handling.h>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>

#define CD_CLICK_MILIS 500
#define CD_FIREBALL_MILIS 10000
#define CD_DESTAURA_MILIS 20000
#define DELAY_DESTAURA_DOT_SECS 1
#define DESTAURA_DOT_TICKS 6

typedef struct _ThreadInstance {
    std::thread currThread;
    std::atomic<bool> executionFlag;

    _ThreadInstance() {
        this->executionFlag = false;
    }

    void toggleUsage() {
        this->executionFlag = !this->executionFlag;
    }

    bool isInUse() {
        return this->executionFlag;
    }
} ThreadInstance;

class Game : public QObject {
    Q_OBJECT

private:
    ThreadInstance *clickExec;
    ThreadInstance *fireballExec;
    ThreadInstance *destAuraExec;
    ThreadInstance *destAuraDmg;

    std::mutex healthBarMut;

    int currFloor;

    void startCooldown(ThreadInstance *cooldownThread, const int timeAmount);
    bool proccessMonsterDamage(const int dealtDamage, int &gainedExp, int &gainedCoins, bool &isLevelUp);
    void damageDestructionAura();

public:
    Game(QWidget *parent = nullptr);
    ~Game();

    Liesel *playerInstance;
    Enemy *currEnemyInstance;

    void callUpdateBar(int current, int max);

    // This function will have lots of IF's to check game state and emit signals to
    // components if needed.
    void checkInstance();

    // @emit: spawnEnemy
    void generateEnemy(QString *name);

    // @emit: defaultDamage;
    void onDefaultDamage(int current, int max);

    // @emit: fireballDamage;
    void onFireballDamage(int current, int max);

    // @emit: destructionAuraDamage;
    void onDestructionAuraDamage(int current, int max);

public slots:
    void evokeDamageOnClick();
    void evokeFireball();
    void evokeDestructionAura();

signals:
    void updateHealthBar(int current, int max);

    // @sender: backend
    // @reciever: EnemyButton
    // @slot: updateEnemyIcon
    // @function: generateEnemy();
    void spawnEnemy(QString *name);

    // @sender: backend
    // @reciever: Healthbar
    // @slot: updateBarOnDamage
    // @function: onDefaultDamage();
    void defaultDamage(int current, int max);

    // @sender: backend
    // @reciever: Healthbar
    // @slot: updateBarOnDamage
    // @function: onFireballDamage();
    void fireballDamage(int current, int max);

    // @sender: backend
    // @reciever: Healthbar
    // @slot: updateBarOnDamage
    // @function: onDestructionAuraDamage();
    void destructionAuraDamage(int current, int max);
};

#endif // GAME_H
