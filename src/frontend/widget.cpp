#include "ui_widget.h"
#include "./lib/frontend/widget.h"
#include <QMovie>

enum Screen {
    MENU,
    GAME
};

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // setupGame must come last!
    setupMainWindow();
    setupEnemyButton();
    setupGame();
    setupHealthbar(game->currEnemyInstance->getCurrHP(), game->currEnemyInstance->getMaxHP());
    connectAll();

    game->playerInstance->fireSkill.updateExp(5000);
    game->playerInstance->destructionSkill.updateExp(5000);
}

Widget::~Widget()
{
    delete ui->enemyButton;
    delete this->game;
    delete ui->healthBar;
    delete ui;
}

/* TODO: Deallocate QMovie */
void Widget::startAnimationIcons()
{
    QMovie *movie = new QMovie(this);
    movie->setFileName(":/imgs/src/assets/ui-components/ButtonEffectFire2.gif");
    connect(movie, &QMovie::frameChanged, [=]{
        ui->fireballIcon->setMovie(movie);
    });
    movie->setScaledSize(QSize(75, 75));
    movie->start();

    QMovie *movie2 = new QMovie(this);
    movie2->setFileName(":/imgs/src/assets/ui-components/ButtonEffectDestructionAura.gif");
    connect(movie2, &QMovie::frameChanged, [=]{
        ui->destructionAuraIcon->setMovie(movie2);
    });
    movie2->setScaledSize(QSize(40, 40));
    movie2->start();
}

void Widget::connectAll() {
    connect(game, SIGNAL(updateHealthBar(int,int)), healthBar, SLOT(updateBarOnDamage(int,int)));
    connect(ui->enemyButton, SIGNAL(clicked()), game, SLOT(evokeDamageOnClick()));
    connect(ui->fireballUseButton, SIGNAL(clicked()), game, SLOT(evokeFireball()));
    connect(ui->destructionAuraUseButton, SIGNAL(clicked()), game, SLOT(evokeDestructionAura()));
}

void Widget::setupEnemyButton() {
    this->enemyButton = new EnemyButton(this);
    this->enemyButton->initButton(ui->enemyButton);
}

void Widget::setupHealthbar(int current, int max) {
    this->healthBar = new Healthbar(this);
    this->healthBar->initHealthbar(ui->healthBar, current, max);

    // connect(ui->enemyButton, SIGNAL(clicked()), healthBar, SLOT(updateBar()), Qt::QueuedConnection);
}



void Widget::setupGame() {
    // Instantiate Game
    this->game = new Game();

    connect(game, SIGNAL(spawnEnemy(QString*)), enemyButton, SLOT(updateEnemyIcon(QString*)), Qt::QueuedConnection);
    QString *name = new QString("Sorcerer");
    game->generateEnemy(name);
}

void Widget::setupMainWindow() {
    setWindowFlags(windowFlags()                                |
                   Qt::CustomizeWindowHint                      |
                   Qt::WindowMinimizeButtonHint                 |
                   Qt::WindowMaximizeButtonHint                 |
                   Qt::WindowCloseButtonHint);
    move(QGuiApplication::screens().at(0)->geometry().center() - frameGeometry().center());
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

