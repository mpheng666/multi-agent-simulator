#ifndef MAS_MAP_HPP_
#define MAS_MAP_HPP_

#include "grid.hpp"
#include <vector>

namespace mas_map {
class Map {
public:
    Map(const std::vector<std::vector<mas_grid::Grid>> &grids) : map_(grids) {}

    std::vector<std::vector<mas_grid::Grid>> getMap() const { return map_; }

private:
    std::vector<std::vector<mas_grid::Grid>> map_;
};
} // namespace mas_map

#endif