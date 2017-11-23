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
    return !(newx + PLAYER_WIDTH < block_index_x*BLOCK_SIZE-BLOCK_SIZE/2
        || newx > block_index_x*BLOCK_SIZE+BLOCK_SIZE-BLOCK_SIZE/2
        || newy + PLAYER_HEIGHT < block_index_y*BLOCK_SIZE-BLOCK_SIZE/2
        || newy > block_index_y*BLOCK_SIZE+BLOCK_SIZE-BLOCK_SIZE/2);
}

/**
 * Moves the player as far as he can go with the current velocity
 */
void Player::trymove(LevelData lvl_dat) {
    bool will_hit_x = false;
    bool will_hit_y = false;

    int tiles_x = 6;
    int tiles_y = 6;

    int start_x = (rect.getPosition().x-3)/BLOCK_SIZE;
    start_x = max(0, min(start_x, LEVEL_WIDTH-tiles_x-2));

    int start_y = (rect.getPosition().y-3)/BLOCK_SIZE;
    start_y = max(0, min(start_y, LEVEL_HEIGHT-tiles_y-2));

    for (int r = start_y, i = 0; r < start_y + tiles_y; r++) {
        for (int c = start_x; c < start_x + tiles_x; c++, i++) {
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ax -= 0.0004;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ax += 0.0004;

    ay += 3e-4;

    ax *= 0.99;
    ay *= 0.99;
    vx = ax;
    vy = ay;
    vx *= 0.999;
    vy *= 0.999;

    trymove(lvl_dat);
}

void Player::draw(sf::RenderWindow *window) {
    window->draw(rect);
}