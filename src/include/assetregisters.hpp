#ifndef INCLUDE_ASSET_REGISTERS_HPP
#define INCLUDE_ASSET_REGISTERS_HPP

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <TGUI/TGUI.hpp>

#include "../thirdparty/AnimatedSprite.hpp"

#define ASSETS_ROOT_RAW "../assets/"
#define ASSETS_ROOT std::string(ASSETS_ROOT_RAW)

inline sf::Texture makeTexture(const std::string filename) {
    sf::Texture tex;
    tex.loadFromFile(filename);
    return tex;
}

inline sf::Texture makeTexture(const std::string filename, const sf::IntRect area) {
    sf::Texture tex;
    tex.loadFromFile(filename, area);
    return tex;
}

inline sf::Font makeFont(const std::string filename) {
    sf::Font fnt;
    fnt.loadFromFile(filename);
    return fnt;
}

/**
 * Returns a vector of Textures to describe an animation.
 *
 * The file which `filename` refers to must contain `frames` frames, all
 * `frame_width`px wide and `frame_height`px tall, in a straight horizontal
 * line with no offset and no padding.
 */
inline Animation makeAnimation(const sf::Texture& texture) {
    Animation ret;
    ret.setSpriteSheet(texture);
    return ret;
}

inline std::map<int, sf::Texture> init_tilemap_register(const std::string filename,
        const unsigned int tiles_x, const unsigned int tiles_y, // Amount of tiles on each axis
        const unsigned int tile_width, const unsigned int tile_height) { // Width in px of each tile texture
    std::map<int, sf::Texture> reg;
    unsigned short int index = 1;
    for (unsigned int y = 0; y < tiles_y; y++) {
        for (unsigned int x = 0; x < tiles_x; x++) {
            reg[index] = makeTexture(filename, sf::IntRect(tile_width*x, tile_height*y, tile_width, tile_height));
            index++;
        }
    }
    return reg;
}

extern std::map<int, sf::Texture>        tilemap_register;
extern std::map<std::string, sf::Texture>     texture_register;
extern std::map<std::string, sf::Font>        font_register;
extern std::map<std::string, Animation>   animation_register;
extern tgui::Theme::Ptr         tgui_theme;

#endif
