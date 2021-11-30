#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include <QGraphicsItem>

class GameButton: public QGraphicsItem {
public:
    void onClick(QGraphicsSceneMouseEvent *e);
};

#endif // GAME_BUTTON_H
