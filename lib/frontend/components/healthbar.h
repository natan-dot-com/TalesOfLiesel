#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QProgressBar>
#include <QObject>
#include <QLabel>

/*
 * Front end component that represents the component that represents both the
 * Healthbar and the QLabel that names the enemy.
 */

class Healthbar : public QObject {
    Q_OBJECT
private:
    static QLabel *mobLabel;
    static QString *mobName;

    static QProgressBar *Bar;
    static int currentHP;
    static int maxHP;

public:
    explicit Healthbar(QWidget *parent = nullptr);
    virtual ~Healthbar();
    void initHealthbar(QLabel *_mobLabel, QString *_mobName,QProgressBar *_Bar, int _currentHP, int _maxHP);
    void setupName();
    void setupBar();

public slots:
    void updateBarOnDamage(int current, int max);
};

#endif // HEALTHBAR_H
