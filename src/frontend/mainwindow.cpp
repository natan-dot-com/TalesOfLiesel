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
    a = new ActiveComponents(
                ui->xpValue,
                ui->maxXP,
                ui->enemyName,
                ui->enemyMinHP,
                ui->enemyMaxHP,
                ui->Bar,
                ui->floorValue,
                ui->soulCoinsValue,
                ui->fireballCost,
                ui->chronomancyCost,
                ui->destructionAuraCost,
                ui->enemyButton,
                ui->fireballUpgradeButton,
                ui->chronomancyUpgradeButton,
                ui->destructionAuraUpgradeButton
                );

    this->g = new Game(a);
    g->setupGameStart();

    auto movie = new QMovie(this);
    movie->setFileName(":/imgs/src/assets/ui-components/ButtonEffectFire2.gif");
    connect(movie, &QMovie::frameChanged, [=]{
        ui->fireballIcon->setMovie(movie);
    });
    movie->setScaledSize(QSize(75, 75));
    movie->start();

    auto movie2 = new QMovie(this);
    movie2->setFileName(":/imgs/src/assets/ui-components/ButtonEffectDestructionAura.gif");
    connect(movie2, &QMovie::frameChanged, [=]{
        ui->destructionAuraIcon->setMovie(movie2);
    });
    movie2->setScaledSize(QSize(50, 50));
    movie2->start();

    auto movie3 = new QMovie(this);
    movie3->setFileName(":/imgs/src/assets/ui-components/ButtonEffectChrono1.gif");
    connect(movie3, &QMovie::frameChanged, [=]{
        ui->chronomancyIcon->setMovie(movie3);
    });
    movie3->setScaledSize(QSize(50, 50));
    movie3->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_enemyButton_clicked()
{
    g->onDefaultDamage();
}


void MainWindow::on_fireballUpgradeButton_clicked()
{

}


void MainWindow::on_lowerFloorButton_clicked()
{
    g->context->previousFloor();
    g->updateLieselInfo();
    g->updateEnemyInfo();
    g->updateEnemyButton();
}


void MainWindow::on_higherFloorButton_clicked()
{
    g->context->nextFloor();
    g->updateLieselInfo();
    g->updateEnemyInfo();
    g->updateEnemyButton();
}
