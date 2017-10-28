#include "include/Button.hpp"

#include <iostream>

Button::Button() {std::cout << "Empty button init\n";}

Button::Button(CBInterface *callback, sf::Text text, sf::Vector2f position, sf::Vector2f size) :
callback(callback), text(text)
{
    bg = sf::RectangleShape(size);
    bg.setPosition(position);

    this->text.setFillColor(sf::Color::Black);
    this->text.setCharacterSize(size.y - 10);
    this->text.setPosition(sf::Vector2f(position.x + 10, position.y));
}

void Button::test(int mx, int my) {
    if (mx >= bg.getPosition().x &&
        mx <= bg.getPosition().x + bg.getSize().x &&
        my >= bg.getPosition().y &&
        my <= bg.getPosition().y + bg.getSize().y) {
            callback->cb();
    }
}

void Button::draw(sf::RenderWindow *window) {
    window->draw(bg);
    window->draw(text);
}