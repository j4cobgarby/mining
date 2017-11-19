// Different data structures for different parts of the level data
#ifndef INCLUDE_LEVELDATA_HPP
#define INCLUDE_LEVELDATA_HPP

#define LEVEL_WIDTH 1000
#define LEVEL_HEIGHT 500

#include <cstdint>

class LevelData {
public:
    uint8_t blocks[LEVEL_HEIGHT][LEVEL_WIDTH];
    int seed;
};

#endif