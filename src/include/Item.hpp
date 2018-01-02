#ifndef INCLUDE_ITEM_HPP
#define INCLUDE_ITEM_HPP

#define DEFAULT_MAX_STACK_SIZE 128

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <iostream>

enum ItemRarity {
    DEFAULT, // <-- default items
    COMMON,
    UNCOMMON,
    RARE,
    EXTREMELY_RARE,
    GODLY,
};

class Item {
private:
    const ItemRarity rarity = COMMON;
    const unsigned short int max_stack_size = DEFAULT_MAX_STACK_SIZE;
    bool is_block = false;
public:
    Item();

    sf::Sprite sprite;

    ItemRarity getRarity() const {return rarity;}
    unsigned short int getMaxStackSize() const {return max_stack_size;}

    virtual void leftclick() = 0;
    virtual void rightclick() = 0;
    virtual inline bool canBreakBlock(size_t block_id) = 0;
    virtual inline bool canHarvestBlock(size_t block_id) = 0;
};

#endif