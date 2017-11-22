#ifndef SCENES_LEVELSELECT_HPP
#define SCENES_LEVELSELECT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <TGUI/TGUI.hpp>
#include <experimental/filesystem>

#include "../include/Scene.hpp"
#include "../include/assetregisters.hpp"
#include "../include/SessionConfig.hpp"

TGUI_IMPORT_LAYOUT_BIND_FUNCTIONS

class LevelSelect : public Scene {
private:
    sf::RenderWindow *window;
    sf::View view;
    tgui::Gui gui;
    int *feedback;
public:
    LevelSelect(sf::RenderWindow*, int *feedback);

    void show();
    void hide();
    void render(sf::Time);
};

#endif