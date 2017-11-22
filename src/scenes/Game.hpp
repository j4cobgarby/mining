#ifndef SCENES_GAME_HPP
#define SCENES_GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <fstream>

#include "../include/Scene.hpp"
#include "../include/assetregisters.hpp"
#include "../include/LevelData.hpp"
#include "../include/SessionConfig.hpp"
#include "../include/Player.hpp"
#include "../thirdparty/FastNoise.h"

class Game : public Scene {
private:
    sf::RenderWindow *window;
    sf::View view;
    LevelData lvl_dat;
    int *feedback;
    Player p;
    sf::RectangleShape blocks[LEVEL_HEIGHT * LEVEL_WIDTH];
public:
    Game(sf::RenderWindow*, int*);

    void show();
    void hide();
    void render(sf::Time);
};

#endif