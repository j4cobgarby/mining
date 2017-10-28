#ifndef INCLUDE_CBINTERFACE_HPP
#define INCLUDE_CBINTERFACE_HPP

#include <SFML/Graphics.hpp>

class CBInterface {
public:
    virtual void cb() = 0;
};

/**
 * Also define the callbacks here
 */
class TestCB : public CBInterface {
public:
    void cb();
};

class ptrTestCB : public CBInterface {
private:
    sf::Text *text;
public:
    ptrTestCB() {};
    ptrTestCB(sf::Text *text) : text(text) {};
    void cb();
};

#endif