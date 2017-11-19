// Different data structures for different parts of the level data
#ifndef INCLUDE_LEVELDATA_HPP
#define INCLUDE_LEVELDATA_HPP

#include <cstdint>

#define LEVEL_WIDTH 1000
#define LEVEL_HEIGHT 500

class LevelData {
    char blocks[LEVEL_WIDTH][LEVEL_HEIGHT];
    uint32_t seed;
};

#endif