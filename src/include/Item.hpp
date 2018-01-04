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
public:
    Item() {}

    sf::Sprite sprite;

    ItemRarity getRarity() const {return rarity;}
    unsigned short int getMaxStackSize() const {return max_stack_size;}

    virtual bool isBlock() = 0;

    virtual void leftclick() = 0;
    virtual void rightclick() = 0;
    virtual inline bool canBreakBlock(size_t block_id) = 0;
    virtual inline bool canHarvestBlock(size_t block_id) = 0;
};

class ItemBlock : public Item {
public:
    ItemBlock() {}

    void leftclick() {std::cout << "block l" << std::endl;}
    void rightclick() {std::cout << "block r" << std::endl;}
    inline bool canBreakBlock(size_t block_id) {return true;}
    inline bool canHarvestBlock(size_t block_id) {return false;}
};

#endif