#include "../include/ItemTypes.hpp"

void IronPickaxe_i::leftclick() {
    std::cout << "Iron pickaxe left click" << std::endl;
}

void IronPickaxe_i::rightclick() {
    std::cout << "Iron pickaxe right click" << std::endl;
}

inline bool IronPickaxe_i::canBreakBlock(size_t block_id) {
    return true;
}

inline bool IronPickaxe_i::canHarvestBlock(size_t block_id) {
    return true;
}