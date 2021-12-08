#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <QGraphicsItem>
#include <QLabel>

struct Healthbar {
    int barWidth;
    QString defaultStyle;

    Healthbar() {

    }

    Healthbar(int _barWidth, QString _defaultStyle) {
        barWidth = _barWidth;
        defaultStyle = _defaultStyle;
    }

    float getDamagedRatio(float current, float max) {
        return current/max;
    }

    void resetBar(QLabel *Bar) {
        Bar->setStyleSheet(defaultStyle);
        Bar->setFixedWidth(barWidth);
    }
};

#endif // COMPONENTS_H
