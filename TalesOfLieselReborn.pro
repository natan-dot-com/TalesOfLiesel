QT       += core gui multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ./src/main.cpp \
    ./src/backend/ctx.cpp \
    ./src/backend/enemy.cpp \
    ./src/backend/error_handling.cpp \
    ./src/backend/liesel.cpp \
    ./src/backend/rng.cpp \
    ./src/backend/skills.cpp \
    ./src/frontend/widget.cpp \
    ./src/frontend/components/healthbar.cpp \
    ./src/game.cpp \
    ./src/frontend/components/enemybutton.cpp \
    ./src/frontend/components/eventpanel.cpp \
    ./src/frontend/components/lieselinfo.cpp \
    ./src/frontend/components/skillinfo.cpp

HEADERS += \
    ./lib/backend/ctx.h \
    ./lib/backend/enemy.h \
    ./lib/backend/error_handling.h \
    ./lib/backend/liesel.h \
    ./lib/backend/rng.h \
    ./lib/backend/skills.h \
    ./lib/frontend/widget.h \
    ./lib/frontend/components/healthbar.h \
    ./lib/game.h \
    ./lib/frontend/components/enemybutton.h \
    ./lib/backend/gamephrases.h \
    ./lib/frontend/components/eventpanel.h \
    ./lib/frontend/components/lieselinfo.h \
    ./lib/frontend/components/skillinfo.h \
    ./lib/gamemacros.h

FORMS += \
    ./ui/widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc
