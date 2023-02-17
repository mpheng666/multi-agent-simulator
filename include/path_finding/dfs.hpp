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
        DepthFirstSearch(const Map& map)
            : MASPathFinder(map)
        {
        }

        bool doSearch() override
        {
            Grid currrent_grid = getStart();
            currrent_grid.visited_state = VisitedState::VISITED;
            path_.push(currrent_grid);
            while (path_.size()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                auto next_grid = path_.top();
                next_grid.visited_state = VisitedState::VISITED;
                std::cout << "path_grid: " << next_grid.index_.front() << " "
                          << next_grid.index_.back() << "\n";
                path_.pop();
                if (next_grid.index_ == getGoal().index_) {
                    return true;
                }
                auto neighbours = getNeighbours(next_grid);
                for (auto& neighbour : neighbours) {
                    if (neighbour.visited_state == VisitedState::NOT_VISITED) {
                        neighbour.visited_state = VisitedState::VISITED;
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
            grids.at(current_grid.index_.front())
            .at(current_grid.index_.back())
            .visited_state = VisitedState::VISITED;
            path_.push(current_grid);
            while (path_.size()) {
                // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                if (path_.top().index_ == getGoal().index_) {
                    std::cout << "Found goal! \n";
                    return true;
                }
                Grid next_grid = path_.top();
                path_.pop();
                std::cout << "next_grid >> : " << next_grid.index_.front() << " "
                          << next_grid.index_.back() << "\n";

                grids.at(next_grid.index_.front())
                .at(next_grid.index_.back())
                .visited_state = VisitedState::VISITED;

                auto neighbours = getNeighbours(next_grid);

                for (auto& neighbour : neighbours) {
                    if (grids.at(neighbour.index_.front())
                        .at(neighbour.index_.back())
                        .visited_state == VisitedState::NOT_VISITED) {
                        grids.at(neighbour.index_.front())
                        .at(neighbour.index_.back())
                        .visited_state = VisitedState::VISITED;
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
    };
} // namespace mas

#endif