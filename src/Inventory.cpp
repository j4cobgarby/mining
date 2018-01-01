#include "include/Inventory.hpp"

Inventory::Inventory() { 
}

void Inventory::init(sf::RenderWindow& window) {
    for (std::size_t y = 0; y < INVENTORY_ITEMS_Y; y++) {
        for (std::size_t x = 0; x < INVENTORY_ITEMS_X; x++) {
            slots[y][x] = InventorySlot(0, 0);
        }
    }
    //slots[0][0] = InventorySlot(1, 0);
    //slots[3][6] = InventorySlot(13, 0);
    //slots[3][6].setId(10);
    slots[0][2].setId(11);
    slots[3][3].setId(12);
    //slots[6][3].setId(11);

    border.setOutlineColor(sf::Color::Black);
    border.setOutlineThickness(1);
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
            slots[y][x].item_in_slot->sprite.setPosition(
                topleft.x+x*slotsize + slotsize/10, 
                topleft.y+y*slotsize + slotsize/10);
            slots[y][x].item_in_slot->sprite.setScale(slotsize/10, slotsize/10);
        }
    }
}

void Inventory::draw(sf::RenderWindow& window) {
    if (open) {
        sf::View game_view = window.getView();
        sf::View ui_view(sf::Vector2f(window.getSize().x*0.5, window.getSize().y*0.5), (sf::Vector2f)window.getSize());
        window.setView(ui_view);

        for (std::size_t y = 0; y < INVENTORY_ITEMS_Y; y++) {
            for (std::size_t x = 0; x < INVENTORY_ITEMS_X; x++) {
                slots[y][x].highlight_if_mouseover(window);
                if (selected_x > -1) { // something's selected
                    slots[selected_y][selected_x].rect.setOutlineThickness(SLOT_BORDER_SELECTED);
                }
                window.draw(slots[y][x].rect); // slot background
                window.draw(slots[y][x].item_in_slot->sprite);
            }
        }
        window.draw(border);
        window.setView(game_view);
    }
}

void Inventory::handle_click(sf::Event& ev, sf::RenderWindow& window) {
    if (ev.type == sf::Event::MouseButtonPressed) {
        for (size_t x = 0; x < INVENTORY_ITEMS_X; x++) {
            for (size_t y = 0; y < INVENTORY_ITEMS_Y; y++) {
                if (slots[y][x].rect.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y)) {
                    // click was on THIS slot!
                    if (selected_x > -1) {
                        // something was already selected
                        // swap, then reset selection
                        int a_id, b_id;
                        a_id = slots[selected_y][selected_x].getId();
                        b_id = slots[y][x].getId();
                        std::cout << a_id << " --> " << b_id << std::endl;
                        slots[selected_y][selected_x].setId(b_id);
                        slots[y][x].setId(a_id);
                        selected_x = -1;
                        selected_y = -1;
                        on_resize(window);
                    } else {
                        // nothing was selected
                        // just select
                        selected_x = x;
                        selected_y = y;
                    }
                }
            }
        }
    }
}