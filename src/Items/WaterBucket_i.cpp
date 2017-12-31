#include "../include/ItemTypes.hpp"

void WaterBucket_i::leftclick() {
}

void WaterBucket_i::rightclick() {
}

inline bool WaterBucket_i::canBreakBlock(size_t block_id) {
    return true;
}

inline bool WaterBucket_i::canHarvestBlock(size_t block_id) {
    return true;
}
