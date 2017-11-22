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
    sf::RenderWindow *window;
    sf::View view;

    /** Master widget */
    tgui::Gui gui;

    int *feedback;
public:
    MainMenu(sf::RenderWindow*, int*);

    void show();
    void hide();
    void render(sf::Time);
};

#endif