#include "scenes/LevelSelect.hpp"

namespace fs = experimental::filesystem;

LevelSelect::LevelSelect(sf::RenderWindow *window, int *feedback) : window(window), feedback(feedback) {
    view.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    view.setCenter(sf::Vector2f(window->getSize().x/2, window->getSize().y/2));

    gui.setWindow(*window);
    gui.setView(sf::View{});
    gui.setView(view);

    tgui::ListBox::Ptr levellist = tgui_theme->load("ListBox");
    levellist->setPosition(0.2 * bindWidth(gui), 30);
    levellist->setSize(bindWidth(gui) * 0.6, "max(parent.height - 130, 40)");
    levellist->setFont(font_register.at("regular"));

    tgui::Button::Ptr loadbtn = tgui_theme->load("Button");
    loadbtn->setPosition(0.3 * bindWidth(gui), bindBottom(levellist) + 30);
    loadbtn->setSize(bindWidth(gui) * 0.2, 40);
    loadbtn->setText("Load level");
    loadbtn->setFont(font_register.at("bold"));
    loadbtn->setTextSize(20);

    tgui::Button::Ptr makebtn = tgui_theme->load("Button");
    makebtn->setPosition(0.5 * bindWidth(gui), bindBottom(levellist) + 30);
    makebtn->setSize(bindWidth(gui) * 0.2, 40);
    makebtn->setText("New level");
    makebtn->setFont(font_register.at("bold"));
    makebtn->setTextSize(20);
    makebtn->connect("pressed", [this](){*this->feedback = 2;});

    fs::path worlds_path("../worlds");
    for (fs::directory_entry d : fs::directory_iterator(worlds_path))
        levellist->addItem(d.path().filename().string(), d.path().string());

    gui.add(levellist, "levellist");
    gui.add(loadbtn, "loadbtn");
    gui.add(makebtn, "makebtn");
}

void LevelSelect::show() {
    gui.setView(view);
    window->setView(view);
}

void LevelSelect::hide() {
    window->setView(window->getDefaultView());
}

void LevelSelect::render(sf::Time delta) {
    sf::Event ev;
    while (window->pollEvent(ev)) {
        gui.handleEvent(ev);

        if (ev.type == sf::Event::Closed) window->close();
        if (ev.type == sf::Event::KeyPressed) {
            if (ev.key.code == sf::Keyboard::Escape) window->close();
            if (ev.key.code == sf::Keyboard::P) {
                tgui::ListBox::Ptr ll = gui.get<tgui::ListBox>("levellist");
                std::cout << (std::string)ll->getSelectedItem() << std::endl;
            }
        }
    }

    view.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    view.setCenter(sf::Vector2f(window->getSize().x/2, window->getSize().y/2));
    gui.setView(view);
    window->setView(view);

    window->clear(sf::Color(0xedeff3ff));
    gui.draw();
    window->display();
}