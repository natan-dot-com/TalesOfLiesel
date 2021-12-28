QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ./src/main.cpp \
    ./src/frontend/mainwindow.cpp \
    ./src/frontend/game.cpp \
    ./src/backend/liesel.cpp \
    ./src/backend/skills.cpp \
    ./src/backend/rng.cpp \
    ./src/backend/enemy.cpp \
    ./src/backend/ctx.cpp \
    ./src/backend/error_handling.cpp

HEADERS += \
    ./lib/frontend/mainwindow.h \
    ./lib/frontend/stylesheet.h \
    ./lib/frontend/components.h \
    ./lib/frontend/game.h \
    ./lib/backend/liesel.h \
    ./lib/backend/skills.h \
    ./lib/backend/rng.h \
    ./lib/backend/enemy.h \
    ./lib/backend/ctx.h \
    ./lib/backend/error_handling.h

FORMS += \
    ./ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
