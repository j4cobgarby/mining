#ifndef INCLUDE_PLAYER_HPP
#define INCLUDE_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "LevelData.hpp"
#include "assetregisters.hpp"
#include "../thirdparty/AnimatedSprite.hpp"
#include "Block.hpp"
#include "Inventory.hpp"

using std::min;
using std::max;

/** Bounding box of player **/
// the actual player texture is 8x16, so divide both by a suitible
// divisor (5)a
// 1 texture px = 0.2 game size
#define PLAYER_HEIGHT 3.2
#define PLAYER_WIDTH 0.8
#define PLAYER_HEIGHT_OVER_2 1.6
#define PLAYER_WIDTH_OVER_2 0.4

#define JUMP_COOLDOWN 0.4 // cooldown between hitting the floor an being able to jump

#define MOVEMENT_SPEED 1.5e2
#define JUMP_FORCE 0.6e2
#define GRAVITY 3e2

#define GODFLY_SPEED 0.005

class Player { 
private:
    float vx, vy;
    bool overlaps(const unsigned int, const unsigned int, 
        const float, const float);
    void trymove(LevelData, sf::Time);

    bool facingright = true;
    bool jumping = false;
    bool grounded = false;
    sf::Clock jumpclock;
public:
    Player();
    Player(float, float);

    AnimatedSprite anim;
    Inventory inventory;

    bool debugflight = false;

    void click(sf::Event, sf::RenderWindow*, LevelData*, Block**);
    void move(LevelData, sf::Time);
    void draw(sf::RenderWindow*);
    void apply_impulse(const float x, const float y);
};

#endif  