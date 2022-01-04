#include "./lib/frontend/mainwindow.h"
#include "./lib/frontend/game.h"
#include "ui_mainwindow.h"
#include "./lib/frontend/stylesheet.h"
#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()                                |
                   Qt::CustomizeWindowHint                      |
                   Qt::WindowMinimizeButtonHint                 |
                   Qt::WindowMaximizeButtonHint                 |
                   Qt::WindowCloseButtonHint);
    a = new ActiveComponents(
        ui->lieselCurrentLevelExp,
        ui->lieselLevelMax,
        ui->enemyName,
        ui->healthBar,
        ui->lieselFloorValue,
        ui->lieselSoulCoinsValue,
        ui->fireballPriceValue,
        ui->chronomancyPriceValue,
        ui->destructionAuraPriceValue,
        ui->damageIndicator,
        ui->enemyButton,
        ui->fireballUpgradeButton,
        ui->chronomancyUpgradeButton,
        ui->destructionAuraUpgradeButton
    );

    this->g = new Game(this, a);
    g->setupGameStart();

//    // Fix this.
//    QMovie *movie = new QMovie(this);
//    movie->setFileName(":/imgs/src/assets/ui-components/ButtonEffectFire2.gif");
//    connect(movie, &QMovie::frameChanged, [=]{
//        ui->fireballIcon->setMovie(movie);
//    });
//    movie->setScaledSize(QSize(75, 75));
//    movie->start();

//    auto movie2 = new QMovie(this);
//    movie2->setFileName(":/imgs/src/assets/ui-components/ButtonEffectDestructionAura.gif");
//    connect(movie2, &QMovie::frameChanged, [=]{
//        ui->destructionAuraIcon->setMovie(movie2);
//    });
//    movie2->setScaledSize(QSize(50, 50));
//    movie2->start();

//    auto movie3 = new QMovie(this);
//    movie3->setFileName(":/imgs/src/assets/ui-components/ButtonEffectChrono1.gif");
//    connect(movie3, &QMovie::frameChanged, [=]{
//        ui->chronomancyIcon->setMovie(movie3);
//    });
//    movie3->setScaledSize(QSize(50, 50));
//    movie3->start();
//    this->centralWidget()->setStyleSheet("background-color: transparent;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_enemyButton_clicked()
{
    Game::context->evokeDamageOnClick();
}

void MainWindow::on_destructionAuraUseButton_clicked()
{
    Game::context->evokeDestructionAura();
}

