#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QProgressBar>
#include <QObject>

class Healthbar : public QObject {
    Q_OBJECT
private:
    static QProgressBar *Bar;
    static int currentHP;
    static int maxHP;

public:
    explicit Healthbar(QWidget *parent = nullptr);
    virtual ~Healthbar();
    void initHealthbar(QProgressBar *_Bar, int _currentHP, int _maxHP);
    void setupBar();

public slots:
    void updateBarOnDamage(int current, int max);
};

#endif // HEALTHBAR_H
