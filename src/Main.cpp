#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <TGUI/TGUI.hpp>

#include "include/assetregisters.hpp"
#include "include/Scene.hpp"
#include "scenes/MainMenu.hpp"
#include "scenes/LevelSelect.hpp"
#include "scenes/LevelCreate.hpp"
#include "include/SessionConfig.hpp"

#define ASSETS_ROOT std::string("../assets/")

using std::cout;
using std::cin;

map<std::string, sf::Font> font_register {
    {"regular", makeFont(ASSETS_ROOT + "gravity/Gravity-Regular.otf")},
    {"bold", makeFont(ASSETS_ROOT + "gravity/Gravity-Bold.otf")},
    {"book", makeFont(ASSETS_ROOT + "gravity/Gravity-Book.otf")},
    {"light", makeFont(ASSETS_ROOT + "gravity/Gravity-Light.otf")},
    {"ultralight", makeFont(ASSETS_ROOT + "gravity/Gravity-UltraLight.otf")},
};

map<std::string, sf::Texture> texture_register {
    {"titlebig", makeTexture(ASSETS_ROOT + "images/titlebig.png")},
};

tgui::Theme::Ptr tgui_theme = tgui::Theme::create(ASSETS_ROOT + "gui/Custom.txt");

sf::RenderWindow window(sf::VideoMode(1001, 1001), "miner");
Scene *active_scene = 0;
int scene_feedback = -1;

std::string level_filename = "";

std::vector<Scene*> scenes {
    new MainMenu(&window, &scene_feedback),
    new LevelSelect(&window, &scene_feedback),
    new LevelCreate(&window, &scene_feedback),
    new Game(&window, &scene_feedback),
};

void swapscene(int);

int main() {
    cout << &scene_feedback << endl;
    swapscene(0);
    sf::Clock deltaclock;
    while (window.isOpen()) {
        sf::Time delta = deltaclock.restart();

        active_scene->render(delta);
        if (scene_feedback >= 0) swapscene(scene_feedback);
        scene_feedback = -1;
    }
}

void swapscene(int scene_index) {
    if (scene_index >= scenes.size()) return; // out of range

    if (active_scene != 0) active_scene->hide();
    active_scene = scenes.at(scene_index);
    active_scene->show();
}
