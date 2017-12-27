#ifndef INCLUDE_INVENTORY_HPP
#define INCLUDE_INVENTORY_HPP

////////////////////////////////////////////////////////////////////////////////
// amount of items to be displayed in the inventory window, on the x and y axes
#define INVENTORY_ITEMS_X 8
#define INVENTORY_ITEMS_Y 16
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// display stuff
#define INVENTORY_WINDOW_PADDING_N 15
#define INVENTORY_WINDOW_PADDING_S 15
#define INVENTORY_WINDOW_PADDING_E 15
#define INVENTORY_WINDOW_PADDING_W 15
////////////////////////////////////////////////////////////////////////////////

#include "InventorySlot.hpp"
#include <cstdint>

using std::min;
using std::max;

class Inventory {
private:
    bool open = false; // is the player looking in their inventory?

    InventorySlot slots[INVENTORY_ITEMS_Y][INVENTORY_ITEMS_X];
public:
    Inventory();

    void handle_input();
    void draw(sf::RenderWindow& window);
    void setOpen(const bool open) {this->open = open;}
    bool isOpen() const {return open;}
};

#endif