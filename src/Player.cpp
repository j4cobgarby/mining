#include "include/Player.hpp"

Player::Player() {
    Player(0, 0);
}

Player::Player(float x, float y) {
    rect = sf::RectangleShape(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
    rect.setPosition(sf::Vector2f(x, y));
    rect.setFillColor(sf::Color::Red);

    ax = 0; ay = 0;
    vx = 0; vy = 0;
}

/** 
 * Does the player collide with this block? 
 */
bool Player::overlaps(int block_index_x, int block_index_y, float dvx, float dvy) {
    float newx = rect.getPosition().x + dvx;
    float newy = rect.getPosition().y + dvy;
    return !(newx + PLAYER_WIDTH < block_index_x*BLOCK_SIZE 
        || newx > block_index_x*BLOCK_SIZE+BLOCK_SIZE
        || newy + PLAYER_HEIGHT < block_index_y*BLOCK_SIZE
        || newy > block_index_y*BLOCK_SIZE+BLOCK_SIZE);
}

/**
 * Moves the player as far as he can go with the current velocity
 */
void Player::trymove(LevelData lvl_dat) {
    bool will_hit_x = false;
    bool will_hit_y = false;
    for (size_t r = 0, i = 0; r < LEVEL_HEIGHT; r++) {
        for (size_t c = 0; c < LEVEL_WIDTH; c++, i++) {
            if (lvl_dat.blocks[r][c] != 0) {
                if (overlaps(c, r, vx, 0)) will_hit_x = true;
                if (overlaps(c, r, 0, vy)) will_hit_y = true;
            }
        }
    }
    if (!will_hit_x) rect.setPosition(rect.getPosition().x + vx, rect.getPosition().y);
    if (!will_hit_y) rect.setPosition(rect.getPosition().x, rect.getPosition().y + vy);
}

void Player::move(LevelData lvl_dat) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ay -= 0.02;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) ay += 0.02;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ax -= 0.02;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ax += 0.02;

    ax *= 0.999;
    ay *= 0.999;
    vx = ax;
    vy = ay;
    vx *= 0.8;
    vy *= 0.8;

    trymove(lvl_dat);
}