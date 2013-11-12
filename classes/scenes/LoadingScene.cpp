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

#include "LoadingScene.h"
#include "GameScene.h"

using namespace cocos2d;

CCScene *LoadingScene::scene()
{
    LoadingScene *layer = new LoadingScene();
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

LoadingScene::LoadingScene()
{
    m_imagesToLoad = {
        "block-blue.png",
        "block-green.png",
        "block-red.png"
    };
}

bool LoadingScene::init()
{
    CCLayer::init();
    const CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCLayerColor *background = CCLayerColor::create(ccc4(200, 200, 200, 255));
    background->setContentSize(size);
    addChild(background, -1);

    CCLabelTTF *labelLoading = CCLabelTTF::create("Loading...", "Arial", 20);
    labelLoading->setPosition(CCPoint(size.width * 0.5, size.height * 0.5));
    addChild(labelLoading, 1);
    labelLoading->setColor(ccBLACK);

    scheduleUpdate();

    return true;
}

void LoadingScene::update(float dt)
{
    CCLayer::update(dt);
    if (!loadNextResource()) {
        unscheduleUpdate();
        loadNextScene();
    }
}

bool LoadingScene::loadNextResource()
{
    if (!m_imagesToLoad.empty()) {
        const std::string image = m_imagesToLoad.back();
        m_imagesToLoad.pop_back();
        CCTextureCache::sharedTextureCache()->addImage(image.c_str());
        return true;
    }
    return false;
}

void LoadingScene::loadNextScene()
{
    CCDirector::sharedDirector()->pushScene(GameScene::scene());
}
