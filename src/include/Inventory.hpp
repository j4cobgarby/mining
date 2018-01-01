#ifndef INCLUDE_INVENTORY_HPP
#define INCLUDE_INVENTORY_HPP

////////////////////////////////////////////////////////////////////////////////
// amount of items to be displayed in the inventory window, on the x and y axes
#define INVENTORY_ITEMS_X 5
#define INVENTORY_ITEMS_Y 10
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// display stuff
#define INVENTORY_WINDOW_PADDING_N 15
#define INVENTORY_WINDOW_PADDING_S 15
#define INVENTORY_WINDOW_PADDING_E 15
#define INVENTORY_WINDOW_PADDING_W 15
////////////////////////////////////////////////////////////////////////////////

#include "InventorySlot.hpp"
#include "assetregisters.hpp"
#include <cstdint>

using std::min;
using std::max;

class Inventory {
private:
    bool open = false; // is the player looking in their inventory?

    sf::RectangleShape border;
public:
    Inventory();

    InventorySlot slots[INVENTORY_ITEMS_Y][INVENTORY_ITEMS_X];
    // x and y of selected item, -1 if no item selected
    short int selected_x = -1, selected_y = -1;

    void init(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);

    void handle_click(sf::Event& ev, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    void set_open(const bool open) {this->open = open;}
    bool is_open() const {return open;}
};

#endif