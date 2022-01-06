#include <./lib/frontend/components/skillinfo.h>

SkillInfo::SkillInfo(QWidget *parent) : QObject(parent) {

}

void SkillInfo::initSkillInfo(QPair<QLabel *, QString> _skillLevelValue, QPair<QLabel *, QString> _coinsNeededUpgrade) {
    this->skillLevelValue.LABEL  = _skillLevelValue.LABEL;
    this->skillLevelValue.STRING = _skillLevelValue.STRING;
    this->coinsNeededUpgrade.LABEL  = _coinsNeededUpgrade.LABEL;
    this->coinsNeededUpgrade.STRING = _coinsNeededUpgrade.STRING;
    setupSkillInfo();
}

void SkillInfo::setupSkillInfo() {
    this->skillLevelValue.LABEL->setText(this->skillLevelValue.STRING);
    this->coinsNeededUpgrade.LABEL->setText(this->coinsNeededUpgrade.STRING);
}

// a = [LEVEL + value] | b = [COINS + NEEDED FOR NEXT LEVEL]
void SkillInfo::updateSkillInfoLabels(QString a, QString b) {
    this->skillLevelValue.STRING = a;
    this->coinsNeededUpgrade.STRING = b;
    setupSkillInfo();
}
