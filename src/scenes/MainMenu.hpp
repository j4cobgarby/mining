#ifndef SCENES_MAINMENU_HPP
#define SCENES_MAINMENU_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../include/Button.hpp"
#include "../include/Scene.hpp"
#include "../include/assetregisters.hpp"

class MainMenu : public Scene {
private:
    sf::RenderWindow *window;
    sf::Text title, text;
    ptrTestCB testcb;
    Button testBtn;
public:
    MainMenu(sf::RenderWindow*);

    void show();
    void hide();
    int render(sf::Time);
};

#endif