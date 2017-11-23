#ifndef INCLUDE_PLAYER_HPP
#define INCLUDE_PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "LevelData.hpp"

using std::min;
using std::max;

/** Bounding box of player **/
#define PLAYER_HEIGHT 3.8
#define PLAYER_WIDTH 1.6

class Player {
private:
    float ax, ay, vx, vy;
    bool overlaps(int, int, float, float);
    void trymove(LevelData);
public:
    Player();
    Player(float, float);

    sf::RectangleShape rect;

    void move(LevelData);
    void draw(sf::RenderWindow*);
};

#endif