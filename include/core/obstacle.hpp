#ifndef MAS_CORE_OBSTACLE_HPP_
#define MAS_CORE_OBSTACLE_HPP_

#include "SFML/Graphics.hpp"
#include <vector>

namespace mas {
    class Obstacle : public sf::RectangleShape {
    public:
        Obstacle() {}
    };
} // namespace mas

#endif