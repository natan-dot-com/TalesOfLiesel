#include "./lib/mainwindow.h"
#include "ui_mainwindow.h"
#include "./lib/stylesheet.h"

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

