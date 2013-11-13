#ifndef SCORELAYER_H
#define SCORELAYER_H

#include "cocos2d_game.h"

class ScoreLayer : public cocos2d::CCLayer
{
public:
    static ScoreLayer *create(const cocos2d::CCSize &size);
    void addScoreForDestroyedBlocks(int destroyedCount);

protected:
    ScoreLayer();
    bool init(const cocos2d::CCSize &size);
    void addScoreDirectly(int score);

private:
    long long m_score;
    cocos2d::CCReference<cocos2d::CCLabelTTF> m_scoreLabel;
};

#endif // SCORELAYER_H
