TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

include(../libs/qmake/game.pri)

INCLUDEPATH += \
    $${PWD}/../include \
    $${PWD}/../classes/singletones \
    $${PWD}/../classes/scenes \
    $${PWD}/../classes/layers \
    $${PWD}/../classes/model \
    $${PWD}/../classes/sharing

SOURCES += main.cpp \
    ../classes/singletones/BlocksApplication.cpp \
    ../classes/scenes/LoadingScene.cpp \
    ../classes/scenes/GameScene.cpp \
    ../classes/model/Block.cpp \
    ../classes/layers/BlocksGridLayer.cpp \
    ../classes/layers/ScoreLayer.cpp \
    ../classes/sharing/MailSender.cpp \
    ../classes/sharing/BreakpadWatcher.cpp \
    ../include/cocos2d_game.cpp \
    ../classes/sharing/ExtraFileUtils.cpp \
    ../classes/sharing/SystemUtils.cpp \
    ../classes/sharing/BreakpadUploader.cpp \
    ../classes/layers/TouchUtils.cpp

HEADERS += \
    ../classes/singletones/BlocksApplication.h \
    ../include/cocos2d_game.h \
    ../classes/scenes/LoadingScene.h \
    ../classes/scenes/GameScene.h \
    ../classes/model/Block.h \
    ../classes/layers/BlocksGridLayer.h \
    ../classes/layers/ScoreLayer.h \
    ../classes/sharing/MailSender.h \
    ../classes/sharing/BreakpadWatcher.h \
    ../classes/sharing/ExtraFileUtils.h \
    ../classes/sharing/SystemUtils.h \
    ../classes/sharing/BreakpadUploader.h \
    ../classes/layers/TouchUtils.h

OTHER_FILES += \
    ../proj.android/jni/Application.mk \
    ../proj.android/jni/Android.mk \
    ../proj.android/AndroidManifest.xml

