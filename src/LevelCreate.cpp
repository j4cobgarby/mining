#include "scenes/LevelCreate.hpp"

namespace fs = experimental::filesystem;

/////////////////////////////////////////
// Level generation
/////////////////////////////////////////
// index = r * cols + c

void make_world(tgui::Gui *gui, int *feedback) {
    ////////////////////////////
    // Validate fields
    ////////////////////////////

    tgui::EditBox::Ptr eptr = gui->get<tgui::EditBox>("levelname_txtbox");
    std::string dirname = eptr->getText();

    int seed;
    try {
        tgui::EditBox::Ptr seed_ptr = gui->get<tgui::EditBox>("seed_txtbox");
        seed = std::stoi((std::string)seed_ptr->getText(), nullptr, 10);
    } catch (std::invalid_argument e) {
        std::cout << "Seed doesn't appear to be a valid number\n";
        return;
    } catch (std::out_of_range e) {
        std::cout << "Seed out of range\n";
        return;
    }
    std::cout << "SEED:\t" << seed << std::endl;
    
    if (dirname == "") {
        std::cout << "Empty level name\n";
        return;
    }

    if (!fs::create_directories("../worlds/" + dirname + "/players")) {
        std::cout << "Invalid world name\n";
        return;
    }
    if (!fs::create_directories("../worlds/" + dirname + "/data")) {
        std::cout << "Invalid world name\n";
        return;
    }

    ///////////////////////////
    // Generate the level
    ///////////////////////////
    std::cout << std::string(10, '=') << " GENERATING LEVEL " << std::string(10, '=') << std::endl;

    ofstream fout;
    fout.open("../worlds/" + dirname + "/data/seed", ios::out); // the seed
    if (!fout.is_open()) {
        std::cout << "Couldn't create seed file\n";
        fs::remove_all("../worlds/" + dirname); // remove level folder which didn't work
        return;
    }
    fout << to_string(seed);
    fout.close();
    fout.open("../worlds/" + dirname + "/data/dims"); // Dimensions of the world
    if (!fout.is_open()) {
        std::cout << "Couldn't open block data file\n";
        fs::remove_all("../worlds/" + dirname); // remove level folder which didn't work
        return;
    }
    fout << to_string(LEVEL_HEIGHT) << '\n' << to_string(LEVEL_WIDTH);
    fout.close();
    fout.open("../worlds/" + dirname + "/data/blocks.dat", ios::binary | ios::out);
    if (!fout.is_open()) {
        std::cout << "Couldn't open block data file\n";
        fs::remove_all("../worlds/" + dirname); // remove level folder which didn't work
        return;
    }
    
    uint8_t world[LEVEL_HEIGHT*LEVEL_WIDTH];

    for (int i = 0; i < LEVEL_HEIGHT * LEVEL_WIDTH; i++)
        world[i] = 0;

    FastNoise noise;
    noise.SetNoiseType(FastNoise::PerlinFractal);
    noise.SetFrequency(0.04);
    noise.SetInterp(FastNoise::Quintic);
    noise.SetFractalType(FastNoise::FBM);
    noise.SetFractalLacunarity(1.3);
    noise.SetSeed(seed);

    FastNoise secondary_noise;
    secondary_noise.SetNoiseType(FastNoise::SimplexFractal);
    noise.SetFrequency(0.02);
    noise.SetInterp(FastNoise::Quintic);
    noise.SetSeed(seed);

    // Basic ground
    for (int r = 0, i = 0; r < LEVEL_HEIGHT; r++) {
        for (int c = 0; c < LEVEL_WIDTH; c++, ++i) {
            float noise_tmp = floor(noise.GetNoise(c, 0) * 160 * secondary_noise.GetNoise(c, 0));
            if (noise_tmp + ((float)LEVEL_HEIGHT * 0.6) >= LEVEL_HEIGHT - r) {
                world[i] = 3;
            }
            if (noise_tmp + ((float)LEVEL_HEIGHT * 0.55) >= LEVEL_HEIGHT - r) {
                world[i] = 1;
            }
        }
    }

    for (int r = 0, i = 0; r < LEVEL_HEIGHT; r++) {
        for (int c = 0; c < LEVEL_WIDTH; c++, ++i) {
            if (i - LEVEL_WIDTH >= 0) {
                if (world[i] == 3 && world[i-LEVEL_WIDTH] == 0) world[i] = 4;
            }
        }
    }

    for (size_t i = 0; i < LEVEL_HEIGHT*LEVEL_WIDTH; i++) {
        fout.put(world[i]);
    }

    // now the level is stored in the file
    // every LEVEL_WIDTH characters is a different row, starting from the top-most
    fout.close();

    level_dirname = dirname;
    *feedback = 3;

    std::cout << std::string(10, '=') << " GENERATING DONE " << std::string(10, '=') << std::endl;
}

