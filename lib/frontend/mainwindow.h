#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <iostream>
#include <./lib/frontend/game.h>
#include <./lib/frontend/components.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_enemyButton_clicked();

    void on_destructionAuraUseButton_clicked();

    void on_fireballUpgradeButton_clicked();

    void on_destructionAuraUpgradeButton_clicked();

private:
    Ui::MainWindow *ui;
    ActiveComponents *a;
    Game *g;
};

#endif // MAINWINDOW_H
