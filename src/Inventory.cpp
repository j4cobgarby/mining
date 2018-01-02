#include "include/Inventory.hpp"

Inventory::Inventory() { 
}

void Inventory::init(sf::RenderWindow& window) {
    for (std::size_t y = 0; y < INVENTORY_ITEMS_Y; y++) {
        for (std::size_t x = 0; x < INVENTORY_ITEMS_X; x++) {
            slots[y][x] = InventorySlot(0, 0);
        }
    }
    slots[0][2].setId(13);
    slots[3][3].setId(14);

    border.setOutlineColor(sf::Color::Black);
    border.setOutlineThickness(1);
    border.setFillColor(sf::Color::Transparent);

    pocket_border.setOutlineColor(sf::Color::Black);
    pocket_border.setOutlineThickness(4);
    pocket_border.setFillColor(sf::Color::Transparent);

    update(window);
}

void Inventory::update(sf::RenderWindow& window) {
    sf::Vector2f totalsize = (sf::Vector2f)window.getSize() - sf::Vector2f(
        INVENTORY_WINDOW_PADDING_E + INVENTORY_WINDOW_PADDING_W, 
        INVENTORY_WINDOW_PADDING_S + INVENTORY_WINDOW_PADDING_N);
    float slotsize = min(MAX_SLOTSIZE, min(totalsize.x / INVENTORY_ITEMS_X, totalsize.y / INVENTORY_ITEMS_Y));

    sf::Vector2f topleft;
    if (open) topleft = sf::Vector2f(INVENTORY_WINDOW_PADDING_W, INVENTORY_WINDOW_PADDING_N);
    else topleft = sf::Vector2f(INVENTORY_WINDOW_PADDING_W, INVENTORY_WINDOW_PADDING_N - slotsize * (INVENTORY_ITEMS_Y-1));

    border.setSize(sf::Vector2f(slotsize * INVENTORY_ITEMS_X, slotsize * INVENTORY_ITEMS_Y));
    border.setPosition(topleft);

    pocket_border.setSize(sf::Vector2f(slotsize*INVENTORY_ITEMS_X, slotsize));
    pocket_border.setPosition(topleft + sf::Vector2f(0, slotsize*(INVENTORY_ITEMS_Y-1)));

    for (std::size_t y = 0; y < INVENTORY_ITEMS_Y; y++) {
        for (std::size_t x = 0; x < INVENTORY_ITEMS_X; x++) {
            slots[y][x].rect.setPosition(sf::Vector2f(x*slotsize + topleft.x, y*slotsize + topleft.y));
            slots[y][x].rect.setSize(sf::Vector2f(slotsize, slotsize));
            slots[y][x].item_in_slot->sprite.setPosition(
                topleft.x+x*slotsize + slotsize/10, 
                topleft.y+y*slotsize + slotsize/10);
            slots[y][x].item_in_slot->sprite.setScale(slotsize/10, slotsize/10);
        }
    }
}

void Inventory::draw(sf::RenderWindow& window) {
    sf::View game_view = window.getView();
    sf::View ui_view(sf::Vector2f(window.getSize().x*0.5, window.getSize().y*0.5), (sf::Vector2f)window.getSize());
    window.setView(ui_view);

    sf::Vector2i mpos = sf::Mouse::getPosition(window);
    
    if (open) {
        for (std::size_t y = 0; y < INVENTORY_ITEMS_Y; y++) {
            for (std::size_t x = 0; x < INVENTORY_ITEMS_X; x++) {
                slots[y][x].highlight_if_mouseover(window, mpos);
                if (tomove_x > -1) { // something's selected
                    slots[tomove_y][tomove_x].rect.setOutlineThickness(-SLOT_BORDER_SELECTED);
                }
                window.draw(slots[y][x].rect); // slot background
                window.draw(slots[y][x].item_in_slot->sprite);
            }
        }
        window.draw(border);
    } else {
        for (std::size_t x = 0; x < INVENTORY_ITEMS_X; x++) {
            slots[INVENTORY_ITEMS_Y-1][x].highlight_if_mouseover(window, mpos);
            if (tomove_x > -1) { // something's selected
                slots[tomove_y][tomove_x].rect.setOutlineThickness(-SLOT_BORDER_SELECTED);
            }
            window.draw(slots[INVENTORY_ITEMS_Y-1][x].rect); // slot background
            window.draw(slots[INVENTORY_ITEMS_Y-1][x].item_in_slot->sprite);
        }
    }
    window.draw(pocket_border);
    
    window.setView(game_view);
}

void Inventory::handle_click(sf::Event& ev, sf::RenderWindow& window) {
    if (ev.type == sf::Event::MouseButtonPressed) {
        if (ev.mouseButton.button == sf::Mouse::Button::Left) {
            if (open) {
                /**
                 * Handle movement of items, if the inv. is open
                 */
                for (size_t x = 0; x < INVENTORY_ITEMS_X; x++) {
                    for (size_t y = 0; y < INVENTORY_ITEMS_Y; y++) {
                        if (slots[y][x].rect.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y)) {
                            // click was on THIS slot!
                            if (tomove_x > -1) {
                                // something was already selected
                                // swap, then reset selection
                                int a_id, b_id;
                                a_id = slots[tomove_y][tomove_x].getId();
                                b_id = slots[y][x].getId();
                                std::cout << a_id << " --> " << b_id << std::endl;
                                slots[tomove_y][tomove_x].setId(b_id);
                                slots[y][x].setId(a_id);
                                tomove_x = -1;
                                tomove_y = -1;
                                update(window);
                            } else {
                                // nothing was selected
                                // just select
                                if (slots[y][x].getId() != 0) { // can't select what isn't there!
                                    tomove_x = x;
                                    tomove_y = y;
                                }
                            }
                        }
                    }
                }
            } else {
                /**
                 * only hotbar is visible, so select that item
                 */
            }
        }
    }
}