#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QScreen>
#include <./lib/frontend/components/healthbar.h>
#include <./lib/frontend/components/enemybutton.h>
#include <./lib/frontend/components/eventpanel.h>
#include <./lib/frontend/components/lieselinfo.h>
#include <./lib/frontend/components/skillinfo.h>
#include <./lib/game.h>

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

    void on_exitGameButton_clicked();

private:
    Ui::Widget *ui;

    // Auxiliary classes to manage behaviour of components.
    Healthbar *healthBar;
    EnemyButton *enemyButton;
    EventPanel *eventPanel;
    LieselInfo *lieselInfo;
    SkillInfo *fireballInfo;
    SkillInfo *destructionAuraInfo;


    // Game backend.
    Game *game;

    // Setup Qt related signals and animations.
    void connectAll();
    void startAnimationIcons();
    void setupMainWindow();

    // Setup and allocate each auxiliary class.
    void setupMusic();
    void setupHealthbar();
    void setupEnemyButton();
    void setupEventPanel();
    void setupLieselInfo();
    void setupFireballInfo();
    void setupDestructionAuraInfo();
    void setupGame();

    // Initialize all classes with it's pointer to the Qt Widget
    // and needed data.
    void initAllComponents();
};
#endif // WIDGET_H
