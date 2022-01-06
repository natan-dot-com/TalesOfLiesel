#ifndef SKILLINFO_H
#define SKILLINFO_H

#include <QObject>
#include <QWidget>
#include <QPair>
#include <QLabel>
#include <QString>

#define LABEL first
#define STRING second

class SkillInfo : public QObject {
    Q_OBJECT
public:
    SkillInfo(QWidget *parent = nullptr);
    virtual ~SkillInfo() {};

    void initSkillInfo(QPair<QLabel *, QString> _skillLevelValue,
                       QPair<QLabel *, QString> _coinsNeededUpgrade);

private:
    QPair<QLabel *, QString> skillLevelValue;
    QPair<QLabel *, QString> coinsNeededUpgrade;

    void setupSkillInfo();

public slots:
    void updateSkillInfoLabels(QString, QString);
};

#endif // SKILLINFO_H
