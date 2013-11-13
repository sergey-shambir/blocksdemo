
TEMPLATE = lib
CONFIG += dll

include(common.prf)

LIBS += $$CC_EXTERNAL_LIBS

# Function cc_files(wildcardPath) returns all files matching given wildcard,
# without recursive folders search.
defineReplace(cc_files) {
    return($$files(../$$1))
}

TARGET = $${CC_LIB_LOCATION}/cocos2dx

OBJECTS_DIR = obj/cocos2dx/$${BUILD_TYPE}
MOC_DIR = obj/cocos2dx/$${BUILD_TYPE}

COCOS2DX_FOLDERS = \
    cocos2dx/ \
    cocos2dx/platform \
    cocos2dx/platform/linux \
    cocos2dx/actions \
    cocos2dx/base_nodes \
    cocos2dx/cocoa \
    cocos2dx/draw_nodes \
    cocos2dx/effects \
    cocos2dx/include \
    cocos2dx/kazmath/include/kazmath/GL \
    cocos2dx/kazmath/include/kazmath \
    cocos2dx/kazmath/src/GL \
    cocos2dx/kazmath/src \
    cocos2dx/keypad_dispatcher \
    cocos2dx/label_nodes \
    cocos2dx/layers_scenes_transitions_nodes \
    cocos2dx/menu_nodes \
    cocos2dx/misc_nodes \
    cocos2dx/particle_nodes \
    cocos2dx/script_support \
    cocos2dx/shaders \
    cocos2dx/sprite_nodes \
    cocos2dx/support \
    cocos2dx/support/component \
    cocos2dx/support/data_support \
    cocos2dx/support/image_support \
    cocos2dx/support/zip_support \
    cocos2dx/support/user_default \
    cocos2dx/support/tinyxml2 \
    cocos2dx/text_input_node \
    cocos2dx/textures \
    cocos2dx/tilemap_parallax_nodes \
    cocos2dx/touch_dispatcher \
    CocosDenshion/include \
    CocosDenshion/linux \
    extensions/AssetsManager/ \
    extensions/network/ \
    extensions/OmegaR/ \
    extensions/

for (FOLDER, COCOS2DX_FOLDERS) {
    HEADERS += $$files(../$${FOLDER}/*.h)
    SOURCES += $$files(../$${FOLDER}/*.cpp) $$files(../$${FOLDER}/*.c)
}

SOURCES -= ../extensions/network/WebSocket.cpp

