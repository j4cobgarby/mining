#include "include/InventorySlot.hpp"

InventorySlot::InventorySlot() {}

InventorySlot::InventorySlot(const unsigned short int item_id, const unsigned short int amount) :
item_id(item_id), amount(amount)
{
    rect = sf::RectangleShape(sf::Vector2f(1, 1)); // will be resized when drawn
    rect.setFillColor(sf::Color(0x0000ff40));
    rect.setOutlineColor(sf::Color(0x00000050));
    rect.setOutlineThickness(1);
}