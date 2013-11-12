#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d_game.h"

class GameScene : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene *scene();

private:
    GameScene();
    bool init();
};

#endif // GAMESCENE_H
