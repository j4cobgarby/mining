#include "include/InventorySlot.hpp"

InventorySlot::InventorySlot() {}

InventorySlot::InventorySlot(const uint8_t item_id, const unsigned short int amount) :
item_id(item_id), amount(amount)
{
    rect = sf::RectangleShape(sf::Vector2f(1, 1)); // will be resized when drawn
    rect.setFillColor(sf::Color(0xffffff80));
    rect.setOutlineColor(sf::Color(0x00000050));
    rect.setOutlineThickness(-SLOT_BORDER_DEFAULT);

    item_in_slot = itemptr_from_id(item_id);
}

void InventorySlot::setId(const uint8_t item_id) {
    this->item_id = item_id;
    item_in_slot = itemptr_from_id(item_id);
}

void InventorySlot::setAmount(const unsigned short int amount) {
    this->amount = amount;
}