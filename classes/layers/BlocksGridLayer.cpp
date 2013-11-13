#include "BlocksGridLayer.h"

static const float PADDING = 10;
static const int MINIMUM_DESTROYABLE_GROUP = 4;
static const float ANIM_GRAVITY_DURATION = 0.2;

using namespace cocos2d;

BlocksGridLayer *BlocksGridLayer::create(float maxWidth, float maxHeight)
{
    BlocksGridLayer *ret = new BlocksGridLayer();
    if (ret->init(maxWidth, maxHeight)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

BlocksGridLayer::BlocksGridLayer()
{
    setTouchComponentDelegate(this);
    setTouchComponentPriority(0);
}

void BlocksGridLayer::onEnter()
{
    CCLayer::onEnter();
    setTouchComponentEnabled(true);

    /// TODO: don't fill, use spawn layer instead.
    fillRandomBlocks();
}

void BlocksGridLayer::onExit()
{
    setTouchComponentEnabled(false);
    CCLayer::onExit();
}

bool BlocksGridLayer::init(float maxWidth, float maxHeight)
{
    m_blockSize = desiredBlockSize();
    m_width = floor((maxWidth - 2 * PADDING) / m_blockSize);
    m_height = floor((maxHeight - 2 * PADDING) / m_blockSize);
    m_blocks.resize(m_width * m_height, Block());
    m_sprites.resize(m_width * m_height, nullptr);

    m_touchArea.origin = CCPoint(PADDING, PADDING);
    m_touchArea.size = CCSize(m_width * m_blockSize, m_height * m_blockSize);

    CCLayerColor::initWithColor(ccc4(0, 0, 0, 255),
                                m_width * m_blockSize + 2 * PADDING,
                                m_height * m_blockSize + 2 * PADDING);

    return true;
}

bool BlocksGridLayer::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
    CCPoint pos = convertTouchToNodeSpace(touch);
    if (!m_touchArea.containsPoint(pos))
        return false;

    pos = pos - m_touchArea.origin;
    int x = floor(pos.x / m_blockSize);
    int y = floor(pos.y / m_blockSize);
    sendDestructionWave(x, y);

    return true;
}

float BlocksGridLayer::desiredBlockSize()
{
    float factor = CCDevice::getDPI() / 160.0;
    return 40 * factor;
}

void BlocksGridLayer::sendDestructionWave(int x, int y)
{
    if (getBlock(x, y).isEmpty())
        return;
    std::vector<BlockIndex> indicies;
    if (!findDestroyableBlocks(indicies, BlockIndex(x, y)))
        return;

    for (const BlockIndex &i : indicies) {
        CCLOG("Index {%i, %i}", i.first, i.second);

        CCSprite *sprite = getSprite(i);
        if (sprite == nullptr) {
            CCLOG("Sprite is nullptr!");
        }
        sprite->stopAllActions();
        sprite->removeFromParent();
        setBlock(i, Block());
    }

    applyGravity();
}

bool BlocksGridLayer::findDestroyableBlocks(std::vector<BlockIndex> &indicies, const BlockIndex &start)
{
    indicies.clear();
    for (Block &block : m_blocks)
        block.setVisited(false);

    std::vector<BlockIndex> neighbors;
    neighbors.push_back(start);
    while (!neighbors.empty()) {
        std::vector<BlockIndex> far;
        for (const BlockIndex &i : neighbors) {
            Block block = getBlock(i);
            if (block.isVisited())
                continue;

            block.setVisited(true);
            setBlock(i, block);
            indicies.push_back(i);

            BlockIndex top(i.first, i.second - 1);
            if (top.second >= 0 && !getBlock(top).isVisited() && getBlock(top) == block)
                far.push_back(top);

            BlockIndex bottom(i.first, i.second + 1);
            if (bottom.second < m_height && !getBlock(bottom).isVisited() && getBlock(bottom) == block)
                far.push_back(bottom);

            BlockIndex left(i.first - 1, i.second);
            if (left.first >= 0 && !getBlock(left).isVisited() && getBlock(left) == block)
                far.push_back(left);

            BlockIndex right(i.first + 1, i.second);
            if (right.second < m_width && !getBlock(right).isVisited() && getBlock(right) == block)
                far.push_back(right);
        }
        far.swap(neighbors);
    }
    if (indicies.size() < MINIMUM_DESTROYABLE_GROUP)
        return false;
    return true;
}

void BlocksGridLayer::applyGravity()
{
    for (int y = 0; y < m_height; ++y)
        for (int x = 0; x < m_width; ++x)
            if (getBlock(x, y).isEmpty()) {
                int y2 = y + 1;
                while (getBlock(x, y2).isEmpty() && y2 < m_height)
                    ++y2;
                if (y2 >= m_height)
                    continue;
                float motionY = (y2 - y) * m_blockSize;
                int index1 = y * m_width + x;
                int index2 = y2 * m_width + x;
                std::swap(m_blocks[index1], m_blocks[index2]);
                std::swap(m_sprites[index1], m_sprites[index2]);
                CCSprite *sprite = m_sprites[index1];
                sprite->runAction(CCMoveBy::create(ANIM_GRAVITY_DURATION, CCPoint(0, -motionY)));
            }
}

void BlocksGridLayer::fillRandomBlocks()
{
    for (int i = 0, n = m_width * m_height; i < n; ++i) {
        m_blocks[i] = Block::randomBlock();
        if (CCSprite *sprite = m_sprites[i]) {
            sprite->stopAllActions();
            sprite->removeFromParent();
            m_sprites[i] = nullptr;
        }
        const Block &block = m_blocks[i];
        createSprite(i % m_width, i / m_width);
    }
}

const Block &BlocksGridLayer::getBlock(int x, int y) const
{
    return m_blocks[y * m_width + x];
}

const Block &BlocksGridLayer::getBlock(const BlockIndex &i) const
{
    return getBlock(i.first, i.second);
}

void BlocksGridLayer::setBlock(int x, int y, const Block &block)
{
    m_blocks[y * m_width + x] = block;
}

void BlocksGridLayer::setBlock(const BlockIndex &i, const Block &block)
{
    setBlock(i.first, i.second, block);
}

CCSprite *BlocksGridLayer::getSprite(const BlockIndex &i)
{
    return m_sprites[i.second * m_width + i.first];
}

CCSprite *BlocksGridLayer::createSprite(int x, int y)
{
    int index = y * m_width + x;

    CCSprite *avatar = CCSprite::create(getBlock(x, y).getImageName());
    avatar->setScaleX(m_blockSize / avatar->getContentSize().width);
    avatar->setScaleY(m_blockSize / avatar->getContentSize().height);
    CCPoint pos = CCPoint(0.5f + x, 0.5f + y) * m_blockSize + CCPoint(PADDING, PADDING);
    avatar->setPosition(pos);
    addChild(avatar, 1);
    m_sprites[index] = avatar;

    return avatar;
}
