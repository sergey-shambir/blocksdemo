#include "BlocksGridLayer.h"

static const float PADDING = 10;
static const int MINIMUM_DESTROYABLE_GROUP = 3;
static const float ANIM_GRAVITY_DURATION = 0.2;
static const float ANIM_SHIFT_DURATION = 0.3;
static const float SPAWN_LAYER_TIME = 2.0;

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

void BlocksGridLayer::onBlocksDestroyed(const std::function<void (int)> &fn)
{
    m_onBlocksDestroyed.push_back(fn);
}

void BlocksGridLayer::onGameStarted(const std::function<void()> &fn)
{
    m_onGameStarted.push_back(fn);
}

BlocksGridLayer::BlocksGridLayer()
    : m_isGameOver(false)
    , m_blockSize(0)
    , m_width(0)
    , m_height(0)
{
    setTouchComponentDelegate(this);
    setTouchComponentPriority(0);
}

void BlocksGridLayer::onEnter()
{
    CCLayer::onEnter();
    setTouchComponentEnabled(true);
    schedule(schedule_selector(BlocksGridLayer::spawnNextBlock), SPAWN_LAYER_TIME / m_width);
    restartGame();
}

void BlocksGridLayer::onExit()
{
    unschedule(schedule_selector(BlocksGridLayer::spawnNextBlock));
    setTouchComponentEnabled(false);
    CCLayer::onExit();
}

bool BlocksGridLayer::init(float maxWidth, float maxHeight)
{
    m_blockSize = desiredBlockSize();
    m_width = floor((maxWidth - 2 * PADDING) / m_blockSize);
    m_height = floor((maxHeight - 2 * PADDING) / m_blockSize);
    m_isGameOver = false;
    m_blocks.resize(m_width * m_height, Block());
    m_sprites.resize(m_width * m_height, nullptr);
    m_spawnedBlocks.resize(m_width, Block());
    m_spawnedSprites.resize(m_width, nullptr);

    m_touchArea.origin = CCPoint(PADDING, m_blockSize + 2 * PADDING);
    m_touchArea.size = CCSize(m_width * m_blockSize, m_height * m_blockSize);

    CCLayerColor::initWithColor(ccc4(0, 0, 0, 255),
                                m_width * m_blockSize + 2 * PADDING,
                                (1 + m_height) * m_blockSize + 3 * PADDING);

    return true;
}

bool BlocksGridLayer::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
    if (m_isGameOver)
    {
        CCPoint pos = m_labelTryAgain->convertTouchToNodeSpace(touch);
        CCRect tapRect;
        tapRect.size = m_labelTryAgain->getContentSize();
        if (tapRect.containsPoint(pos)) {
            restartGame();
            return true;
        }
        return false;
    }

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
    const int destroyedCount = int(indicies.size());

    for (const BlockIndex &i : indicies) {
        CCSprite *sprite = getSprite(i);
        sprite->stopAllActions();
        sprite->removeFromParent();
        setBlock(i, Block());
        m_sprites[i.second * m_width + i.first] = nullptr;
    }

    applyGravity();

    for (const auto &fn : m_onBlocksDestroyed)
        fn(destroyedCount);
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

            // TODO: don't check it when crash mode enabled.
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
            if (right.first < m_width && !getBlock(right).isVisited() && getBlock(right) == block)
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

