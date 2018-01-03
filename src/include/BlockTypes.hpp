#ifndef INCLUDE_BLOCKTYPES_HPP
#define INCLUDE_BLOCKTYPES_HPP

#include <vector>
#include <cstdint>

#include "assetregisters.hpp"
#include "Block.hpp"

////////////////////////////////////////////////////////////////////////////////
// macro for easy declaration of new blocks!
#define DEF_BLOCK(blockname, blockid) class blockname : public Block {\
public:\
    blockname () {setTexture(&tilemap_register.at(blockid));}\
    void interact();\
};
// void interact() should be defined in <blockname.cpp>
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Define blocks here, the id is the position in the spritesheet
DEF_BLOCK(Air_b,        0)

DEF_BLOCK(Stone_b,      1)
DEF_BLOCK(Cobbles_b,    2)
DEF_BLOCK(Dirt_b,       3)
DEF_BLOCK(Grass_b,      4)
DEF_BLOCK(Sand_b,       5)
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Add any new blocks here. The case should match their id
inline Block* blockptr_from_id(const uint8_t id) {
    switch (id) {
    case 1:return new Stone_b; break;
    case 2:return new Cobbles_b; break;
    case 3:return new Dirt_b; break;
    case 4:return new Grass_b; break;
    case 5:return new Sand_b; break;

    // ...

    case 0:
    default:
        return new Air_b; break;
    }
}
//
////////////////////////////////////////////////////////////////////////////////

#endif