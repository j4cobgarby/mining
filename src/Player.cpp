#include "include/Player.hpp"

Player::Player() {
    Player(0, 0);
}

Player::Player(float x, float y) {
    rect = sf::Sprite(animation_register.at("player_normal_idle").at(0));
    rect.scale(0.2, 0.2);
    rect.setPosition(sf::Vector2f(x, y));

    vx = 0; vy = 0;
}

/**
 * Does the player collide with this block?
 */
bool Player::overlaps(const unsigned int block_index_x, const unsigned int block_index_y, const float dvx, const float dvy) {
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
void Player::trymove(LevelData lvl_dat, sf::Time delta) {
    bool will_hit_x = false;
    bool will_hit_y = false;
    bool movingdown = vy > 0;

    int tiles_x = 6;
    int tiles_y = 6;

    int start_x = (rect.getPosition().x-3)/BLOCK_SIZE;
    start_x = max(0, min(start_x, LEVEL_WIDTH-tiles_x));

    int start_y = (rect.getPosition().y-3)/BLOCK_SIZE;
    start_y = max(0, min(start_y, LEVEL_HEIGHT-tiles_y));

    float pos_x = rect.getPosition().x, pos_y = rect.getPosition().y;

    float vxd = vx * delta.asSeconds();
    float vyd = vy * delta.asSeconds();

    for (int r = start_y, i = 0; r < start_y + tiles_y; r++) {
        for (int c = start_x; c < start_x + tiles_x; c++, i++) {
            if (lvl_dat.blocks[r][c] != 0) {
                /** Try x-movement */
                if (overlaps(c, r, vxd, 0)) {
                    will_hit_x = true;
                    vx = 0;
                }
                /** Try y-movement */
                if (overlaps(c, r, 0, vyd)) {
                    will_hit_y = true;
                    vy = 0;
                }
            }
        }
    }
    if (will_hit_x);
    else {
        rect.setPosition(rect.getPosition().x + vx*delta.asSeconds(), rect.getPosition().y);
        if (rect.getPosition().x <= 0) rect.setPosition(sf::Vector2f(0.001, rect.getPosition().y));
        if (rect.getPosition().x >= LEVEL_WIDTH*BLOCK_SIZE-PLAYER_WIDTH) rect.setPosition(sf::Vector2f(LEVEL_WIDTH*BLOCK_SIZE-PLAYER_WIDTH-0.001, rect.getPosition().y));
    }

    if (will_hit_y) { // This does fire WHILE you're on the floor, not only as you hit it
        jumping = false;
        if (movingdown) {
            grounded = true;
        }
    }
    else {
        grounded = false;
        rect.setPosition(rect.getPosition().x, rect.getPosition().y + vy*delta.asSeconds());
    }
}

void Player::click(sf::Event ev, sf::RenderWindow *window, LevelData *lvl_dat, sf::RectangleShape *rects) {
    int block_x = floor(window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x);
    int block_y = floor(window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y);
    if (block_x % 2 != 0) block_x -= 1;
    if (block_y % 2 != 0) block_y -= 1;
    block_x /= 2;
    block_y /= 2;

    const uint8_t clicked_id = lvl_dat->blocks[block_y][block_x]; 

    const sf::Vector2f player_center = rect.getPosition();
    switch (ev.mouseButton.button) {
        case sf::Mouse::Left:
            if (block_x < LEVEL_WIDTH && block_y < LEVEL_HEIGHT && 
                    block_x >= 0 && block_y >= 0 && 
                    clicked_id != 0 &&
                    (
                        pow(max((float)block_x*2,player_center.x) - min((float)block_x*2,player_center.x), 2) +
                        pow(max((float)block_y*2,player_center.y) - min((float)block_y*2,player_center.y), 2)
                        <= 49 * BLOCK_SIZE
                    )) {
                lvl_dat->blocks[block_y][block_x] = 0;
                rects[block_y*LEVEL_WIDTH+block_x].setFillColor(sf::Color::Transparent);
            }
            break;
        case sf::Mouse::Right:
            {
            if (block_x < LEVEL_WIDTH && block_y < LEVEL_HEIGHT && 
                    block_x >= 0 && block_y >= 0 && 
                    clicked_id == 0 && 
                    !overlaps(block_x, block_y, 0, 0) &&
                    (
                        // If the sum of the adjacent blocks is greater than zero
                        // then there is at least one adjacent block
                        lvl_dat->blocks[block_y-1][block_x-1] + // top left
                        lvl_dat->blocks[block_y-1][block_x] + // top mid
                        lvl_dat->blocks[block_y-1][block_x+1] + // top right
                        lvl_dat->blocks[block_y][block_x-1] + // mid left
                        // we're not checking the middle block, which would be here
                        lvl_dat->blocks[block_y][block_x+1] + // mid right
                        lvl_dat->blocks[block_y+1][block_x-1] + // bottom left
                        lvl_dat->blocks[block_y+1][block_x] + // bottom mid
                        lvl_dat->blocks[block_y+1][block_x+1] // bottom right
                        > 0
                    ) &&
                    (
                        // Check if the block is close enough to the center of the player
                        pow(max((float)block_x*2,player_center.x) - min((float)block_x*2,player_center.x), 2) +
                        pow(max((float)block_y*2,player_center.y) - min((float)block_y*2,player_center.y), 2)
                        <= 49 * BLOCK_SIZE
                    )) {
                lvl_dat->blocks[block_y][block_x] = 2;
                rects[block_y*LEVEL_WIDTH+block_x] = sf::RectangleShape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                rects[block_y*LEVEL_WIDTH+block_x].setPosition(sf::Vector2f(block_x*BLOCK_SIZE, block_y*BLOCK_SIZE));
                rects[block_y*LEVEL_WIDTH+block_x].setFillColor(sf::Color::White);
                rects[block_y*LEVEL_WIDTH+block_x].setTexture(&tilemap_register.at(2));
            }
            }
            break;
        default: break;
    }
}

void Player::move(LevelData lvl_dat, sf::Time delta) {
    if (!debugflight) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) vx -= MOVEMENT_SPEED * delta.asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) vx += MOVEMENT_SPEED * delta.asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !jumping && grounded
                && jumpclock.getElapsedTime().asSeconds() >= JUMP_COOLDOWN) {
            jumping = true;
            vy -= JUMP_FORCE;
            jumpclock.restart();
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            jumping = false;
        }
        if (jumping) {
            if (abs(vy) < 10) {
                jumping = false;
            }
        }

        if (!jumping) vy += GRAVITY * delta.asSeconds();

        float scaled_damping = pow(0.998, delta.asSeconds() * 3500);
        vx *= scaled_damping;
        vy *= scaled_damping;

        trymove(lvl_dat, delta);
    } else {
        // this means flying using ijkl keys, through blocks
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            rect.setPosition(sf::Vector2f(rect.getPosition().x, rect.getPosition().y-GODFLY_SPEED));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            rect.setPosition(sf::Vector2f(rect.getPosition().x, rect.getPosition().y+GODFLY_SPEED));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
            rect.setPosition(sf::Vector2f(rect.getPosition().x-GODFLY_SPEED, rect.getPosition().y));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            rect.setPosition(sf::Vector2f(rect.getPosition().x+GODFLY_SPEED, rect.getPosition().y));
    }
}

void Player::draw(sf::RenderWindow *window) {
    window->draw(rect);
}

void Player::apply_impulse(const float x, const float y) {
    vx += x;
    vy += y;
}