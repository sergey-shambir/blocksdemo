LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../classes/layers/BlocksGridLayer.cpp \
                   ../../classes/layers/ScoreLayer.cpp \
                   ../../classes/model/Block.cpp \
                   ../../classes/sharing/MailSender.cpp \
                   ../../classes/scenes/GameScene.cpp \
                   ../../classes/scenes/LoadingScene.cpp \
                   ../../classes/singletones/BlocksApplication.cpp

LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/../../include \
        $(LOCAL_PATH)/../../classes/singletones \
        $(LOCAL_PATH)/../../classes/scenes \
        $(LOCAL_PATH)/../../classes/layers \
        $(LOCAL_PATH)/../../classes/model \
        $(LOCAL_PATH)/../../classes/sharing

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx)
$(call import-module,extensions)
