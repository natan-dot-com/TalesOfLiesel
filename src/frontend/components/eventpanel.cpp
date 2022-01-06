#include <./lib/frontend/components/eventpanel.h>
#include <QTime>
#include <QDebug>

QListWidget *EventPanel::eventList;

EventPanel::EventPanel(QWidget *parent) : QObject(parent) {

}

void EventPanel::initEventPanel(QListWidget *_eventList) {
    this->eventList = _eventList;
}

void EventPanel::addEventOnFeed(QString event) {
    this->eventList->insertItem(0, "[" + QTime::currentTime().toString() + "] " + event);
    this->eventList->scrollToTop();
}
