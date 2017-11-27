#ifndef INCLUDE_PLAYER_HPP
#define INCLUDE_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "LevelData.hpp"
#include "assetregisters.hpp"

using std::min;
using std::max;

/** Bounding box of player **/
#define PLAYER_HEIGHT 3.3
#define PLAYER_WIDTH 1.6

#define MOVEMENT_ACCELERATION 0.16
#define JUMP_FORCE 160
#define JUMP_INCR 0.3
#define GRAVITY 0.2

class Player {
private:
    float ax, ay, vx, vy;
    bool overlaps(int, int, float, float);
    void trymove(LevelData);

    bool jumping = false;
    bool grounded = true;
public:
    Player();
    Player(float, float);

    sf::RectangleShape rect;

    void click(sf::Event, sf::RenderWindow*, LevelData*, sf::RectangleShape*);
    void move(LevelData, sf::Time);
    void draw(sf::RenderWindow*);
};

#endif
