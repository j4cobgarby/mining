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

/**
 * Load custom gui theme
 */
tgui::Theme::Ptr tgui_theme = tgui::Theme::create(ASSETS_ROOT + "gui/Custom.txt");

/**
 * Initialise window to slightly larger than desired, so that I can resize
 * it and avoid a glitch with the GUI
 */
sf::RenderWindow window(sf::VideoMode(1001, 1001), "miner");

/**
 * Default scene is the main menu
 */
Scene *active_scene = 0;

/**
 * -1 means no change of scene. scenes will change this to swap the scene
 */
int scene_feedback = -1;

/**
 * Unset value of the levelname. Changed by the menu, by the user
 */
std::string level_dirname = "";

/**
 * Initialise the scenes
 */
std::vector<Scene*> scenes {
    new MainMenu(&window, &scene_feedback),
    new LevelSelect(&window, &scene_feedback),
    new LevelCreate(&window, &scene_feedback),
    new Game(&window, &scene_feedback),
};

void swapscene(int);

int main() {
    /** Set starting scene to main menu */
    swapscene(0);
    sf::Clock deltaclock;
    while (window.isOpen()) {
        /** Time since last frame */
        sf::Time delta = deltaclock.restart();

        /** Call scene to render itself, handle events, etc. */
        active_scene->render(delta);

        /** If the scene wants to change the scene then do that */
        if (scene_feedback >= 0) swapscene(scene_feedback);
        scene_feedback = -1;
    }
}

/**
 * Handles swapping the scene, calling appropriate methods
 */
void swapscene(int scene_index) {
    if (scene_index >= scenes.size()) return; // out of range

    /** This is NOT checking if the scene INDEX is 0, it's checking
     * if the active scene has actually been set yet!
     */
    if (active_scene != 0) active_scene->hide();
    active_scene = scenes.at(scene_index);
    active_scene->show();
}
