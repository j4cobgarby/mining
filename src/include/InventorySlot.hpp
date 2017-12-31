#ifndef INCLUDE_INVENTORYSLOT
#define INCLUDE_INVENTORYSLOT

#include <SFML/Graphics.hpp>

#include "assetregisters.hpp"
#include "ItemTypes.hpp"

class InventorySlot {
private:
    uint8_t item_id;
    unsigned short int amount;
public:
    /**
     * An id of 0 means no item 
     */
    InventorySlot();
    InventorySlot(const uint8_t, const unsigned short int amount);

    sf::RectangleShape rect;
    Item* item_in_slot;

    void setId(const uint8_t item_id);
    uint8_t getId() const {return item_id;}

    void setAmount(const unsigned short int amount);
    unsigned short int getAmount() const {return amount;}
};

#endif