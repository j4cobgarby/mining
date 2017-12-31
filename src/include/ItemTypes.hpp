#ifndef INCLUDE_ITEMTYPES_HPP
#define INCLUDE_ITEMTYPES_HPP

#include <vector>
#include <cstdint>

#include "assetregisters.hpp"
#include "Item.hpp"

////////////////////////////////////////////////////////////////////////////////
// macro for easy decleration of new blocks!
// itemname: the class name
// itemid: the id of the item/block
#define DEF_ITEM(itemname, item_id) class itemname : public Item {\
public:\
    itemname () {setTexture(itemmap_register.at(item_id));}\
    void leftclick();\
    void rightclick();\
    inline bool canBreakBlock(size_t block_id);\
    inline bool canHarvestBlock(size_t block_id);\
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// declare items here
DEF_ITEM(Null_i,            0)
DEF_ITEM(IronPickaxe_i,     1)
DEF_ITEM(IronShovel_i,      2)
DEF_ITEM(IronAxe_i,         3)
DEF_ITEM(IronSword_i,       4)
DEF_ITEM(IronHammer_i,      5)
DEF_ITEM(IronSickle_i,      6)
DEF_ITEM(GreenBow_i,        7)
DEF_ITEM(GreenArrow_i,      8)
DEF_ITEM(MagiciansWand_i,   9)
DEF_ITEM(BranchWand_i,     10)
DEF_ITEM(BoneWand_i,       11)
DEF_ITEM(PolishedWand_i,   12)
DEF_ITEM(RedApple_i,       13)
DEF_ITEM(GreenApple_i,     14)
DEF_ITEM(Bread_i,          15)
DEF_ITEM(CheeseTomatoLettuceSandwich_i, 16)
DEF_ITEM(CheeseWheel_i,    17)
DEF_ITEM(Tomato_i,         18)
DEF_ITEM(Lettuce_i,        19)
DEF_ITEM(EmptyBucket_i,    20)
DEF_ITEM(MilkBucket_i,     21)
DEF_ITEM(WaterBucket_i,    22)
DEF_ITEM(Wheat_i,          23)
////////////////////////////////////////////////////////////////////////////////

inline Item* itemptr_from_id(const uint8_t id) {
    switch (id) {
    case 1: return new IronPickaxe_i;
    case 2: return new IronShovel_i;
    case 3: return new IronAxe_i;
    case 4: return new IronSword_i;
    case 5: return new IronHammer_i;
    case 6: return new IronSickle_i;
    case 7: return new GreenBow_i;
    case 8: return new GreenArrow_i;
    case 9: return new MagiciansWand_i;
    case 10: return new BranchWand_i;
    case 11: return new BoneWand_i;
    case 12: return new PolishedWand_i;
    case 13: return new RedApple_i;
    case 14: return new GreenApple_i;
    case 15: return new Bread_i;
    case 16: return new CheeseTomatoLettuceSandwich_i;
    case 17: return new CheeseWheel_i;
    case 18: return new Tomato_i;
    case 19: return new Lettuce_i;
    case 20: return new EmptyBucket_i;
    case 21: return new MilkBucket_i;
    case 22: return new WaterBucket_i;
    case 23: return new Wheat_i;

    // ... add more here

    case 0:
    default:
        return new Null_i;
    }
}

#endif