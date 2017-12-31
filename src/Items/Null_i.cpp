#include "../include/ItemTypes.hpp"

void Null_i::leftclick() {
}

void Null_i::rightclick() {
}

inline bool Null_i::canBreakBlock(size_t block_id) {
    return false;
}

inline bool Null_i::canHarvestBlock(size_t block_id) {
    return false;
}
