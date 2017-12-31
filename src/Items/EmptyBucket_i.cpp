#include "../include/ItemTypes.hpp"

void EmptyBucket_i::leftclick() {
}

void EmptyBucket_i::rightclick() {
}

inline bool EmptyBucket_i::canBreakBlock(size_t block_id) {
    return true;
}

inline bool EmptyBucket_i::canHarvestBlock(size_t block_id) {
    return true;
}
