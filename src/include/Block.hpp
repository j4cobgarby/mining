#ifndef INCLUDE_BLOCK_HPP
#define INCLUDE_BLOCK_HPP

#include <SFML/Graphics.hpp>
#include "LevelData.hpp"

class Block : public sf::RectangleShape {
public:
    explicit Block();

    void setSize(const sf::Vector2f& size);
    const sf::Vector2f& getSize() const;

    virtual std::size_t getPointCount() const;
    virtual sf::Vector2f getPoint(std::size_t index) const;
private:
    sf::Vector2f m_size;
};

#endif