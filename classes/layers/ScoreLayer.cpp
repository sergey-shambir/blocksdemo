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
