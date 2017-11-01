#include "scenes/MainMenu.hpp"

MainMenu::MainMenu(sf::RenderWindow *window, int *feedback) : window(window), feedback(feedback) {
    view.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    view.setCenter(sf::Vector2f(window->getSize().x/2, window->getSize().y/2));

    gui.setWindow(*window);
    gui.setView(sf::View{});
    gui.setView(view);

    tgui::Button::Ptr playbtn = tgui_theme->load("Button");
    playbtn->setText("Play");
    playbtn->setPosition(0.3 * bindWidth(gui), 0.25 * bindWidth(gui) + 80);
    playbtn->setSize(bindWidth(gui) * 0.4, 40);
    playbtn->setFont(font_register.at("bold"));
    playbtn->setTextSize(20);
    // On press, change active scene
    playbtn->connect("pressed", [this](){*this->feedback = 1;});

    tgui::Button::Ptr settingsbtn = tgui_theme->load("Button");
    settingsbtn->setText("Settings");
    settingsbtn->setPosition(bindLeft(playbtn), bindBottom(playbtn) + 40 + 20);
    settingsbtn->setSize(bindSize(playbtn));
    settingsbtn->setFont(font_register.at("bold"));
    settingsbtn->setTextSize(20);

    gui.add(playbtn, "playbtn");
    gui.add(settingsbtn, "settingsbtn");
}

void MainMenu::show() {
    std::cout << "Showing main menu\n";
    window->setSize(sf::Vector2u(1000, 1000));
    gui.setView(view);
    window->setView(view);
}

void MainMenu::hide() {
    std::cout << "Hiding main menu\n";
    window->setView(window->getDefaultView());
}

void MainMenu::render(sf::Time delta) {
    sf::Event ev;
    while (window->pollEvent(ev)) {
        gui.handleEvent(ev);

        if (ev.type == sf::Event::Closed) window->close();
        if (ev.type == sf::Event::KeyPressed) {
            if (ev.key.code == sf::Keyboard::Escape) window->close();
        }
    }

    view.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    view.setCenter(sf::Vector2f(window->getSize().x/2, window->getSize().y/2));
    gui.setView(view);
    window->setView(view);

    sf::Sprite title(texture_register.at("titlebig"));
    title.setPosition(sf::Vector2f(0, 40));
    title.setScale((float)window->getSize().x / (float)texture_register.at("titlebig").getSize().x,
        (float)window->getSize().x / (float)texture_register.at("titlebig").getSize().x);

        window->clear(sf::Color(0xedeff3ff));
    gui.draw();
    window->draw(title);
    window->display();
}