#ifndef INCLUDE_ITEMTYPES_HPP
#define INCLUDE_ITEMTYPES_HPP

#include <vector>
#include <cstdint>
#include <iostream>

#include "assetregisters.hpp"
#include "Item.hpp"
#include "Block.hpp"

////////////////////////////////////////////////////////////////////////////////
// macro for easy decleration of new items!
// itemname: the class name
// itemid: the id of the item/block
#define DEF_ITEM(ITEMNAME, ITEM_ID)\
class ITEMNAME : public Item {\
public:\
    ITEMNAME () {sprite.setTexture(itemmap_register.at( ITEM_ID ));}\
    void leftclick();\
    void rightclick();\
    inline bool canBreakBlock(size_t block_id);\
    inline bool canHarvestBlock(size_t block_id);\
};
#define DEF_ITEMBLOCK(BLOCKNAME, BLOCK_ID)\
class BLOCKNAME : public ItemBlock {\
private:\
    bool is_block = true;\
public:\
    BLOCKNAME () {\
        sprite.setTexture(tilemap_register.at( BLOCK_ID ));\
    }\
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// declare items here
DEF_ITEM(Null_i,            0) // the item in an empty inv slot
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

DEF_ITEMBLOCK(Air_ib,       0) // shouldn't actually be used ever
DEF_ITEMBLOCK(Stone_ib,     1)
DEF_ITEMBLOCK(Cobbles_ib,   2)
DEF_ITEMBLOCK(Dirt_ib,      3)
DEF_ITEMBLOCK(Grass_ib,     4)
DEF_ITEMBLOCK(Sand_ib,       5)
////////////////////////////////////////////////////////////////////////////////

inline Item* itemptr_from_id(const uint8_t id, bool is_a_block) {
    if (is_a_block) {
        switch (id) {
        case 1: return new Stone_ib; break;
        case 2: return new Cobbles_ib; break;
        case 3: return new Dirt_ib; break;
        case 4: return new Grass_ib; break;
        case 5: return new Sand_ib; break;

        // ...

        case 0:
        default:
            return new Air_ib; break;
        }
    } else {
        switch (id) {
        case 1: return new IronPickaxe_i; break;
        case 2: return new IronShovel_i; break;
        case 3: return new IronAxe_i; break;
        case 4: return new IronSword_i; break;
        case 5: return new IronHammer_i; break;
        case 6: return new IronSickle_i; break;
        case 7: return new GreenBow_i; break;
        case 8: return new GreenArrow_i; break;
        case 9: return new MagiciansWand_i; break;
        case 10: return new BranchWand_i; break;
        case 11: return new BoneWand_i; break;
        case 12: return new PolishedWand_i; break;
        case 13: return new RedApple_i; break;
        case 14: return new GreenApple_i; break;
        case 15: return new Bread_i; break;
        case 16: return new CheeseTomatoLettuceSandwich_i; break;
        case 17: return new CheeseWheel_i; break;
        case 18: return new Tomato_i; break;
        case 19: return new Lettuce_i; break;
        case 20: return new EmptyBucket_i; break;
        case 21: return new MilkBucket_i; break;
        case 22: return new WaterBucket_i; break;
        case 23: return new Wheat_i; break;

        // ... add more here

        case 0:
        default:
            return new Null_i;
            break;
        }
    }
}

#endif