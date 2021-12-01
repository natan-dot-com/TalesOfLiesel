#include "./lib/frontend/mainwindow.h"
#include "ui_mainwindow.h"
#include "./lib/frontend/stylesheet.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_giveLevelButton_clicked()
{
    liesel->updateExp(1);
    ui->levelValue->setText(QString::number(liesel->getExp()));
}


void MainWindow::on_pushButton_clicked()
{
    enemy->inflictDamage(5);
    float currentHP = (float)enemy->getCurrHP()/(float)enemy->getMaxHP();
    ui->Bar->setFixedWidth((int)(currentHP * ui->Bar->width()));
}
