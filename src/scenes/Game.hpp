#ifndef SCENES_GAME_HPP
#define SCENES_GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../include/Scene.hpp"
#include "../include/assetregisters.hpp"
#include "../include/LevelData.hpp"
#include "../include/SessionConfig.hpp"

class Game : public Scene {
private:
    sf::RenderWindow *window;
    sf::View view;
    LevelData lvl_dat;
    int *feedback;
public:
    Game(sf::RenderWindow*, int*);

    void show();
    void hide();
    void render(sf::Time);
};

#endif