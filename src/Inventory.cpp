#include "include/Inventory.hpp"

Inventory::Inventory() { 
}

void Inventory::init(sf::RenderWindow& window) {
    for (std::size_t y = 0; y < INVENTORY_ITEMS_Y; y++) {
        for (std::size_t x = 0; x < INVENTORY_ITEMS_X; x++) {
            slots[y][x] = InventorySlot(0, 0);
        }
    }

    border.setOutlineColor(sf::Color::Black);
    border.setOutlineThickness(2);
    border.setFillColor(sf::Color::Transparent);

    on_resize(window);
}

void Inventory::on_resize(sf::RenderWindow& window) {
    sf::Vector2f topleft(INVENTORY_WINDOW_PADDING_W, INVENTORY_WINDOW_PADDING_N);
    sf::Vector2f totalsize = (sf::Vector2f)window.getSize() - sf::Vector2f(
        INVENTORY_WINDOW_PADDING_E + INVENTORY_WINDOW_PADDING_W, 
        INVENTORY_WINDOW_PADDING_S + INVENTORY_WINDOW_PADDING_N);
    float slotsize = min(totalsize.x / INVENTORY_ITEMS_X, totalsize.y / INVENTORY_ITEMS_Y);

    border.setSize(sf::Vector2f(slotsize * INVENTORY_ITEMS_X, slotsize * INVENTORY_ITEMS_Y));
    border.setPosition(topleft);

    for (std::size_t y = 0; y < INVENTORY_ITEMS_Y; y++) {
        for (std::size_t x = 0; x < INVENTORY_ITEMS_X; x++) {
            slots[y][x].rect.setPosition(sf::Vector2f(x*slotsize + INVENTORY_WINDOW_PADDING_W, y*slotsize + INVENTORY_WINDOW_PADDING_N));
            slots[y][x].rect.setSize(sf::Vector2f(slotsize, slotsize));
        }
    }
}

void Inventory::draw(sf::RenderWindow& window) {
    if (!open) return;

    sf::View game_view = window.getView();
    sf::View ui_view(sf::Vector2f(window.getSize().x*0.5, window.getSize().y*0.5), (sf::Vector2f)window.getSize());
    window.setView(ui_view);

    for (std::size_t y = 0; y < INVENTORY_ITEMS_Y; y++) {
        for (std::size_t x = 0; x < INVENTORY_ITEMS_X; x++) {
            window.draw(slots[y][x].rect);
        }
    }
    window.draw(border);
    window.setView(game_view);
}