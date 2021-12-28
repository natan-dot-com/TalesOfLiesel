#include "./lib/frontend/mainwindow.h"
#include "./lib/frontend/game.h"
#include "ui_mainwindow.h"
#include "./lib/frontend/stylesheet.h"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_enemyButton_clicked()
{
    g->onDefaultDamage();
}

