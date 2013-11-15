LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
        ../../include/cocos2d_game.cpp \
        ../../classes/layers/BlocksGridLayer.cpp \
        ../../classes/layers/ScoreLayer.cpp \
        ../../classes/layers/TouchUtils.cpp \
        ../../classes/model/Block.cpp \
        ../../classes/sharing/MailSender.cpp \
        ../../classes/sharing/BreakpadUploader.cpp \
        ../../classes/sharing/BreakpadWatcher.cpp \
        ../../classes/sharing/ExtraFileUtils.cpp \
        ../../classes/sharing/SystemUtils.cpp \
        ../../classes/scenes/GameScene.cpp \
        ../../classes/scenes/LoadingScene.cpp \
        ../../classes/singletones/BlocksApplication.cpp

LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/../../include \
        $(LOCAL_PATH)/../../classes/singletones \
        $(LOCAL_PATH)/../../classes/scenes \
        $(LOCAL_PATH)/../../classes/layers \
        $(LOCAL_PATH)/../../classes/model \
        $(LOCAL_PATH)/../../classes/sharing \
        $(LOCAL_PATH)/../../libs/googlebreakpad/src/client/linux/handler

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static chipmunk_static
LOCAL_STATIC_LIBRARIES       += breakpad_client
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android)
$(call import-module,external/chipmunk)
$(call import-module,cocos2dx)
$(call import-module,extensions)
$(call import-module,googlebreakpad)
