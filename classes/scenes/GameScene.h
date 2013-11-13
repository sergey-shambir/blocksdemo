#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d_game.h"

class BlocksGridLayer;

class GameScene : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene *scene();

private:
    GameScene();
    bool init();

    cocos2d::CCReference<BlocksGridLayer> m_grid;
};

#endif // GAMESCENE_H
