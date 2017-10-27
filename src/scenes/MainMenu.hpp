#ifndef INCLUDE_MAINMENU_HPP
#define INCLUDE_MAINMENU_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../include/Scene.hpp"
#include "../include/assetregisters.hpp"

class MainMenu : public Scene {
private:
    sf::RenderWindow *window;
public:
    MainMenu(sf::RenderWindow*);

    void show();
    void hide();
    int render(sf::Time);
};

#endif