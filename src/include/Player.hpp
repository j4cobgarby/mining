#ifndef SCENES_GAME_HPP
#define SCENES_GAME_HPP

#include <SFML/Graphics.hpp>
#include "LevelData.hpp"

/** Bounding box of player **/
#define PLAYER_HEIGHT 4.8
#define PLAYER_WIDTH 1.6

class Player {
private:
    sf::RectangleShape rect;
    float ax, ay, vx, vy;

    void overlaps(int, int, float, float);
    void trymove(LevelData);
public:
    Player();
    Player(float, float);

    void move(LevelData);
    void draw(sf::RenderWindow*);
};

#endif