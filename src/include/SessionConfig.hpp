/**
 * Session-defined variables, probably by the user.
 */

#ifndef INCLUDE_SESSIONCONFIG_HPP
#define INCLUDE_SESSIONCONFIG_HPP

#include <string>

struct config {
    int window_width;
    int window_height;
};

extern std::string level_filename;

#endif