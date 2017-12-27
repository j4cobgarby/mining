#ifndef INCLUDE_INVENTORYSLOT
#define INCLUDE_INVENTORYSLOT

#include <SFML/Graphics.hpp>

#include "assetregisters.hpp"

class InventorySlot {
private:
    unsigned short int item_id;
    unsigned short int amount;
public:
    /**
     * An id of 0 means no item 
     */
    InventorySlot();
    InventorySlot(const unsigned short int item_id, const unsigned short int amount);

    sf::RectangleShape rect;

    void setId(const unsigned short int item_id) {this->item_id = item_id;}
    unsigned short int getId() const {return item_id;}

    void setAmount(const unsigned short int amount) {this->amount = amount;}
    unsigned short int getAmount() const {return amount;}
};

#endif