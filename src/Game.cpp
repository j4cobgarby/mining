#include "scenes/Game.hpp"

Game::Game(sf::RenderWindow* window, int *feedback) : window(window), feedback(feedback) {
    view.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
}

void Game::show() {
    std::cout << "Showing game\n";
    std::cout << "LEVEL:\t" << level_dirname << std::endl; 
    // load the world from a file
    std::cout << string(10, '=') << "LOADING LEVEL" << string(10, '=') << std::endl;
    ifstream fin;
    fin.open("../worlds/" + level_dirname + "/data/blocks.dat", ios::in | ios::binary);
    if (!fin.is_open()) {
        std::cout << "Failed to open block file to read\n";
        window->close();
    }
    for (int i = 0, r = 0; r < LEVEL_HEIGHT; r++) {
        for (int c = 0; c < LEVEL_WIDTH; c++, i++) {
            lvl_dat.blocks[r][c] = fin.get();
        }
    }
    fin.close();
    std::cout << string(10, '=') << "LOADING DONE" << string(10, '=') << std::endl;
}

void Game::hide() {
    std::cout << "Bye bye!\n";
}

void Game::render(sf::Time delta) {
    sf::Event ev;
    while (window->pollEvent(ev)) {
        if (ev.type == sf::Event::Closed) {
            hide();
            window->close();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        view.setCenter(sf::Vector2f(view.getCenter().x, view.getCenter().y - 600 * delta.asSeconds()));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        view.setCenter(sf::Vector2f(view.getCenter().x, view.getCenter().y + 600 * delta.asSeconds()));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        view.setCenter(sf::Vector2f(view.getCenter().x - 600 * delta.asSeconds(), view.getCenter().y));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        view.setCenter(sf::Vector2f(view.getCenter().x + 600 * delta.asSeconds(), view.getCenter().y));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        view.zoom(1-delta.asSeconds());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        view.zoom(1+delta.asSeconds());

    window->setView(view);
    window->clear();
    sf::VertexArray floor_lns(sf::LinesStrip, 2);
    floor_lns[0].position = sf::Vector2f(0, 0);
    floor_lns[1].position = sf::Vector2f(256 * 5, 0);

    window->draw(floor_lns);
    window->display();
}