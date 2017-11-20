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

    fin.open("../worlds/" + level_dirname + "/data/seed", ios::in | ios::binary);
    if (!fin.is_open()) {
        std::cout << "Failed to open seed file to read\n";
        window->close();
    }
    fin >> lvl_dat.seed;
    std::cout << "SEED\t" << lvl_dat.seed << std::endl;
    fin.close();

    fin.open("../worlds/" + level_dirname + "/data/blocks.dat", ios::in | ios::binary);
    if (!fin.is_open()) {
        std::cout << "Failed to open block file to read\n";
        window->close();
    }
    for (int i = 0, r = 0; r < LEVEL_HEIGHT; r++) {
        for (int c = 0; c < LEVEL_WIDTH; c++, i++) {
            uint8_t id = fin.get();
            if (id != 0) {
                lvl_dat.blocks[r][c] = id;
                blocks[i] = sf::RectangleShape(sf::Vector2f(2, 2));
                blocks[i].setPosition(sf::Vector2f(c * 2, r * 2));
            }  
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
    floor_lns[0].color = sf::Color::Red;
    floor_lns[1].position = sf::Vector2f(256 * 5, 0);
    floor_lns[1].color = sf::Color::Red;

    for (int i = 0; i < LEVEL_HEIGHT * LEVEL_WIDTH; i++) {
        window->draw(blocks[i]);
    }

    window->draw(floor_lns);
    window->display();
}