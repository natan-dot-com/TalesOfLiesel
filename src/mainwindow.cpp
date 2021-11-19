#include "./lib/mainwindow.h"
#include "ui_mainwindow.h"
#include "./ui/stylesheet.h"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_upgradeAButton_clicked()
{
    if (upgradeA.upgradeValue < 10)
        ui->upgradeAProgress->setValue(upgradeA.upgradeValue++);
    else
        ui->status->setText(
            h1(Comando Indisponivel)
        );
}


void MainWindow::on_Monster_clicked()
{
    ui->status->setText(QString::fromStdString("<h1>" + std::to_string(monsterHealth--) + "</h1>"));
}