/////////////////////////////////////////
// GUI
/////////////////////////////////////////

LevelCreate::LevelCreate(sf::RenderWindow *window, int *feedback) : window(window), feedback(feedback) {
    view.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    view.setCenter(sf::Vector2f(window->getSize().x/2, window->getSize().y/2));

    gui.setWindow(*window);
    gui.setView(sf::View{});
    gui.setView(view);

    tgui::Label::Ptr levelname_label = tgui_theme->load("Label");
    levelname_label->setText("Level name");
    levelname_label->setPosition("0.2 * &.w", 50);
    levelname_label->setFont(font_register.at("regular"));

    tgui::EditBox::Ptr levelname_txtbox = tgui_theme->load("EditBox");
    levelname_txtbox->setPosition("0.2 * &.w", bindBottom(levelname_label) + 10);
    levelname_txtbox->setSize("0.6 * &.w", 30);
    levelname_txtbox->setFont(font_register.at("regular"));

    tgui::Label::Ptr seed_label = tgui_theme->load("Label");
    seed_label->setText("Seed");
    seed_label->setPosition("0.2 * &.w", bindBottom(levelname_txtbox) + 20);
    seed_label->setFont(font_register.at("regular"));

    tgui::EditBox::Ptr seed_txtbox = tgui_theme->load("EditBox");
    seed_txtbox->setPosition("0.2 * &.w", bindBottom(seed_label) + 10);
    seed_txtbox->setSize("0.6 * &.w", 30);
    seed_txtbox->setFont(font_register.at("regular"));

    tgui::Button::Ptr backbtn = tgui_theme->load("Button");
    backbtn->setPosition(0.3 * bindWidth(gui), bindBottom(seed_txtbox) + 30);
    backbtn->setSize(bindWidth(gui) * 0.2, 40);
    backbtn->setText("Back");
    backbtn->setFont(font_register.at("bold"));
    backbtn->setTextSize(20);
    backbtn->connect("pressed", [this](){*this->feedback = 1;});

    tgui::Button::Ptr makebtn = tgui_theme->load("Button");
    makebtn->setPosition(0.5 * bindWidth(gui), bindBottom(seed_txtbox) + 30);
    makebtn->setSize(bindWidth(gui) * 0.2, 40);
    makebtn->setText("Generate!");
    makebtn->setFont(font_register.at("bold"));
    makebtn->setTextSize(20);
    makebtn->connect("pressed", make_world, &gui, feedback);

    gui.add(levelname_label, "levelname_label");
    gui.add(levelname_txtbox, "levelname_txtbox");
    gui.add(seed_label, "seed_label");
    gui.add(seed_txtbox, "seed_txtbox");
    gui.add(backbtn, "backbtn");
    gui.add(makebtn, "makebtn");
}

void LevelCreate::show() {
    gui.setView(view);
    window->setView(view);
}

void LevelCreate::hide() {
    window->setView(window->getDefaultView());
}

void LevelCreate::render(sf::Time delta) {
    sf::Event ev;
    while (window->pollEvent(ev)) {
        gui.handleEvent(ev);
        if (ev.type == sf::Event::Closed) window->close();
    }

    view.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    view.setCenter(sf::Vector2f(window->getSize().x/2, window->getSize().y/2));
    gui.setView(view);
    window->setView(view);

    window->clear(sf::Color(0xedeff3ff));
    gui.draw();
    window->display();
}