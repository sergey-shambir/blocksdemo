/****************************************************************************
Copyright (c) 2013 Omega-R company <omega-r.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

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
    m_grid->onGameStarted(std::bind(&ScoreLayer::resetScore, m_score.data()));
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
    m_grid->toggleContextMenu();
}
