#include "Block.h"
#include "cocos2d_game.h"

enum Variants {
    VariantRed = 1,
    VariantGreen,
    VariantBlue
};

Block Block::randomBlock()
{
    Block ret;
    float randomized = 3 * CCRANDOM_0_1();
    if (randomized <= 1) {
        ret.m_variant = VariantRed;
    } else if (randomized <= 2) {
        ret.m_variant = VariantGreen;
    } else {
        ret.m_variant = VariantBlue;
    }
    return ret;
}

Block::Block()
    : m_variant(0)
    , m_visited(false)
{
}

Block::Block(const Block &o)
    : m_variant(o.m_variant)
    , m_visited(o.m_visited)
{
}

Block &Block::operator =(const Block &o)
{
    m_variant = o.m_variant;
    m_visited = o.m_visited;
    return *this;
}

bool Block::isEmpty() const
{
    return m_variant == 0;
}

int Block::getVariant() const
{
    return m_variant;
}

const char *Block::getImageName() const
{
    switch (m_variant) {
    case VariantRed:
        return "block-red.png";
    case VariantGreen:
        return "block-green.png";
    case VariantBlue:
        return "block-blue.png";
    default:
        return "";
    }
}

bool Block::isVisited() const
{
    return m_visited;
}

void Block::setVisited(bool visited)
{
    m_visited = visited;
}

bool Block::operator ==(const Block &o) const
{
    return m_variant == o.m_variant;
}

bool Block::operator !=(const Block &o) const
{
    return m_variant != o.m_variant;
}
