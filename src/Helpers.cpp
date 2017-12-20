#include "include/Helpers.hpp"

inline sf::Vector2f normalise(const sf::Vector2f& vec) {
    float len = sqrt((vec.x * vec.x) + (vec.y * vec.y));
    if (len == 0) return vec;
    return sf::Vector2f(vec.x / len, vec.y / len);
}