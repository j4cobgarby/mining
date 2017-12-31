#ifndef INCLUDE_BLOCK_HPP
#define INCLUDE_BLOCK_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "LevelData.hpp"

class Block : public sf::RectangleShape {
public:
    explicit Block();

    void setSize(const sf::Vector2f& size);
    const sf::Vector2f& getSize() const;

    std::size_t getPointCount() const;
    sf::Vector2f getPoint(std::size_t index) const;

    virtual void interact() = 0;
private:
    sf::Vector2f m_size;
};

#endif