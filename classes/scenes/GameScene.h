#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d_game.h"

class BlocksGridLayer;
class ScoreLayer;

class GameScene : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene *scene();

protected:
    GameScene();
    bool init();
    void onEnter() CC_DECL_OVERRIDE;
    void onExit() CC_DECL_OVERRIDE;

    void keyBackClicked(void) CC_DECL_OVERRIDE;
    void keyMenuClicked(void) CC_DECL_OVERRIDE;

private:
    cocos2d::CCReference<BlocksGridLayer> m_grid;
    cocos2d::CCReference<ScoreLayer> m_score;
};

#endif // GAMESCENE_H