void BlocksGridLayer::restartGame()
{
    m_isGameOver = false;

    if (m_labelGameOver) {
        m_labelGameOver->removeFromParent();
        m_labelGameOver = nullptr;
    }
    if (m_labelTryAgain) {
        m_labelTryAgain->removeFromParent();
        m_labelTryAgain = nullptr;
    }

    for (int i = 0, n = m_width * m_height; i < n; ++i) {
        m_blocks[i] = Block();
        if (CCSprite *sprite = m_sprites[i]) {
            sprite->stopAllActions();
            sprite->removeFromParent();
            m_sprites[i] = nullptr;
        }
    }
    for (int i = 0, n = m_width * (m_height / 2); i < n; ++i) {
        m_blocks[i] = Block::randomBlock();
        m_sprites[i] = createSprite(i % m_width, i / m_width);
    }
    for (int x = 0; x < m_width; ++x) {
        if (CCSprite *sprite = m_spawnedSprites[x]) {
            sprite->stopAllActions();
            sprite->removeFromParent();
            m_spawnedSprites[x] = nullptr;
        }
        m_spawnedBlocks[x] = Block();
    }

    for (const auto &fn : m_onGameStarted)
    {
        fn();
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
    CCSprite *avatar = CCSprite::create(getBlock(x, y).getImageName());
    avatar->setScaleX(m_blockSize / avatar->getContentSize().width);
    avatar->setScaleY(m_blockSize / avatar->getContentSize().height);
    CCPoint pos = CCPoint(0.5f + x, 1.5f + y) * m_blockSize + CCPoint(PADDING, 2 * PADDING);
    avatar->setPosition(pos);
    addChild(avatar, 1);
    return avatar;
}

CCSprite *BlocksGridLayer::createSpawnedSprite(int x)
{
    CCSprite *avatar = CCSprite::create(m_spawnedBlocks[x].getImageName());
    avatar->setScaleX(m_blockSize / avatar->getContentSize().width);
    avatar->setScaleY(m_blockSize / avatar->getContentSize().height);
    CCPoint pos = CCPoint(0.5f + x, 0.5f) * m_blockSize + CCPoint(PADDING, PADDING);
    avatar->setPosition(pos);
    avatar->setOpacity(160);
    addChild(avatar, 1);
    return avatar;
}

void BlocksGridLayer::spawnNextBlock(float dt)
{
    if (m_isGameOver)
        return;

    for (int x = 0; x < m_width; ++x) {
        if (m_spawnedBlocks[x].isEmpty()) {
            m_spawnedBlocks[x] = Block::randomBlock();
            m_spawnedSprites[x] = createSpawnedSprite(x);
            return;
        }
    }
    shiftSpawnedBlocks();
}

void BlocksGridLayer::shiftSpawnedBlocks()
{
    for (int x = 0; x < m_width; ++x) {
        if (!getBlock(x, m_height - 1).isEmpty()) {
            onGameOver();
            return;
        }
    }

    for (int y = m_height - 2; y >= 0; --y) {
        for (int x = 0; x < m_width; ++x) {
            setBlock(x, y + 1, getBlock(x, y));
            if (CCSprite *sprite = getSprite(BlockIndex(x, y))) {
                m_sprites[(y + 1) * m_width + x] = sprite;
                sprite->runAction(CCMoveBy::create(ANIM_SHIFT_DURATION, CCPoint(0, m_blockSize)));
            }
            m_sprites[y * m_width + x] = nullptr;
        }
    }

    for (int x = 0; x < m_width; ++x) {
        setBlock(x, 0, m_spawnedBlocks[x]);
        m_spawnedBlocks[x] = Block();
        std::swap(m_sprites[x], m_spawnedSprites[x]);
        m_sprites[x]->runAction(CCMoveBy::create(ANIM_SHIFT_DURATION, CCPoint(0, m_blockSize + PADDING)));
        m_sprites[x]->runAction(CCFadeTo::create(ANIM_SHIFT_DURATION, 255));
    }
}

void BlocksGridLayer::onGameOver()
{
    m_isGameOver = true;

    m_labelGameOver = CCLabelTTF::create("GAME OVER", "Arial", 32);
    m_labelGameOver->setColor(ccRED);
    m_labelGameOver->setPosition(CCPoint(getContentSize().width * 0.5, getContentSize().height * 0.6));
    addChild(m_labelGameOver, 1);

    m_labelTryAgain = CCLabelTTF::create("Tap here to try again...", "Arial", 32);
    m_labelTryAgain->setColor(ccWHITE);
    m_labelTryAgain->setPosition(CCPoint(getContentSize().width * 0.5, getContentSize().height * 0.4));
    addChild(m_labelTryAgain, 1);
}
