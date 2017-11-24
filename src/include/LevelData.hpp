// Different data structures for different parts of the level data
#ifndef INCLUDE_LEVELDATA_HPP
#define INCLUDE_LEVELDATA_HPP

#define LEVEL_WIDTH 1024
#define LEVEL_HEIGHT 256

#define BLOCK_SIZE 2

#include <cstdint>

class LevelData {
public:
    int seed;
    uint8_t blocks[LEVEL_HEIGHT][LEVEL_WIDTH];
};

#endif