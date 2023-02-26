#ifndef MAS_PATH_FINDING_DFS_HPP_
#define MAS_PATH_FINDING_DFS_HPP_

#include "path_finder.hpp"
#include <chrono>
#include <list>
#include <stack>
#include <thread>
#include <unordered_set>
namespace mas {
    class DepthFirstSearch : public MASPathFinder {
    public:
        DepthFirstSearch(Map& map)
            : MASPathFinder(map)
        {
        }

        bool doSearch() override
        {
            auto grids = getMap().getGrids();
            Grid current_grid = getStart();

            grids.at(current_grid.getIndex().x)
            .at(current_grid.getIndex().y)
            .setVisitedState(VisitedState::VISITED);

            path_.push(current_grid);
            while (path_.size()) {
                if (path_.top().getIndex() == getGoal().getIndex()) {
                    std::cout << "Found goal! \n";
                    return true;
                }
                Grid next_grid = path_.top();
                path_.pop();
                std::cout << "next_grid >> : " << next_grid.getIndex().x << " "
                          << next_grid.getIndex().y << "\n";

                grids.at(next_grid.getIndex().x)
                .at(next_grid.getIndex().y)
                .setVisitedState(VisitedState::VISITED);
                explored_path_.push_back(next_grid.getIndex());

                grids.at(next_grid.getIndex().x)
                .at(next_grid.getIndex().y)
                .setSpaceState(SpaceState::EMPTY);

                auto neighbours = getNeighbours(next_grid);

                for (auto& neighbour : neighbours) {
                    if (grids.at(neighbour.getIndex().x)
                        .at(neighbour.getIndex().y)
                        .getVisitedState() == VisitedState::NOT_VISITED &&
                        grids.at(neighbour.getIndex().x)
                        .at(neighbour.getIndex().y)
                        .getSpaceState() != SpaceState::OCCUPIED) {
                        path_.push(neighbour);
                    }
                }
            }
            return false;
        }

        std::vector<Grid> getPath()
        {
            std::vector<Grid> ret_path(explored_path_.begin(), explored_path_.end());

            return ret_path;
        }

    private:
        std::stack<Grid> path_;
        std::list<Grid> explored_path_;

        void printPathStack()
        {
            std::stack<Grid> printStack = path_;
            std::cout << "Current stack: ";
            while (printStack.size()) {
                // std::cout << printStack.top().getIndex() << " ";
                printStack.pop();
            }
            std::cout << "\n";
        }
    };
} // namespace mas

#endif