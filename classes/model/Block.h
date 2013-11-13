#ifndef BLOCK_H
#define BLOCK_H

#include <string>

class Block
{
public:
    static Block randomBlock();
    Block();
    Block(const Block &o);
    Block &operator =(const Block &o);

    bool isEmpty() const;
    int getVariant() const;
    const char *getImageName() const;

    bool isVisited() const;
    void setVisited(bool visited);

    bool operator ==(const Block &o) const;
    bool operator !=(const Block &o) const;

private:
    int m_variant;
    bool m_visited;
};

#endif // BLOCK_H
