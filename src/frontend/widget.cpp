#include "ui_widget.h"
#include "./lib/frontend/widget.h"
#include <./lib/gamemacros.h>
#include <QMovie>
#include <QPair>
#include <QMediaPlayer>
#include <QMediaPlaylist>

// Auxiliary enum to identify each Qt QMovies.
enum QMovies {
    FIREBALL_ICON,
    DESTAURA_ICON
};

// Auxiliary enum to identify each Qt StackedWidgets.
enum Screen {
    MENU,
    GAME
};

// Variables only used in this file.
// Mainly Qt components that doesnt need to be defined in the class.
QMovie *movies[2];
QMediaPlayer *title;
QMediaPlayer *gameplay;
QMediaPlaylist *gamePlaylist;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setupMainWindow(); // Must come first!
    setupHealthbar();
    setupEnemyButton();
    setupEventPanel();
    setupLieselInfo();
    setupFireballInfo();
    setupDestructionAuraInfo();
    setupGame();
    connectAll();
    setupMusic();
    initAllComponents();

    GENERATE_FIRST_ENEMY;
}

Widget::~Widget()
{
    delete title;
    delete gameplay;
    delete gamePlaylist;
    delete this->game;
    delete this->enemyButton;
    delete this->healthBar;
    delete this->eventPanel;
    delete this->fireballInfo;
    delete this->destructionAuraInfo;
    delete movies[FIREBALL_ICON];
    delete movies[DESTAURA_ICON];
    delete ui;
}

void Widget::setupMusic() {
    title = new QMediaPlayer();
    gameplay = new QMediaPlayer();
    gamePlaylist = new QMediaPlaylist();

    title->setMedia(QUrl("qrc:/music/music/0-tavern.mp3"));
    title->play();
    title->setVolume(25);
    gameplay->setVolume(25);

    gamePlaylist->addMedia(QUrl("qrc:/music/music/1-highland.mp3"));
    gamePlaylist->addMedia(QUrl("qrc:/music/music/2-streets-of-plague.mp3"));
    gamePlaylist->addMedia(QUrl("qrc:/music/music/3-battle-of-the-creek.mp3"));
    gamePlaylist->addMedia(QUrl("qrc:/music/music/4-medieval.mp3"));

    gamePlaylist->setPlaybackMode(QMediaPlaylist::Loop);
    gameplay->setPlaylist(gamePlaylist);
}

void Widget::startAnimationIcons()
{
    // Start Firball Attack Icon GIF.
    movies[FIREBALL_ICON] = new QMovie(this);
    movies[FIREBALL_ICON]->setFileName(":/imgs/src/assets/ui-components/ButtonEffectFire2.gif");
    connect(movies[FIREBALL_ICON], &QMovie::frameChanged, [=]{
        ui->fireballIcon->setMovie(movies[FIREBALL_ICON]);
    });
    movies[FIREBALL_ICON]->setScaledSize(QSize(75, 75));
    movies[FIREBALL_ICON]->start();

    // Start Destruction Aura Icon GIF.
    movies[DESTAURA_ICON] = new QMovie(this);
    movies[DESTAURA_ICON]->setFileName(":/imgs/src/assets/ui-components/ButtonEffectDestructionAura.gif");
    connect(movies[DESTAURA_ICON], &QMovie::frameChanged, [=]{
        ui->destructionAuraIcon->setMovie(movies[DESTAURA_ICON]);
    });
    movies[DESTAURA_ICON]->setScaledSize(QSize(40, 40));
    movies[DESTAURA_ICON]->start();
}

void Widget::connectAll() {

    // spawnEnemy signal triggers both a update on the enemy icon and label.
    connect(game, SIGNAL(spawnEnemy(QString)), healthBar, SLOT(updateEnemyLabel(QString)));
    connect(game, SIGNAL(spawnEnemy(QString)), enemyButton, SLOT(updateEnemyIcon(QString)));

    // updateLieselInfo signal triggers and update on the UI part that tells liesel's level, xp and coins.
    connect(game, SIGNAL(updateLieselInfo(QString,QString,QString,QString,QString)),
            lieselInfo, SLOT(updateLieselInfoLabels(QString,QString,QString,QString,QString)));

    // updateHealthBar signal triggers a update to the UI part that tells the enemy health.
    connect(game, SIGNAL(updateHealthBar(int,int)), healthBar, SLOT(updateBarOnDamage(int,int)));

    // updateEventFeed signal triggers a update to the game event feed.
    connect(game, SIGNAL(updateEventFeed(QString)), eventPanel, SLOT(addEventOnFeed(QString)));

    // Button based signals that are pretty self explanatory.
    connect(ui->enemyButton, SIGNAL(clicked()), game, SLOT(evokeDamageOnClick()));
    connect(ui->fireballUseButton, SIGNAL(clicked()), game, SLOT(evokeFireball()));
    connect(ui->destructionAuraUseButton, SIGNAL(clicked()), game, SLOT(evokeDestructionAura()));
    connect(game, SIGNAL(toggleFireballButton(bool)), ui->fireballUseButton, SLOT(setEnabled(bool)));
    connect(game, SIGNAL(toggleDestructionAuraButton(bool)), ui->destructionAuraUseButton, SLOT(setEnabled(bool)));
    connect(ui->exitGameButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->goUpButton, SIGNAL(clicked()), game, SLOT(nextFloor()));
    connect(ui->goDownButton, SIGNAL(clicked()), game, SLOT(previousFloor()));
    connect(ui->fireballUpgradeButton, SIGNAL(clicked()), game, SLOT(updateFireball()));
    connect(ui->destructionAuraUpgradeButton, SIGNAL(clicked()), game, SLOT(updateDestructionAura()));

    // backend sending signals to UI components
    connect(game, SIGNAL(updateFireballInfo(QString,QString)), fireballInfo, SLOT(updateSkillInfoLabels(QString,QString)));
    connect(game, SIGNAL(updateDestructionAuraInfo(QString,QString)), destructionAuraInfo, SLOT(updateSkillInfoLabels(QString,QString)));
}

void Widget::setupHealthbar() {
    this->healthBar = new Healthbar(this);
}

void Widget::setupEnemyButton() {
    this->enemyButton = new EnemyButton(this);
}

void Widget::setupEventPanel() {
    this->eventPanel = new EventPanel(this);
}

void Widget::setupLieselInfo() {
    this->lieselInfo = new LieselInfo(this);
}

void Widget::setupFireballInfo() {
    this->fireballInfo = new SkillInfo(this);
}

void Widget::setupDestructionAuraInfo() {
    this->destructionAuraInfo = new SkillInfo(this);
}

void Widget::setupGame() {
    this->game = new Game();
}

void Widget::setupMainWindow() {
    SET_WINDOW_FLAGS;
    SET_WINDOW_CENTERED;

    ui->stackedWidget->setCurrentIndex(MENU);
    startAnimationIcons();
}

void Widget::initAllComponents() {
    INIT_HEALTHBAR;
    INIT_ENEMYBUTTON;
    INIT_EVENTPANEL;
    INIT_LIESELINFO;

    GENERATE_FIREBALL_INIT_LABELS;
    INIT_FIREBALL_INFO;

    GENERATE_DESTAURA_INIT_LABELS;
    INIT_DESTAURA_INFO;
}

void Widget::on_newGameButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(GAME);
    title->stop();
    gamePlaylist->shuffle();
    gameplay->play();
}

void Widget::on_saveGoMenuButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(MENU);
    gameplay->stop();
    title->play();
}


void Widget::on_exitGameButton_clicked()
{
    this->close();
}

