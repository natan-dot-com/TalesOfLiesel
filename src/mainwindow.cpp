#include "./lib/mainwindow.h"
#include "ui_mainwindow.h"
#include "./lib/stylesheet.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->upgradeAProgress->setValue(0);
    ui->upgradeBProgress->setValue(0);
    ui->upgradeCProgress->setValue(0);
    ui->upgradeDProgress->setValue(0);
    ui->upgradeEProgress->setValue(0);
    ui->MonsterHealth->setValue(100);
    ui->MonsterHealth->setTextVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_upgradeAButton_clicked()
{
    if (upgradeA.upgradeValue < 101)
        ui->upgradeAProgress->setValue(upgradeA.upgradeValue++);
}


void MainWindow::on_Monster_clicked()
{
    if (monsterHealth) {
        monsterHealth -= 500;
        // Set value relies on percentage.
        ui->MonsterHealth->setValue((100 * monsterHealth)/2000);
    }

}

