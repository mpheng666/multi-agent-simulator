#ifndef MAS_SIM_POINT_2D_HPP_
#define MAS_SIM_POINT_2D_HPP_

#include <SFML/System/Vector2.hpp>

namespace mas {
    template <typename T>
    class Point2D : public sf::Vector2<T> {
    public:
        Point2D()
            : sf::Vector2u()
        {
        }

        Point2D(T x, T y)
            : sf::Vector2<T>(x, y)
        {
        }

        virtual ~Point2D() = default;
    };
} // namespace mas_sim

#endif