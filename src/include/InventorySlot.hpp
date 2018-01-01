#ifndef INCLUDE_INVENTORYSLOT
#define INCLUDE_INVENTORYSLOT

#include <SFML/Graphics.hpp>

#include "assetregisters.hpp"
#include "ItemTypes.hpp"

#define SLOT_BORDER_DEFAULT 1
#define SLOT_BORDER_HOVERED 5
#define SLOT_BORDER_SELECTED 3

class InventorySlot {
private:
    uint8_t item_id;
    unsigned short int amount;
public:
    InventorySlot();
    InventorySlot(const uint8_t, const unsigned short int amount);

    sf::RectangleShape rect;
    Item* item_in_slot;

    void setId(const uint8_t item_id);
    uint8_t getId() const {return item_id;}

    void setAmount(const unsigned short int amount);
    unsigned short int getAmount() const {return amount;}

    inline void highlight_if_mouseover(sf::RenderWindow& window) {
        sf::Vector2i mpos = sf::Mouse::getPosition(window);
        if (rect.getGlobalBounds().contains(mpos.x, mpos.y)) {
            rect.setOutlineThickness(-SLOT_BORDER_HOVERED);
        } else {
            rect.setOutlineThickness(-SLOT_BORDER_DEFAULT);
        }
    }
};

#endif