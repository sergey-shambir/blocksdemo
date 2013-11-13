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
