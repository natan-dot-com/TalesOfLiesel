#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <iostream>
#include <./lib/backend/liesel.h>
#include <./lib/backend/enemy.h>
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
    void on_giveLevelButton_clicked();
    void on_giveSoulCoins_clicked();
    void on_enemyButton_clicked();

private:
    Ui::MainWindow *ui;
    Liesel *liesel = new Liesel();
    Enemy *enemy = new Enemy();
    Healthbar h;
    EnemyButton enemyButton;
};

#endif // MAINWINDOW_H
