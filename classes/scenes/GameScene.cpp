#include "GameScene.h"
#include "BlocksGridLayer.h"

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
    const CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCLayerColor *background = CCLayerColor::create(ccc4(50, 50, 50, 255));
    background->setContentSize(size);
    addChild(background, -1);

    m_grid = BlocksGridLayer::create(0.96 * size.width, size.height * 0.7);
    m_grid->setPosition(CCPoint(0.5 * (size.width - m_grid->getContentSize().width),
                                0.2 * size.height));
    addChild(m_grid, 1);

    return true;
}
