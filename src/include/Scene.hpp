/**
 * An abstract class 
 */

#ifndef INCLUDE_SCENE_HPP
#define INCLUDE_SCENE_HPP

#include <SFML/Graphics.hpp>

class Scene {
private:
    int *feedback;
public:
    // Called every time this scene is made the current scene
    virtual void show() = 0;

    // Called every time this scene is made not the current scene anymore
    virtual void hide() = 0; 

    /** Called every frame. Should render the scene.
     * The return value is -1 for no scene change, or any
     * positive integer (including 0) to change the scene
     * to the scene of that index
     */
    virtual void render(sf::Time delta) = 0;
};

#endif