#include "ui_widget.h"
#include "./lib/frontend/widget.h"
#include <./lib/gamemacros.h>
#include <QMovie>
#include <QPair>

// Variables only used in this file.
// Mainly Qt components that doesnt need to be defined in the class.
QMovie *movies[2];

// Auxiliary enum to identify each Qt StackedWidgets.
enum Screen {
    MENU,
    GAME
};

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

    // This is a test induced call of these functions, DELETE those for release.
    game->playerInstance->fireSkill.updateExp(5000);
    game->playerInstance->destructionSkill.updateExp(5000);

    initAllComponents();
    GENERATE_FIRST_ENEMY;
}

Widget::~Widget()
{
    delete this->game;
    delete this->enemyButton;
    delete this->healthBar;
    delete this->eventPanel;
    delete movies[0];
    delete movies[1];
    delete ui;
}

void Widget::startAnimationIcons()
{
    // Start Firball Attack Icon GIF.
    movies[0] = new QMovie(this);
    movies[0]->setFileName(":/imgs/src/assets/ui-components/ButtonEffectFire2.gif");
    connect(movies[0], &QMovie::frameChanged, [=]{
        ui->fireballIcon->setMovie(movies[0]);
    });
    movies[0]->setScaledSize(QSize(75, 75));
    movies[0]->start();

    // Start Destruction Aura Icon GIF.
    movies[1] = new QMovie(this);
    movies[1]->setFileName(":/imgs/src/assets/ui-components/ButtonEffectDestructionAura.gif");
    connect(movies[1], &QMovie::frameChanged, [=]{
        ui->destructionAuraIcon->setMovie(movies[1]);
    });
    movies[1]->setScaledSize(QSize(40, 40));
    movies[1]->start();
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
    connect(ui->exitGameButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->goUpButton, SIGNAL(clicked()), game, SLOT(nextFloor()));
    connect(ui->goDownButton, SIGNAL(clicked()), game, SLOT(previousFloor()));
    connect(ui->fireballUpgradeButton, SIGNAL(clicked()), game, SLOT(updateFireball()));
    connect(ui->destructionAuraUpgradeButton, SIGNAL(clicked()), game, SLOT(updateDestructionAura()));

    // TODO: Explain
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

void Widget::initAllComponents() {
    INIT_HEALTHBAR;
    INIT_ENEMYBUTTON;
    INIT_EVENTPANEL;
    INIT_LIESELINFO;

    QString a = "LEVEL " + QString::number(game->playerInstance->fireSkill.getLevel());
    QString b = QString::number(game->playerInstance->fireSkill.getLevelUp() - game->playerInstance->fireSkill.getExp()) + "IS NEEDED TO LEVEL UP";

    this->fireballInfo->initSkillInfo(qMakePair(ui->fireballLevelValue, a),
                                      qMakePair(ui->fireballCoinsNeededUpgrade, b));

    QString c = "LEVEL " + QString::number(game->playerInstance->destructionSkill.getLevel());
    QString d = QString::number(game->playerInstance->destructionSkill.getLevelUp() - game->playerInstance->destructionSkill.getExp()) + "IS NEEDED TO LEVEL UP";

    this->destructionAuraInfo->initSkillInfo(qMakePair(ui->destructionAuraLevelValue, c),
                                             qMakePair(ui->destructionAuraCoinsNeededUpgrade, d));
}

void Widget::setupGame() {
    // Instantiate Game
    this->game = new Game();
}

void Widget::setupMainWindow() {
    SET_WINDOW_FLAGS;
    SET_WINDOW_CENTERED;

    ui->stackedWidget->setCurrentIndex(MENU);
    startAnimationIcons();
}

void Widget::on_newGameButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(GAME);
}

void Widget::on_saveGoMenuButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(MENU);
}

