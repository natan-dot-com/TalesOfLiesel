#ifndef EVENTPANEL_H
#define EVENTPANEL_H

#include <QObject>
#include <QWidget>
#include <QListWidget>

/*
 * Frontend component that keeps a live feed of the latest events on the game,
 * like damage of a special skill or if Liesel leveled up.
 *
 */

class EventPanel : public QObject {
    Q_OBJECT
private:
    static QListWidget *eventList;

public:
    EventPanel(QWidget *parent = nullptr);
    virtual ~EventPanel() {};

    void initEventPanel(QListWidget *_eventList);

public slots:
    void addEventOnFeed(QString event);
};

#endif // EVENTPANEL_H
