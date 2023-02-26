#ifndef MAS_PATH_FINDING_DFS_HPP_
#define MAS_PATH_FINDING_DFS_HPP_

#include "path_finder.hpp"
#include <chrono>
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
            Grid currrent_grid = getStart();
            currrent_grid.setVisitedState(VisitedState::VISITED);
            path_.push(currrent_grid);
            while (path_.size()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                auto next_grid = path_.top();
                next_grid.setVisitedState(VisitedState::VISITED);
                std::cout << "path_grid: " << next_grid.getIndex().x << " "
                          << next_grid.getIndex().y << "\n";
                path_.pop();
                if (next_grid.getIndex() == getGoal().getIndex()) {
                    return true;
                }
                auto neighbours = getNeighbours(next_grid);
                for (auto& neighbour : neighbours) {
                    if (neighbour.getVisitedState() == VisitedState::NOT_VISITED) {
                        neighbour.setVisitedState(VisitedState::VISITED);
                        path_.push(neighbour);
                    }
                }
            }

            return false;
        }

        bool doMapSearch()
        {
            auto grids = getMap().getGrids();
            Grid current_grid = getStart();
            grids.at(current_grid.getIndex().x)
            .at(current_grid.getIndex().y)
            .setVisitedState(VisitedState::VISITED);
            path_.push(current_grid);
            while (path_.size()) {
                // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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

                auto neighbours = getNeighbours(next_grid);

                for (auto& neighbour : neighbours) {
                    if (grids.at(neighbour.getIndex().x)
                        .at(neighbour.getIndex().y)
                        .getVisitedState() == VisitedState::NOT_VISITED) {
                        grids.at(neighbour.getIndex().x)
                        .at(neighbour.getIndex().y)
                        .setVisitedState(VisitedState::VISITED);
                        path_.push(neighbour);
                    }
                }
            }
            return false;
        }

        std::vector<Grid> getPath()
        {
            std::vector<Grid> ret_path;
            while (path_.size()) {
                ret_path.push_back(path_.top());
                path_.pop();
            }
            return ret_path;
        }

    private:
        std::stack<Grid> path_;

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