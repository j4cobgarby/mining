#include "scenes/LevelCreate.hpp"

namespace fs = experimental::filesystem;

/////////////////////////////////////////
// Level generation
/////////////////////////////////////////

void make_world(tgui::Gui *gui, int *feedback) {
    tgui::EditBox::Ptr eptr = gui->get<tgui::EditBox>("levelname_txtbox");
    std::string dirname = eptr->getText();

    if (dirname == "") {
        std::cout << "No dirname given\n";
        return;
    }

    fs::create_directories("../worlds/" + dirname + "/players");
    fs::create_directories("../worlds/" + dirname + "/data");

    //
    // change feedback to some other scene once the world is made
    //
}

/////////////////////////////////////////
// GUI
/////////////////////////////////////////

LevelCreate::LevelCreate(sf::RenderWindow *window, int *feedback) : window(window), feedback(feedback) {
    view.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    view.setCenter(sf::Vector2f(window->getSize().x/2, window->getSize().y/2));

    gui.setWindow(*window);
    gui.setView(sf::View{});
    gui.setView(view);

    tgui::Label::Ptr levelname_label = tgui_theme->load("Label");
    levelname_label->setText("Level name");
    levelname_label->setPosition("0.2 * &.w", 50);
    levelname_label->setFont(font_register.at("regular"));

    tgui::EditBox::Ptr levelname_txtbox = tgui_theme->load("EditBox");
    levelname_txtbox->setPosition("0.2 * &.w", bindBottom(levelname_label) + 10);
    levelname_txtbox->setSize("0.6 * &.w", 30);
    levelname_txtbox->setFont(font_register.at("regular"));

    tgui::Button::Ptr backbtn = tgui_theme->load("Button");
    backbtn->setPosition(0.3 * bindWidth(gui), bindBottom(levelname_txtbox) + 30);
    backbtn->setSize(bindWidth(gui) * 0.2, 40);
    backbtn->setText("Back");
    backbtn->setFont(font_register.at("bold"));
    backbtn->setTextSize(20);
    backbtn->connect("pressed", [this](){*this->feedback = 1;});

    tgui::Button::Ptr makebtn = tgui_theme->load("Button");
    makebtn->setPosition(0.5 * bindWidth(gui), bindBottom(levelname_txtbox) + 30);
    makebtn->setSize(bindWidth(gui) * 0.2, 40);
    makebtn->setText("Generate!");
    makebtn->setFont(font_register.at("bold"));
    makebtn->setTextSize(20);
    makebtn->connect("pressed", make_world, &gui, feedback);

    gui.add(levelname_label, "levelname_label");
    gui.add(levelname_txtbox, "levelname_txtbox");
    gui.add(backbtn, "backbtn");
    gui.add(makebtn, "makebtn");
}

void LevelCreate::show() {
    gui.setView(view);
    window->setView(view);
}

void LevelCreate::hide() {
    window->setView(window->getDefaultView());
}

void LevelCreate::render(sf::Time delta) {
    sf::Event ev;
    while (window->pollEvent(ev)) {
        gui.handleEvent(ev);
        if (ev.type == sf::Event::Closed) window->close();
    }

    view.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    view.setCenter(sf::Vector2f(window->getSize().x/2, window->getSize().y/2));
    gui.setView(view);
    window->setView(view);

    window->clear(sf::Color(0xedeff3ff));
    gui.draw();
    window->display();
}