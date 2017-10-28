#ifndef INCLUDE_BUTTON_HPP
#define INCLUDE_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "CBInterface.hpp"

class Button {
private:
    CBInterface *callback;
    sf::Text text;
    sf::RectangleShape bg;

    bool canclick = true;
public:
    Button();
    Button(CBInterface *callback, sf::Text text, sf::Vector2f position, sf::Vector2f size);

    void test(int mx, int my);
    void draw(sf::RenderWindow *window);
};

#endif