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

#ifndef SCORELAYER_H
#define SCORELAYER_H

#include "cocos2d_game.h"

class ScoreLayer : public cocos2d::CCLayer
{
public:
    static ScoreLayer *create(const cocos2d::CCSize &size);
    void addScoreForDestroyedBlocks(int destroyedCount);
    void resetScore();

protected:
    ScoreLayer();
    bool init(const cocos2d::CCSize &size);
    void addScoreDirectly(int score);

private:
    long long m_score;
    cocos2d::CCReference<cocos2d::CCLabelTTF> m_scoreLabel;
};

#endif // SCORELAYER_H
