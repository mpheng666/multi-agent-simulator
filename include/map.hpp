#ifndef MAS_MAP_HPP_
#define MAS_MAP_HPP_

#include "grid.hpp"
#include <vector>

namespace mas_map {
    class Map {
    public:
        Map(const std::vector<std::vector<mas_grid::Grid>>& grids)
            : map_(grids)
        {
        }

        std::vector<std::vector<mas_grid::Grid>> getMap() const { return map_; }

        std::size_t getColumnSize() { return map_.size(); }
        std::size_t getRowSize() { return map_.front().size(); }

    private:
        std::vector<std::vector<mas_grid::Grid>> map_;
    };
} // namespace mas_map

#endif