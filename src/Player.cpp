#include "include/Player.hpp"

Player::Player() {
    Player(0, 0);
}

Player::Player(float x, float y) {
    rect = sf::RectangleShape(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
    rect.setPosition(sf::Vector2f(x, y));
    rect.setFillColor(sf::Color::Red);

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

    int tiles_x = 6;
    int tiles_y = 6;

    int start_x = (rect.getPosition().x-3)/BLOCK_SIZE;
    start_x = max(0, min(start_x, LEVEL_WIDTH-tiles_x));

    int start_y = (rect.getPosition().y-3)/BLOCK_SIZE;
    start_y = max(0, min(start_y, LEVEL_HEIGHT-tiles_y));

    for (int r = start_y, i = 0; r < start_y + tiles_y; r++) {
        for (int c = start_x; c < start_x + tiles_x; c++, i++) {
            if (lvl_dat.blocks[r][c] != 0) {
                if (overlaps(c, r, vx, 0)) {
                    will_hit_x = true;
                    vx = 0;
                }
                if (overlaps(c, r, 0, vy)) {
                    will_hit_y = true;
                    vy = 0;
                }
            }
        }
    }
    if (!will_hit_x) rect.setPosition(rect.getPosition().x + vx, rect.getPosition().y);
    if (!will_hit_y) rect.setPosition(rect.getPosition().x, rect.getPosition().y + vy);
}

void Player::click(sf::Event ev, sf::RenderWindow *window, LevelData *lvl_dat, sf::RectangleShape *rects) {
    int block_x = floor(window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x);
    int block_y = floor(window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y);
    if (block_x % 2 != 0) block_x -= 1;
    if (block_y % 2 != 0) block_y -= 1;
    block_x /= 2;
    block_y /= 2;

    switch (ev.mouseButton.button) {
        case sf::Mouse::Left:
            if (block_x < LEVEL_WIDTH && block_y < LEVEL_HEIGHT && block_x >= 0 && block_y >= 0) {
                std::cout << block_x << '\t' << block_y << std::endl;
                lvl_dat->blocks[block_y][block_x] = 0;
                rects[block_y*LEVEL_WIDTH+block_x].setFillColor(sf::Color::Transparent);
            }
            break;
        case sf::Mouse::Right:
            if (block_x < LEVEL_WIDTH && block_y < LEVEL_HEIGHT && block_x >= 0 && block_y >= 0) {
                std::cout << block_x << '\t' << block_y << std::endl;
                lvl_dat->blocks[block_y][block_x] = 2;
                rects[block_y*LEVEL_WIDTH+block_x] = sf::RectangleShape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                rects[block_y*LEVEL_WIDTH+block_x].setPosition(sf::Vector2f(block_x*BLOCK_SIZE, block_y*BLOCK_SIZE));
                rects[block_y*LEVEL_WIDTH+block_x].setFillColor(sf::Color::White);
                rects[block_y*LEVEL_WIDTH+block_x].setTexture(&tilemap_register.at(2));
            }
            break;
        default: break;
    }
}

void Player::move(LevelData lvl_dat, sf::Time delta) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) vx -= MOVEMENT_ACCELERATION;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) vx += MOVEMENT_ACCELERATION;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        jumping = true;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        jumping = false;
    }

    if (jumping)
        vy -= JUMP_INCR;
    else
        vy += GRAVITY;

    vx *= 0.995;
    vy *= 0.995;
    vx *= delta.asSeconds() * 100;
    vy *= delta.asSeconds() * 100;
    trymove(lvl_dat);
}

void Player::draw(sf::RenderWindow *window) {
    window->draw(rect);
}
