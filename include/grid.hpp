#ifndef MRS_GRID_HPP_
#define MRS_GRID_HPP_

#include <vector>

namespace mrs_grid {
class Grid {
public:
    Grid(const double cost = 1.0) : cost_(cost) {}

    // double getWidth() const { return width_; }
    // double getHeight() const { return height_; }
    double getCost() const { return cost_; }

private:
    // double width_{0.0};
    // double height_{0.0};
    double cost_{0};
};
} // namespace mrs_grid

#endif