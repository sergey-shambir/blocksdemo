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

#ifndef BLOCKSGRIDLAYER_H
#define BLOCKSGRIDLAYER_H

#include "cocos2d_game.h"
#include "../model/Block.h"
#include <functional>

class BlocksGridLayer : public cocos2d::CCLayerColor, public cocos2d::TouchComponent
{
public:
    static BlocksGridLayer *create(float maxWidth, float maxHeight);

    void onBlocksDestroyed(const std::function<void(int amount)> &fn);
    void onGameStarted(const std::function<void()> &fn);

protected:
    typedef std::pair<int, int> BlockIndex;

    BlocksGridLayer();
    void onEnter() CC_DECL_OVERRIDE;
    void onExit() CC_DECL_OVERRIDE;
    bool init(float maxWidth, float maxHeight);
    bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) CC_DECL_OVERRIDE;

    static float desiredBlockSize();

    void sendDestructionWave(int x, int y);
    bool findDestroyableBlocks(std::vector<BlockIndex> &indicies, const BlockIndex &start);
    void applyGravity();
    void restartGame();

    const Block &getBlock(int x, int y) const;
    const Block &getBlock(const BlockIndex &i) const;
    void setBlock(int x, int y, const Block &block);
    void setBlock(const BlockIndex &i, const Block &block);

    cocos2d::CCSprite *getSprite(const BlockIndex &i);
    cocos2d::CCSprite *createSprite(int x, int y);
    cocos2d::CCSprite *createSpawnedSprite(int x);

    void spawnNextBlock(float dt);
    void shiftSpawnedBlocks();
    void onGameOver();

private:
    std::vector<std::function<void(int amount)>> m_onBlocksDestroyed;
    std::vector<std::function<void()>> m_onGameStarted;

    float m_blockSize;
    int m_width;
    int m_height;
    std::vector<Block> m_blocks;
    std::vector<Block> m_spawnedBlocks;
    std::vector<cocos2d::CCSprite *> m_sprites;
    std::vector<cocos2d::CCSprite *> m_spawnedSprites;
    cocos2d::CCRect m_touchArea;
    bool m_isGameOver;
    cocos2d::CCReference<cocos2d::CCLabelTTF> m_labelTryAgain;
    cocos2d::CCReference<cocos2d::CCLabelTTF> m_labelGameOver;
};

#endif // BLOCKSGRIDLAYER_H
