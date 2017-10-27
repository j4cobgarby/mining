#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <experimental/filesystem>
#include <string>

#include "include/assetregisters.hpp"
#include "include/Scene.hpp"
#include "include/MainMenu.hpp"

#define ASSETS_ROOT std::string("../assets/")

using std::cout;
using std::cin;
namespace fs = std::experimental::filesystem;

map<std::string, sf::Font> font_register {
    {"regular", makeFont(ASSETS_ROOT + "gravity/Gravity-Regular.otf")},
    {"bold", makeFont(ASSETS_ROOT + "gravity/Gravity-Bold.otf")},
    {"book", makeFont(ASSETS_ROOT + "gravity/Gravity-Book.otf")},
    {"light", makeFont(ASSETS_ROOT + "gravity/Gravity-Light.otf")},
    {"ultralight", makeFont(ASSETS_ROOT + "gravity/Gravity-UltraLight.otf")},
};

sf::RenderWindow window(sf::VideoMode(1000, 1000), "mining");
Scene *active_scene = 0;

std::vector<Scene*> scenes {
    new MainMenu(&window),
};

void swapscene(unsigned short int);

int main() {
    swapscene(0);
    sf::Clock deltaclock;
    while (window.isOpen()) {
        sf::Time delta = deltaclock.restart();

        int feedback = active_scene->render(delta);
        if (feedback >= 0) swapscene(feedback);
    }
}

void swapscene(unsigned short int scene_index) {
    if (scene_index >= scenes.size()) return; // out of range

    if (active_scene != 0) active_scene->hide();
    active_scene = scenes.at(scene_index);
    active_scene->show();
}