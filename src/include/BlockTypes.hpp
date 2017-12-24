#ifndef INCLUDE_BLOCKTYPES_HPP
#define INCLUDE_BLOCKTYPES_HPP

#include <vector>

#include "assetregisters.hpp"
#include "Block.hpp"

//////////////////////////////////////////////////////////////////////////////
// macro for easy declaration of new blocks!
#define DEF_BLOCK(blockname, blockid) class blockname : public Block {\
public:\
    blockname () {setTexture(&tilemap_register.at(blockid));}\
    void interact();\
};
// void interact() should be defined in <blockname.cpp>
//////////////////////////////////////////////////////////////////////////////

DEF_BLOCK(Air_b,        0)

DEF_BLOCK(Stone_b,      1)
DEF_BLOCK(Cobbles_b,    2)
DEF_BLOCK(Dirt_b,       3)
DEF_BLOCK(Grass_b,      4)
DEF_BLOCK(Sand_b,       5)

#endif