#ifndef MAS_CORE_OBJECT_HPP_
#define MAS_CORE_OBJECT_HPP_

#include "SFML/Graphics.hpp"
#include <vector>

namespace mas {
    class Object : public sf::RectangleShape {
    public:
        Object() {}
    };
} // namespace mas

#endif