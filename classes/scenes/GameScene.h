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
