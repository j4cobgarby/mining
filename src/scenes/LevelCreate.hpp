#ifndef SCENES_LEVELCREATE_HPP
#define SCENES_LEVELCREATE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <TGUI/TGUI.hpp>
#include <experimental/filesystem>

#include "../include/Scene.hpp"
#include "../include/assetregisters.hpp"

TGUI_IMPORT_LAYOUT_BIND_FUNCTIONS

class LevelCreate : public Scene {
private:
    sf::RenderWindow *window;
    sf::View view;
    tgui::Gui gui;
    int *feedback;
public:
    LevelCreate(sf::RenderWindow *, int *feedback);

    void show();
    void hide();
    void render(sf::Time);
};

#endif