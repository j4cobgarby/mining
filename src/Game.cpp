#include "scenes/Game.hpp"

float lerp(float from, float to, const float progress) {
    return from + (to - from) * progress;
}

Game::Game(sf::RenderWindow* window, int *feedback) : window(window), feedback(feedback) {
    view.setSize(sf::Vector2f(window->getSize().x*0.04, window->getSize().y*0.04));
    view.setCenter(sf::Vector2f(0, 0));

    player = Player(0, 0);
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

    fin.open("../worlds/" + level_dirname + "/data/spawn_position", ios::in | ios::binary);
    if (!fin.is_open()) {
        std::cout << "Failed to open spawn position file to read\n";
        window->close();
    }
    float spawnpos_x, spawnpos_y;
    fin >> spawnpos_x >> spawnpos_y;
    std::cout << "SPAWNPOS\t" << spawnpos_x << '\t' << spawnpos_y << std::endl;
    fin.close();

    player.rect.setPosition(sf::Vector2f(spawnpos_x, spawnpos_y));
    view.setCenter(sf::Vector2f(player.rect.getPosition().x, player.rect.getPosition().y + 40));

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
                blocks[i] = sf::RectangleShape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                blocks[i].setPosition(sf::Vector2f(c * BLOCK_SIZE, r * BLOCK_SIZE));
                blocks[i].setTexture(&tilemap_register.at(id));
                if (id == 0) blocks[i].setFillColor(sf::Color::Transparent);
            }
        }
    }
    fin.close();
    std::cout << string(10, '=') << "LOADING DONE" << string(10, '=') << std::endl;
}

void Game::hide() {
    // Write the possibly modified level to file
    ofstream fout;

    fout.open("../worlds/" + level_dirname + "/data/blocks.dat", ios::in | ios::binary);
    fout.clear();
    for (size_t y = 0; y < LEVEL_HEIGHT; y++) {
        for (size_t x = 0; x < LEVEL_WIDTH; x++) {
            fout.put(lvl_dat.blocks[y][x]);
        }
    }

    fout.close();
    fout.open("../worlds/" + level_dirname + "/data/spawn_position");
    fout.clear();
    fout << player.rect.getPosition().x << '\t' << player.rect.getPosition().y;
    fout.close();
    std::cout << "Bye bye!\n";
}

void Game::render(sf::Time delta) {
    sf::Event ev;
    while (window->pollEvent(ev)) {
        if (ev.type == sf::Event::Closed) {
            hide();
            window->close();
        }
        if (ev.type == sf::Event::MouseButtonPressed) {
            player.click(ev, window, &lvl_dat, blocks);
        }
    }

    player.move(lvl_dat, delta);

    window->setTitle(to_string(1.0/delta.asSeconds()));

    sf::Vector2f new_view_center = player.rect.getPosition();
    if (new_view_center.x < view.getSize().x/2) new_view_center.x = view.getSize().x/2;
    if (new_view_center.y < view.getSize().y/2) new_view_center.y = view.getSize().y/2;
    if (new_view_center.x > (LEVEL_WIDTH*BLOCK_SIZE)-view.getSize().x/2) new_view_center.x = (LEVEL_WIDTH*BLOCK_SIZE)-view.getSize().x/2;
    if (new_view_center.y > (LEVEL_HEIGHT*BLOCK_SIZE)-view.getSize().y/2) new_view_center.y = (LEVEL_HEIGHT*BLOCK_SIZE)-view.getSize().y/2;

    view.setCenter(sf::Vector2f(
        lerp(view.getCenter().x, new_view_center.x, 0.0007), 
        lerp(view.getCenter().y, new_view_center.y, 0.0007)
    ));

    view.setSize(sf::Vector2f(window->getSize().x*0.04, window->getSize().y*0.04));

    window->setView(view);
    window->clear(sf::Color(0x679effff));

    int tiles_x = view.getSize().x/BLOCK_SIZE;
    int tiles_y = view.getSize().y/BLOCK_SIZE;

    int start_x = (view.getCenter().x-view.getSize().x/2)/BLOCK_SIZE;
    start_x = max(0, min(start_x, LEVEL_WIDTH-tiles_x-2));

    int start_y = (view.getCenter().y-view.getSize().y/2)/BLOCK_SIZE;
    start_y = max(0, min(start_y, LEVEL_HEIGHT-tiles_y-2));

    for (int i = 0, r = start_y; r < start_y + tiles_y + 2; r++) {
        for (int c = start_x; c < start_x + tiles_x + 2; c++, i++) {
            window->draw(blocks[r*LEVEL_WIDTH+c]);
        }
    }

    player.draw(window);
    window->display();
}
