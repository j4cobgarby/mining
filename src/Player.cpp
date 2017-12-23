#include "include/Player.hpp"

Player::Player() {
    Player(0, 0);
}

Player::Player(float x, float y) {
    anim.setFrameTime(sf::seconds(0.6));

    anim.setPosition(x, y);
    anim.setScale(0.2, 0.2);
    anim.setOrigin(2, 0);
    
    vx = 0; vy = 0;
}

/**
 * Will the player collide with this block?
 */
bool Player::overlaps(const unsigned int block_index_x, const unsigned int block_index_y, 
        const float dvx, const float dvy) {
    float newx = anim.getPosition().x + dvx;
    float newy = anim.getPosition().y + dvy;
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

    int start_x = (anim.getPosition().x-3)/BLOCK_SIZE;
    start_x = max(0, min(start_x, LEVEL_WIDTH-tiles_x));

    int start_y = (anim.getPosition().y-3)/BLOCK_SIZE;
    start_y = max(0, min(start_y, LEVEL_HEIGHT-tiles_y));

    float pos_x = anim.getPosition().x, pos_y = anim.getPosition().y;

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
        anim.move(vxd, 0);
        if (anim.getPosition().x <= 0) anim.setPosition(0.001, anim.getPosition().y);
        if (anim.getPosition().x >= LEVEL_WIDTH*BLOCK_SIZE-PLAYER_WIDTH) anim.setPosition(LEVEL_WIDTH*BLOCK_SIZE-PLAYER_WIDTH-0.001, anim.getPosition().y);
    }

    if (will_hit_y) { // This does fire WHILE you're on the floor, not only as you hit it
        jumping = false;
        if (movingdown) {
            grounded = true;
        }
    }
    else {
        grounded = false;
        anim.move(0, vyd);
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

    const sf::Vector2f player_center = anim.getPosition();
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
    // left or right idle based on the velocity
    Animation* current_animation = &animation_register.at(facingright ? "player_default_idle_rt" : "player_default_idle_lt");
    sf::Time current_frametime = sf::seconds(0.6);

    if (!debugflight) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            facingright = false;
            vx -= MOVEMENT_SPEED * delta.asSeconds();
            current_animation = &animation_register.at("player_default_wlt");
            current_frametime = sf::seconds(0.05);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            facingright = true;
            vx += MOVEMENT_SPEED * delta.asSeconds();
            current_animation = &animation_register.at("player_default_wrt");
            current_frametime = sf::seconds(0.05);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !jumping && grounded
                && jumpclock.getElapsedTime().asSeconds() >= JUMP_COOLDOWN) {
            jumping = true;
            apply_impulse(0, -JUMP_FORCE);
            jumpclock.restart();
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            jumping = false;
        }
        if (jumping) {
            if (abs(vy) < 10) {
                jumping = false;
            }
        } else {
            vy += GRAVITY * delta.asSeconds();
        }

        float scaled_damping = pow(0.997, delta.asSeconds() * 3500);
        vx *= scaled_damping;
        vy *= scaled_damping;

        trymove(lvl_dat, delta);
    } else {
        // this means flying using ijkl keys, through blocks
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            anim.move(0, -GODFLY_SPEED);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            anim.move(0, GODFLY_SPEED);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
            anim.move(-GODFLY_SPEED, 0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            anim.move(+GODFLY_SPEED, 0);
    }

    anim.setFrameTime(current_frametime);
    anim.play(*current_animation);
    anim.update(delta);
}

void Player::draw(sf::RenderWindow *window) {
    window->draw(anim);
}

void Player::apply_impulse(const float x, const float y) {
    vx += x;
    vy += y;
}