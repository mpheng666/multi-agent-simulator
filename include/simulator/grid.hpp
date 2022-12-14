#ifndef MAS_GRID_HPP_
#define MAS_GRID_HPP_

#include "SFML/Graphics.hpp"
#include <vector>

namespace mas_grid {
class Grid : public sf::RectangleShape {
public:
    Grid(const double cost = 1.0) : cost_(cost) {}

    double getCost() const { return cost_; }

private:
    double cost_{0};
};
} // namespace mas_grid

#endif