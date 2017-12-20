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
#define JUMP_COOLDOWN 0.4 // cooldown between hitting the floor an being able to jump

#define MOVEMENT_SPEED 1.5e2
#define JUMP_FORCE 0.6e2
#define GRAVITY 3e2

#define GODFLY_SPEED 0.005

enum PLAYER_ANIMATION_STATE {
    // normal
    normal_idle_1, normal_idle_2, // idle
    normal_wrt_1, normal_wrt_2, // walk right
    normal_wlt_1, normal_wlt_2, // walk left

    // hit flashing
    hit_idle_1, hit_idle_2,
    hit_wrt_1, hit_wrt_2,
    hit_wlt_1, hit_wlt_2,
};

class Player { 
private:
    float vx, vy;
    bool overlaps(const unsigned int, const unsigned int, 
        const float, const float);
    void trymove(LevelData, sf::Time);

    bool jumping = false;
    bool grounded = false;
    sf::Clock jumpclock;
public:
    Player();
    Player(float, float);

    sf::RectangleShape rect;

    bool debugflight = false;

    void click(sf::Event, sf::RenderWindow*, LevelData*, sf::RectangleShape*);
    void move(LevelData, sf::Time);
    void draw(sf::RenderWindow*);
    void apply_impulse(const float x, const float y);
};

#endif  