#include <./lib/frontend/components/eventpanel.h>
#include <QTime>
#include <QDebug>
#include <QListWidgetItem>

QListWidget *EventPanel::eventList;

EventPanel::EventPanel(QWidget *parent) : QObject(parent) {

}

void EventPanel::initEventPanel(QListWidget *_eventList) {
    this->eventList = _eventList;
}

void EventPanel::addEventOnFeed(QString event) {
    this->eventList->insertItem(0, new QListWidgetItem("[" + QTime::currentTime().toString() + "] " + event));
    this->eventList->scrollToTop();
}
