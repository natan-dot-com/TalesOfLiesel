#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <./lib/upgrade.h>

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
    void on_upgradeAButton_clicked();

    void on_Monster_clicked();

private:
    Ui::MainWindow *ui;
    Upgrade upgradeA;
    int monsterHealth = 100;
};
#endif // MAINWINDOW_H
