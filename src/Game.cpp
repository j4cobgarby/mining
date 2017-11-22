#include "scenes/Game.hpp"

Game::Game(sf::RenderWindow* window, int *feedback) : window(window), feedback(feedback) {
    view.setSize(sf::Vector2f(window->getSize().x*0.04, window->getSize().y*0.04));
    view.setCenter(sf::Vector2f(0, 0));
}

void Game::show() {
    srand(time(NULL));
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
                blocks[i].setTexture(&tilemap_register.at(id));
                blocks[i].setOrigin(sf::Vector2f(1, 1));
                if (id == 1 || id == 3) blocks[i].setRotation((rand()%4) * 90);
                if (id == 0) blocks[i].setFillColor(sf::Color::Transparent);
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

    window->setTitle(to_string(1.0/delta.asSeconds()));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
        view.setCenter(sf::Vector2f(view.getCenter().x, view.getCenter().y - (sf::Keyboard::isKeyPressed(sf::Keyboard::X) ? 50 : 300) * delta.asSeconds()));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        view.setCenter(sf::Vector2f(view.getCenter().x, view.getCenter().y + (sf::Keyboard::isKeyPressed(sf::Keyboard::X) ? 50 : 300) * delta.asSeconds()));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        view.setCenter(sf::Vector2f(view.getCenter().x - (sf::Keyboard::isKeyPressed(sf::Keyboard::X) ? 50 : 300) * delta.asSeconds(), view.getCenter().y));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        view.setCenter(sf::Vector2f(view.getCenter().x + (sf::Keyboard::isKeyPressed(sf::Keyboard::X) ? 50 : 300) * delta.asSeconds(), view.getCenter().y));

    view.setSize(sf::Vector2f(window->getSize().x*0.04, window->getSize().y*0.04));

    window->setView(view);
    window->clear(sf::Color(0x77bdffff));
    sf::VertexArray floor_lns(sf::LinesStrip, 2);
    floor_lns[0].position = sf::Vector2f(0, 0);
    floor_lns[0].color = sf::Color::Red;
    floor_lns[1].position = sf::Vector2f(256 * 5, 0);
    floor_lns[1].color = sf::Color::Red;

    int tiles_x = view.getSize().x/BLOCK_SIZE;
    int tiles_y = view.getSize().y/BLOCK_SIZE;

    int start_x = (view.getCenter().x-view.getSize().x/2)/BLOCK_SIZE;
    start_x = max(0, min(start_x, LEVEL_WIDTH-tiles_x-1));

    int start_y = (view.getCenter().y-view.getSize().y/2)/BLOCK_SIZE;
    start_y = max(0, min(start_y, LEVEL_HEIGHT-tiles_y-1));

    for (int i = 0, r = start_y; r < start_y + tiles_y + 2; r++) {
        for (int c = start_x; c < start_x + tiles_x + 2; c++, i++) {
            window->draw(blocks[r*LEVEL_WIDTH+c]);
        }
    }

    window->draw(floor_lns);
    window->display();
}