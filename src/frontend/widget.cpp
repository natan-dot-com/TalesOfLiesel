#include "ui_widget.h"
#include "./lib/frontend/widget.h"
#include <QMovie>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setupMainWindow();

    this->enemyButton = new EnemyButton();
    this->enemyButton->initButton(ui->enemyButton);

    // Instantiate Game
    this->game = new Game();

    connect(game, SIGNAL(spawnEnemy(QString*)), enemyButton, SLOT(updateEnemyIcon(QString*)), Qt::QueuedConnection);
    QString *name = new QString("Mage");
    game->generateEnemy(name);

    this->healthBar = new Healthbar();
    this->healthBar->initHealthbar(ui->healthBar, 100, 100);
    this->healthBar->setupBar();
    connect(ui->enemyButton, SIGNAL(clicked()), healthBar, SLOT(updateBar()), Qt::QueuedConnection);
}

Widget::~Widget()
{
    delete ui->enemyButton;
    delete this->game;
    delete ui->healthBar;
    delete ui;
}

void Widget::startAnimationIcons()
{
    QMovie *movie = new QMovie(this);
    movie->setFileName(":/imgs/src/assets/ui-components/ButtonEffectFire2.gif");
    connect(movie, &QMovie::frameChanged, [=]{
        ui->fireballIcon->setMovie(movie);
    });
    movie->setScaledSize(QSize(75, 75));
    movie->start();

    QMovie *movie2 = new QMovie(this);
    movie2->setFileName(":/imgs/src/assets/ui-components/ButtonEffectDestructionAura.gif");
    connect(movie2, &QMovie::frameChanged, [=]{
        ui->destructionAuraIcon->setMovie(movie2);
    });
    movie2->setScaledSize(QSize(40, 40));
    movie2->start();
}

void Widget::setupMainWindow() {
    setWindowFlags(windowFlags()                                |
                   Qt::CustomizeWindowHint                      |
                   Qt::WindowMinimizeButtonHint                 |
                   Qt::WindowMaximizeButtonHint                 |
                   Qt::WindowCloseButtonHint);
    move(QGuiApplication::screens().at(0)->geometry().center() - frameGeometry().center());
    ui->stackedWidget->setCurrentIndex(0);
    startAnimationIcons();
}

void Widget::on_newGameButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_saveGoMenuButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

