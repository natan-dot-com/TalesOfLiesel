#include "./lib/frontend/mainwindow.h"
#include "ui_mainwindow.h"
#include "./lib/frontend/stylesheet.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    h.defaultStyle = ui->Bar->styleSheet();
    h.barWidth = ui->Bar->width();
    ui->enemyName->setText(enemy->getMobName());
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
    ui->Bar->setFixedWidth(h.getDamagedRatio(enemy->getCurrHP(), enemy->getMaxHP()) * h.barWidth);

    if (enemy->getCurrHP() == 0) {
        qDebug() << "RESET!" << "\n";
        h.resetBar(ui->Bar);
        // Now that the bar has been reseted, we need to spawn a new enemy.
    }
}
