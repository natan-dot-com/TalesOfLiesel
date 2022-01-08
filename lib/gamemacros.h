#ifndef GAMEMACROS_H
#define GAMEMACROS_H

/* -- SIGNAL RELATED MACROS -- */

// MACRO PAIR
// Macro to get a string with the type of the damage and the QString with the value.
#define GENERATE_TYPE_DAMAGE_EVENT(TYPE)    QString event = TYPE + QString::number(dealtDamage)
#define EMIT_CLICK_DAMAGE_FEED              updateEventFeed(event)

#define GENERATE_FIREBALL_INIT_LABELS       QString a = "LEVEL " + QString::number(game->playerInstance->fireSkill.getLevel()); \
                                            QString b = QString::number(game->playerInstance->fireSkill.getLevelUp() - game->playerInstance->fireSkill.getExp()) + " IS NEEDED TO LEVEL UP"

#define INIT_FIREBALL_INFO                  this->fireballInfo->initSkillInfo(qMakePair(ui->fireballLevelValue, a), \
                                             qMakePair(ui->fireballCoinsNeededUpgrade, b))

#define GENERATE_DESTAURA_INIT_LABELS       QString c = "LEVEL " + QString::number(game->playerInstance->destructionSkill.getLevel()); \
                                            QString d = QString::number(game->playerInstance->destructionSkill.getLevelUp() - game->playerInstance->destructionSkill.getExp()) + " IS NEEDED TO LEVEL UP"

#define INIT_DESTAURA_INFO                  this->destructionAuraInfo->initSkillInfo(qMakePair(ui->destructionAuraLevelValue, c), \
                                            qMakePair(ui->destructionAuraCoinsNeededUpgrade, d))

// MACRO PAIR
#define FIREBALL a,b
#define DESTAURA c,d

#define GENERATE_FIREBALL_INFO_LABELS       QString a = "LEVEL " + QString::number(this->playerInstance->fireSkill.getLevel()); \
                                            QString b = QString::number(this->playerInstance->fireSkill.getLevelUp() - this->playerInstance->fireSkill.getExp()) + " IS NEEDED TO LEVEL UP"

#define GENERATE_DESTAURA_INFO_LABELS       QString c = "LEVEL " + QString::number(this->playerInstance->destructionSkill.getLevel()); \
                                            QString d = QString::number(this->playerInstance->destructionSkill.getLevelUp() - this->playerInstance->destructionSkill.getExp()) + " IS NEEDED TO LEVEL UP"

#define EMIT_UPDATE_FIREBALL_INFO(X)        updateFireballInfo(X)
#define EMIT_UPDATE_DESTAURA_INFO(X)        updateDestructionAuraInfo(X)

// SELF EXPLANATORY EMIT MACROS
#define EMIT_SPAWN_NEW_ENEMY                spawnEnemy(QString::fromStdString(this->currEnemyInstance->getMobName()))
#define EMIT_TEMPLATE_PHRASE(X)             updateEventFeed(QString::fromStdString(GamePhrases::gameEventPhrases[X]))
#define EMIT_UPDATE_HEALTHBAR               updateHealthBar(this->currEnemyInstance->getCurrHP(), this->currEnemyInstance->getMaxHP())
#define EMIT_UPDATE_LIESEL_INFO             updateLieselInfo(QString::number(getCurrentFloor()), \
                                            QString::number(playerInstance->getLevel()), \
                                            QString::number(playerInstance->getExp()), \
                                            QString::number(playerInstance->getLevelUp()), \
                                            QString::number(playerInstance->getSoulCoins()))

#define GENERATE_FIRST_ENEMY                game->generateEnemy(QString::fromStdString(game->currEnemyInstance->getMobName()))



/* -- FRONTEND RELATED MACROS -- */

// INITIALIZE HEALTHBAR
#define INIT_HEALTHBAR                      this->healthBar->initHealthbar(ui->enemyName, \
                                            QString::fromStdString(game->currEnemyInstance->getMobName()), \
                                            ui->healthBar, \
                                            game->currEnemyInstance->getCurrHP(), \
                                            game->currEnemyInstance->getMaxHP())

// INITIALIZE ENEMY BUTTON
#define INIT_ENEMYBUTTON                    this->enemyButton->initButton(ui->enemyButton);

// INITIALIZE EVENT FEED
#define INIT_EVENTPANEL                     this->eventPanel->initEventPanel(ui->eventList);

// INITIALIZE LIESEL INFO
#define INIT_LIESELINFO                     this->lieselInfo->initLieselInfo(qMakePair(ui->lieselFloorValue, QString::number(game->getCurrentFloor())), \
                                            qMakePair(ui->lieselCurrentLevelValue, QString::number(game->playerInstance->getLevel())), \
                                            qMakePair(ui->lieselCurrentLevelExp, QString::number(game->playerInstance->getExp())), \
                                            qMakePair(ui->lieselLevelMax, QString::number(game->playerInstance->getLevelUp())), \
                                            qMakePair(ui->lieselSoulCoinsValue, QString::number(game->playerInstance->getSoulCoins())))


/* -- QT RELATED MACROS -- */

#define SET_WINDOW_FLAGS                    setWindowFlags(windowFlags()                                | \
                                            Qt::CustomizeWindowHint                                     | \
                                            Qt::WindowMinimizeButtonHint                                | \
                                            Qt::WindowMaximizeButtonHint                                | \
                                            Qt::WindowCloseButtonHint)

#define SET_WINDOW_CENTERED                 move(QGuiApplication::screens().at(0)->geometry().center() - frameGeometry().center())

#endif // GAMEMACROS_H
