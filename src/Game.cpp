#include "scenes/Game.hpp"

Game::Game(sf::RenderWindow* window, int *feedback) : window(window), feedback(feedback) {
    view.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
}

void Game::show() {
    std::cout << "Showing game\n";
    std::cout << "LEVEL:\t" << level_filename << std::endl; 
    // load the world from a file
}

void Game::hide() {

}

void Game::render(sf::Time delta) {
    sf::Event ev;
    while (window->pollEvent(ev)) {
        if (ev.type == sf::Event::Closed) window->close();
    }

    window->clear();

    window->display();
}