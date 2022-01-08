#ifndef LIESELINFO_H
#define LIESELINFO_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QPair>

#define LABEL first
#define STRING second

class LieselInfo : public QObject {
    Q_OBJECT
public:
    LieselInfo(QWidget *parent = nullptr);
    virtual ~LieselInfo() {};

    void initLieselInfo(QPair<QLabel *, QString> _floorValue,
                        QPair<QLabel *, QString> _currentLevelValue,
                        QPair<QLabel *, QString> _currentLevelExp,
                        QPair<QLabel *, QString> _currentLevelMax,
                        QPair<QLabel *, QString> _soulCoinsValue);
    void setupLieselInfo();

private:
    QPair<QLabel *, QString> floorValue;
    QPair<QLabel *, QString> currentLevelValue;
    QPair<QLabel *, QString> currentLevelExp;
    QPair<QLabel *, QString> currentLevelMax;
    QPair<QLabel *, QString> soulCoinsValue;

public slots:
    void updateLieselInfoLabels(QString, QString, QString, QString, QString);
};

#endif // LIESELINFO_H
