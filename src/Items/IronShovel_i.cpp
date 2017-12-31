#include "../include/ItemTypes.hpp"

void IronShovel_i::leftclick() {
}

void IronShovel_i::rightclick() {
}

inline bool IronShovel_i::canBreakBlock(size_t block_id) {
    return true;
}

inline bool IronShovel_i::canHarvestBlock(size_t block_id) {
    return true;
}
