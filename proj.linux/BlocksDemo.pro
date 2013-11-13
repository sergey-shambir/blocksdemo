TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

include(../libs/qmake/game.pri)

INCLUDEPATH += \
    $${PWD}/../include \
    $${PWD}/../classes/singletones \
    $${PWD}/../classes/scenes \
    $${PWD}/../classes/layers

SOURCES += main.cpp \
    ../classes/singletones/BlocksApplication.cpp \
    ../classes/scenes/LoadingScene.cpp \
    ../classes/scenes/GameScene.cpp \
    ../classes/model/Block.cpp \
    ../classes/layers/BlocksGridLayer.cpp \
    ../classes/layers/BlocksSpawnLayer.cpp \
    ../classes/layers/ScoreLayer.cpp

HEADERS += \
    ../classes/singletones/BlocksApplication.h \
    ../include/cocos2d_game.h \
    ../classes/scenes/LoadingScene.h \
    ../classes/scenes/GameScene.h \
    ../classes/model/Block.h \
    ../classes/layers/BlocksGridLayer.h \
    ../classes/layers/BlocksSpawnLayer.h \
    ../classes/layers/ScoreLayer.h

