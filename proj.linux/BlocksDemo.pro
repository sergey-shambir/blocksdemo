TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

include(../libs/qmake/game.pri)

INCLUDEPATH += \
    $${PWD}/../include \
    $${PWD}/../classes/singletones \
    $${PWD}/../classes/scenes

SOURCES += main.cpp \
    ../classes/singletones/BlocksApplication.cpp \
    ../classes/scenes/LoadingScene.cpp \
    ../classes/scenes/GameScene.cpp

HEADERS += \
    ../classes/singletones/BlocksApplication.h \
    ../include/cocos2d_game.h \
    ../classes/scenes/LoadingScene.h \
    ../classes/scenes/GameScene.h

