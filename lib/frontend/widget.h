#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QScreen>
#include <./lib/frontend/components/healthbar.h>
#include <./lib/frontend/components/enemybutton.h>
#include <./lib/frontend/components/eventpanel.h>
#include <./lib/Game.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_newGameButton_clicked();
    void on_saveGoMenuButton_clicked();

private:
    Ui::Widget *ui;
    Healthbar *healthBar;
    EnemyButton *enemyButton;
    EventPanel *eventPanel;

    Game *game;

    void connectAll();
    void startAnimationIcons();
    void setupMainWindow();
    void setupHealthbar(int current, int max);
    void setupEnemyButton();
    void setupGame();
};
#endif // WIDGET_H
