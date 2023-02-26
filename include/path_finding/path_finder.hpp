#ifndef MAS_PATH_FINDER_HPP_
#define MAS_PATH_FINDER_HPP_

#include "core/map.hpp"
#include "direction.hpp"
#include <array>
#include <iostream>
#include <memory>
#include <vector>
namespace mas {
    class MASPathFinder {
    public:
        MASPathFinder(Map& map)
            : map_(map){

              };

        virtual bool doSearch() = 0;

        std::vector<Grid> getNeighbours(const Grid& current_grid)
        {
            std::vector<Grid> neighbours{};
            for (const auto& direction : CardinalStep::steps) {
                Grid neighbour(current_grid.getIndex().x + direction.front(),
                               current_grid.getIndex().y + direction.back());
                if (neighbour.getIndex().x < map_.getColumnSize() &&
                    neighbour.getIndex().y < map_.getRowSize() &&
                    neighbour.getSpaceState() != SpaceState::OCCUPIED) {
                    std::cout << "neighbour: " << neighbour.getIndex().x << " "
                              << neighbour.getIndex().y << "\n";
                    neighbours.emplace_back(neighbour);
                }
            }
            return neighbours;
        }

        Grid getStart() const { return start_; }
        Grid getGoal() const { return goal_; }

        void setStart(const Grid& start) { start_ = start; }
        void setGoal(const Grid& goal) { goal_ = goal; }
        Map getMap() const { return map_; }

    private:
        Grid start_;
        Grid goal_;
        Map map_;

        PathFinderDirection direction_;
        std::vector<Grid> found_path_;
    };
} // namespace mas

#endif