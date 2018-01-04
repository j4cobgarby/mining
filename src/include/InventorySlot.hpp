#ifndef INCLUDE_INVENTORYSLOT
#define INCLUDE_INVENTORYSLOT

#include <SFML/Graphics.hpp>

#include "assetregisters.hpp"
#include "ItemTypes.hpp"

#define SLOT_BORDER_DEFAULT 0.5
#define SLOT_BORDER_HOVERED 2.5
#define SLOT_BORDER_SELECTED 2

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

    void setBlock(const bool is_a_block);
    bool isBlock() {return item_in_slot->isBlock();}

    void setAmount(const unsigned short int amount);
    unsigned short int getAmount() const {return amount;}

    inline void highlight_if_mouseover(sf::RenderWindow& window, sf::Vector2i& mpos) {
        if (rect.getGlobalBounds().contains(mpos.x, mpos.y)) {
            rect.setOutlineThickness(-SLOT_BORDER_HOVERED);
        } else {
            rect.setOutlineThickness(-SLOT_BORDER_DEFAULT);
        }
    }
};

#endif