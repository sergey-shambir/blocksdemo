#ifndef BLOCKSGRIDLAYER_H
#define BLOCKSGRIDLAYER_H

#include "cocos2d_game.h"
#include "../model/Block.h"

class BlocksGridLayer : public cocos2d::CCLayerColor, public cocos2d::TouchComponent
{
public:
    static BlocksGridLayer *create(float maxWidth, float maxHeight);

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
    void fillRandomBlocks();

    const Block &getBlock(int x, int y) const;
    const Block &getBlock(const BlockIndex &i) const;
    void setBlock(int x, int y, const Block &block);
    void setBlock(const BlockIndex &i, const Block &block);

    cocos2d::CCSprite *getSprite(const BlockIndex &i);
    cocos2d::CCSprite *createSprite(int x, int y);

private:
    float m_blockSize;
    int m_width;
    int m_height;
    std::vector<Block> m_blocks;
    std::vector<cocos2d::CCSprite *> m_sprites;
    cocos2d::CCRect m_touchArea;
};

#endif // BLOCKSGRIDLAYER_H
