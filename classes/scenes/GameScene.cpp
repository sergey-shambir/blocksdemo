#include "GameScene.h"
#include "BlocksGridLayer.h"
#include "ScoreLayer.h"

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

    m_grid = BlocksGridLayer::create(0.96 * size.width, size.height * 0.8);
    m_grid->setPosition(CCPoint(0.5 * (size.width - m_grid->getContentSize().width),
                                0.05 * size.height));
    addChild(m_grid, 1);

    m_score = ScoreLayer::create(CCSize(0.6 * size.width, 0.1 * size.height));
    m_score->setPosition(CCPoint(0.5 * size.width, 0.95 * size.height));
    m_grid->onBlocksDestroyed(std::bind(&ScoreLayer::addScoreForDestroyedBlocks, m_score.data(), std::placeholders::_1));
    addChild(m_score, 1);

    return true;
}

void GameScene::onEnter()
{
    CCLayer::onEnter();
    setKeypadEnabled(true);
}

void GameScene::onExit()
{
    setKeypadEnabled(false);
    CCLayer::onExit();
}

void GameScene::keyBackClicked(void)
{
    CCDirector::sharedDirector()->end();
}

void GameScene::keyMenuClicked(void)
{
    // TODO: show crasher menu.
}
