#ifndef MAS_MAP_HPP_
#define MAS_MAP_HPP_

#include "simulator/grid.hpp"
#include <vector>
#include <iostream>

namespace mas_map {
    class Map {
    public:
        Map(const std::vector<std::vector<mas_grid::Grid>>& grids)
            : grid_map(grids)
        {
        }

        Map(const int col, const int row)
            : col_(col)
            , row_(row)
        {
            try
            {
                grid_map.resize(col_, std::vector<mas_grid::Grid>(row_));
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        std::size_t getColumnSize() const { return grid_map.size(); }
        std::size_t getRowSize() const { return grid_map.front().size(); }
        std::vector<std::vector<mas_grid::Grid>> grid_map;

    private:
        int col_{0};
        int row_{0};
    };
} // namespace mas_map

#endif