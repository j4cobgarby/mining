#include "include/MainMenu.hpp"

MainMenu::MainMenu(sf::RenderWindow *window) : window(window) {}

void MainMenu::show() {
    std::cout << "Showing main menu\n";
}

void MainMenu::hide() {
    std::cout << "Hiding main menu\n";
}

int MainMenu::render(sf::Time delta) {
    sf::Event ev;
    while (window->pollEvent(ev)) {
        if (ev.type == sf::Event::Closed) window->close();
        if (ev.type == sf::Event::KeyPressed) {
            if (ev.key.code == sf::Keyboard::Escape) window->close();
        }
    }

    window->clear();
    window->display();

    return -1;
}