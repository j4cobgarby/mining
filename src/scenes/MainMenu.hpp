#ifndef SCENES_MAINMENU_HPP
#define SCENES_MAINMENU_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <TGUI/TGUI.hpp>
#include <string>

#include "../include/Scene.hpp"
#include "../include/assetregisters.hpp"

/**
 * Import all the TGUI bind functions
 */
TGUI_IMPORT_LAYOUT_BIND_FUNCTIONS

class MainMenu : public Scene {
private:
    int l = 0;
    sf::RenderWindow *window;
    sf::View view;

    /** Master widget */
    tgui::Gui gui;
public:
    MainMenu(sf::RenderWindow*);

    void show();
    void hide();
    int render(sf::Time);
};

#endif