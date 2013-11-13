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

#include "ScoreLayer.h"
#include <math.h>

using namespace cocos2d;

ScoreLayer *ScoreLayer::create(const CCSize &size)
{
    ScoreLayer *ret = new ScoreLayer();
    if (ret->init(size)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

void ScoreLayer::addScoreForDestroyedBlocks(int destroyedCount)
{
    if (destroyedCount == 3) {
        addScoreDirectly(1);
    } else {
        const float factor = pow(2.0, 0.6 * fmin(destroyedCount, 9.0));
        const int score = floor(destroyedCount * (3.0 + factor));
        addScoreDirectly(score);
    }
}

void ScoreLayer::resetScore()
{
    m_score = 0;
    CCString *text = CCString::createWithFormat("Score: %lld", m_score);
    m_scoreLabel->setString(text->getCString());
}

ScoreLayer::ScoreLayer()
    : m_score(0)
{
}

bool ScoreLayer::init(const CCSize &size)
{
    CCLayer::init();
    setContentSize(size);

    m_scoreLabel = CCLabelTTF::create("Score: 0", "Arial", 32, size,
                                      kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
    m_scoreLabel->setColor(ccYELLOW);
    addChild(m_scoreLabel, 1);

    return true;
}

void ScoreLayer::addScoreDirectly(int score)
{
    m_score += score;
    CCString *text = CCString::createWithFormat("Score: %lld", m_score);
    m_scoreLabel->setString(text->getCString());
}
