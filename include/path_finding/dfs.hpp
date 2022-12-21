#ifndef MAS_PATH_FINDING_DFS_HPP_
#define MAS_PATH_FINDING_DFS_HPP_

#include "simulator/map.hpp"
#include <stack>

namespace mas_dfs {
    class MASDFS {
    public:
        MASDFS() {}
        ~MASDFS() {}

        std::vector<mas_grid::Grid>
        start(mas_map::Map& map, int start_x, int start_y, int end_x, int end_y, int grid_w, int grid_h)
        {
            std::cout << "START DFS!\n";
            bool found_path{false};
            mas_grid::Grid start_grid;
            mas_grid::Grid end_grid;
            start_grid.setSize(sf::Vector2f(grid_w, grid_h));
            end_grid.setSize(sf::Vector2f(grid_w, grid_h));
            start_grid.setPosition(start_x, start_y);
            end_grid.setPosition(end_x, end_y);
            startDFS(map, start_grid, end_grid, found_path);
            return path_result_;
        }

        bool startDFS(mas_map::Map& map,
                      mas_grid::Grid start,
                      mas_grid::Grid end,
                      bool& found_path)
        {
            if (start.getPosition().x >= map.getColumnSize() ||
                start.getPosition().x < 0 || start.getPosition().y >= map.getRowSize() ||
                start.getPosition().y < 0 || end.getPosition().x >= map.getColumnSize() ||
                end.getPosition().x < 0 || end.getPosition().y >= map.getRowSize() ||
                end.getPosition().y < 0) {
                // std::cout << "Start or end out of bound" << '\n';
                return false;
            }

            if (map.grid_map.at(start.getPosition().x)
                .at(start.getPosition().y)
                .getFillColor() == sf::Color::Blue) {
            }

            if (!found_path) {
                if (map.grid_map.at(start.getPosition().x)
                    .at(start.getPosition().y)
                    .getFillColor() == sf::Color::White) {
                    // std::cout << "push: " << start.getPosition().x << " " <<
                    // start.getPosition().y << '\n';
                    path_stack_.push(
                    map.grid_map.at(start.getPosition().x).at(start.getPosition().y));
                    // std::cout << "Valid cell: " << start.getPosition().x << " " <<
                    // start.getPosition().y <<
                    // "\n";
                    map.grid_map.at(start.getPosition().x)
                    .at(start.getPosition().y)
                    .setFillColor(sf::Color::Blue);
                    if (start.getPosition().x == end.getPosition().x &&
                        start.getPosition().y == end.getPosition().y) {
                        // std::cout << "Found path at: " << start.getPosition().x << " "
                        // << start.getPosition().y
                        //           << "\n";

                        map.grid_map.at(start.getPosition().x)
                        .at(start.getPosition().y)
                        .setFillColor(sf::Color::Blue);
                        while (path_stack_.size()) {
                            path_result_.push_back(path_stack_.top());
                            path_stack_.pop();
                        }
                        found_path = true;
                        return true;
                    }
                }
            }
            start.setPosition(start.getPosition().x, start.getPosition().y + 1);
            startDFS(map, start.getPosition().y, end, found_path);
            start.setPosition(start.getPosition().x, start.getPosition().y - 1);

            start.setPosition(start.getPosition().x + 1, start.getPosition().y);
            startDFS(map, start, end, found_path);
            start.setPosition(start.getPosition().x - 1, start.getPosition().y);

            start.setPosition(start.getPosition().x, start.getPosition().y - 1);
            startDFS(map, start.getPosition().y, end, found_path);
            start.setPosition(start.getPosition().x, start.getPosition().y + 1);

            start.setPosition(start.getPosition().x - 1, start.getPosition().y);
            startDFS(map, start, end, found_path);
            start.setPosition(start.getPosition().x + 1, start.getPosition().y);

            // std::cout << "pop: " << start.x_ << " " << start.getPosition().y << '\n';
            path_stack_.pop();
            return true;
        }

        std::vector<mas_grid::Grid> path_result_;
        std::stack<mas_grid::Grid> path_stack_;

    private:
    };
} // namespace mas_dfs

#endif