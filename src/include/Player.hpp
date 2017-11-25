#ifndef INCLUDE_PLAYER_HPP
#define INCLUDE_PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "LevelData.hpp"

using std::min;
using std::max;

/** Bounding box of player **/
#define PLAYER_HEIGHT 3.3
#define PLAYER_WIDTH 1.6

#define MOVEMENT_ACCELERATION 0.00004
#define JUMP_FORCE 0.04

class Player {
private:
    float vx, vy;
    bool overlaps(int, int, float, float);
    void trymove(LevelData);

    bool grounded = true;
public:
    Player();
    Player(float, float);

    sf::RectangleShape rect;

    void move(LevelData, sf::Time);
    void draw(sf::RenderWindow*);
};

#endif