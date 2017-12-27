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

using std::cout;
using std::cin;

std::map<std::string, sf::Font> font_register {
    {"regular", makeFont(ASSETS_ROOT + "gravity/Gravity-Regular.otf")},
    {"bold", makeFont(ASSETS_ROOT + "gravity/Gravity-Bold.otf")},
    {"book", makeFont(ASSETS_ROOT + "gravity/Gravity-Book.otf")},
    {"light", makeFont(ASSETS_ROOT + "gravity/Gravity-Light.otf")},
    {"ultralight", makeFont(ASSETS_ROOT + "gravity/Gravity-UltraLight.otf")},
};

std::map<std::string, sf::Texture> texture_register {
    {"titlebig", makeTexture(ASSETS_ROOT + "images/titlebig.png")},
    {"spritesheet", makeTexture(ASSETS_ROOT + "images/sprites2.png")},
};

std::map<int, sf::Texture> tilemap_register = init_tilemap_register(ASSETS_ROOT + "images/tilemap8.png",
    16, 16, // amount of tiles
    8, 8); // size of each tile (x, y)

std::map<int, sf::Texture> itemmap_register = init_tilemap_register(ASSETS_ROOT + "images/items8.png",
    16, 16, 8, 8
);

std::map<std::string, Animation> animation_register {
    {"player_default_idle_rt", makeAnimation(texture_register.at("spritesheet"))},
    {"player_default_idle_lt", makeAnimation(texture_register.at("spritesheet"))},
    {"player_default_wrt",  makeAnimation(texture_register.at("spritesheet"))},
    {"player_default_wlt",  makeAnimation(texture_register.at("spritesheet"))},
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

void swapscene(size_t);

int main() {
    window.setVerticalSyncEnabled(false);

    /**
     * Initialise animations
     */
    animation_register["player_default_idle_rt"].addFrame(sf::IntRect( 8, 80, 8, 16));
    animation_register["player_default_idle_rt"].addFrame(sf::IntRect(16, 80, 8, 16));
    
    animation_register["player_default_idle_lt"].addFrame(sf::IntRect(24, 80, 8, 16));
    animation_register["player_default_idle_lt"].addFrame(sf::IntRect(32, 80, 8, 16));

    animation_register["player_default_wrt"].addFrame(sf::IntRect( 8, 48, 8, 16));
    animation_register["player_default_wrt"].addFrame(sf::IntRect(16, 48, 8, 16));
    animation_register["player_default_wrt"].addFrame(sf::IntRect(24, 48, 8, 16));
    animation_register["player_default_wrt"].addFrame(sf::IntRect(32, 48, 8, 16));
    animation_register["player_default_wrt"].addFrame(sf::IntRect(40, 48, 8, 16));
    animation_register["player_default_wrt"].addFrame(sf::IntRect(48, 48, 8, 16));
    animation_register["player_default_wrt"].addFrame(sf::IntRect(56, 48, 8, 16));
    animation_register["player_default_wrt"].addFrame(sf::IntRect(64, 48, 8, 16));
    animation_register["player_default_wrt"].addFrame(sf::IntRect(72, 48, 8, 16));

    animation_register["player_default_wlt"].addFrame(sf::IntRect( 8, 64, 8, 16));
    animation_register["player_default_wlt"].addFrame(sf::IntRect(16, 64, 8, 16));
    animation_register["player_default_wlt"].addFrame(sf::IntRect(24, 64, 8, 16));
    animation_register["player_default_wlt"].addFrame(sf::IntRect(32, 64, 8, 16));
    animation_register["player_default_wlt"].addFrame(sf::IntRect(40, 64, 8, 16));
    animation_register["player_default_wlt"].addFrame(sf::IntRect(48, 64, 8, 16));
    animation_register["player_default_wlt"].addFrame(sf::IntRect(56, 64, 8, 16));
    animation_register["player_default_wlt"].addFrame(sf::IntRect(64, 64, 8, 16));
    animation_register["player_default_wlt"].addFrame(sf::IntRect(72, 64, 8, 16));
    
    

    /** 
     * Set starting scene to main menu 
     */
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
void swapscene(size_t scene_index) {
    if (scene_index >= scenes.size()) return; // out of range

    /** This is NOT checking if the scene INDEX is 0, it's checking
     * if the active scene has actually been set yet!
     */
    if (active_scene != 0) active_scene->hide();
    active_scene = scenes.at(scene_index);
    active_scene->show();
}
