#ifndef SCENES_GAME_HPP
#define SCENES_GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../include/Scene.hpp"
#include "../include/assetregisters.hpp"

class Game : public Scene {
private:
    sf::RenderWindow *window;
public:
    Game(sf::RenderWindow*);

    void show();
    void hide();
    void render(sf::Time);
};

#endif