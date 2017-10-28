#include "scenes/MainMenu.hpp"

MainMenu::MainMenu(sf::RenderWindow *window) : window(window) {
    title = sf::Text("MAIN MENU",
        font_register.at("bold"));
    title.setCharacterSize(30);
    title.setPosition(sf::Vector2f(30, 30));
    title.setFillColor(sf::Color::Yellow);

    text = sf::Text(
        "Press 'G' to generate a new world\nPress 'L' to load an already made world", 
        font_register.at("regular"));
    text.setCharacterSize(30);
    text.setPosition(sf::Vector2f(30, 80));

    testcb = ptrTestCB(&text);
    testBtn = Button(&testcb, sf::Text("Hello, world!", font_register.at("regular")),
        sf::Vector2f(30, 170), sf::Vector2f(300, 40));
}

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
        if (ev.type == sf::Event::MouseButtonPressed) {
            if (ev.mouseButton.button == sf::Mouse::Left) {
                testBtn.test(ev.mouseButton.x, ev.mouseButton.y);
            }
        }
    }

    window->clear();
    window->draw(title);
    window->draw(text);

    testBtn.draw(window);

    window->display();

    return -1;
}