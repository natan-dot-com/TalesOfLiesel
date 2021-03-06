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

#define CD_CLICK_MILIS 100
#define CD_FIREBALL_MILIS 10000
#define CD_DESTAURA_MILIS 20000
#define DELAY_DESTAURA_DOT_SECS 1
#define DESTAURA_DOT_TICKS 6

#define FIREBALL_THREAD_ID 1000
#define DESTAURA_THREAD_ID 1001

/**
 * Struct that represents an instance of a thread.
 *
 */
typedef struct _ThreadInstance {
    std::thread currThread;
    std::atomic<bool> executionFlag;
    int threadID;


    _ThreadInstance(int _threadID = -1) {
        this->threadID = _threadID;
        this->executionFlag = false;
    }

    void toggleUsage() {
        this->executionFlag = !this->executionFlag;
    }

    bool isInUse() {
        return this->executionFlag;
    }
} ThreadInstance;

/**
 * Main backend class with all classes that make the game logic.
 * Basically, it has all the multithreaded resources and
 * calls the Qt framework signals when needed.
 *
 */

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
    bool proccessMonsterDamage(const double dealtDamage, int &gainedExp, int &gainedCoins, bool &isLevelUp);
    void damageDestructionAura();

public:
    Game(QWidget *parent = nullptr);
    ~Game();

    Liesel *playerInstance;
    Enemy *currEnemyInstance;

    // This function will have lots of IF's to check game state and emit signals to
    // components if needed.
    void checkInstance();

    // @emit: spawnEnemy
    void generateEnemy(QString name);

    // @emit: defaultDamage;
    void onDefaultDamage(int current, int max);

    // @emit: fireballDamage;
    void onFireballDamage(int current, int max);

    // @emit: destructionAuraDamage;
    void onDestructionAuraDamage(int current, int max);

    int getCurrentFloor();

public slots:
    // Damage/skills related methods
    void evokeDamageOnClick();
    void evokeFireball();
    void evokeDestructionAura();

    // Skills management
    bool updateFireball();
    bool updateDestructionAura();

    // Floor management
    void nextFloor();
    void previousFloor();


signals:
    void toggleDestructionAuraButton(bool);
    void toggleFireballButton(bool);
    void updateFireballInfo(QString, QString);
    void updateDestructionAuraInfo(QString, QString);
    void updateLieselInfo(QString, QString, QString, QString, QString);
    void changeEnemyName(QString name);
    void updateEventFeed(QString event);
    void updateHealthBar(int current, int max);

    /* STAYING FOR LEGACY OR IF I CHANGE MY MIND */
    /* PROBABLY WON'T USE THIS */

    // @sender: backend
    // @reciever: EnemyButton
    // @slot: updateEnemyIcon
    // @function: generateEnemy();
    void spawnEnemy(QString name);
};

#endif // GAME_H
