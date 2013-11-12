#include "GameScene.h"

using namespace cocos2d;

CCScene *GameScene::scene()
{
    GameScene *layer = new GameScene();
    if (!layer->init()) {
        delete layer;
        return 0;
    }
    layer->autorelease();

    CCScene *scene = new CCScene();
    scene->init();
    scene->addChild(layer);

    return scene;
}

GameScene::GameScene()
{
}

bool GameScene::init()
{
    CCLayer::init();
    return true;
}
