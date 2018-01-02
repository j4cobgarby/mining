#include "include/Block.hpp"

Block::Block() {
    setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));   
}

void Block::setSize(const sf::Vector2f& size) {
    m_size = size;
    update();
}

const sf::Vector2f& Block::getSize() const {
    return m_size;
}

size_t Block::getPointCount() const {
    return 4;
}

sf::Vector2f Block::getPoint(size_t index) const {
    switch (index)
    {
        default:
        case 0: return sf::Vector2f(0, 0);
        case 1: return sf::Vector2f(m_size.x, 0);
        case 2: return sf::Vector2f(m_size.x, m_size.y);
        case 3: return sf::Vector2f(0, m_size.y);
    }
}