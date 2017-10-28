#include "include/CBInterface.hpp"

#include <iostream>

void TestCB::cb() {
    std::cout << "Callback!\n";
}

void ptrTestCB::cb() {
    text->setString("Clicked.");
}