#include "path_finder/rrt.hpp"

#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <unordered_map>

namespace mas
{
    RRTPathFinder::RRTPathFinder(RRTConfig config)
        : config_ {config}
    {
    }

    std::vector<sf::Vector2i> RRTPathFinder::findPath(const Map& map,
                                                      const sf::Vector2i& start,
                                                      const sf::Vector2i& goal)
    {
        std::cout << "Finding path using RRT"
                  << "\n";
        std::cout << "Start: " << start.x << " " << start.y << "\n";
        std::cout << "Goal: " << goal.x << " " << goal.y << "\n";
        std::cout << "Max Iter: " << config_.max_iter << "\n";
        std::cout << "Step Size: " << config_.step_size << "\n";
        std::cout << "Goal Bias: " << config_.goal_bias << "\n";
        std::cout << "Goal Radius: " << config_.goal_radius << "\n";
        std::cout << "RRT Type: " << static_cast<int>(config_.type) << "\n";
        // RRT Pseudo CodeQgoal //region that identifies success
        // Counter = 0 //keeps track of iterations
        // lim = n //number of iterations algorithm should run for
        // G(V,E) //Graph containing edges and vertices, initialized as empty
        // While counter < lim:
        //     Xnew  = RandomPosition()
        //     if IsInObstacle(Xnew) == True:
        //         continue
        //     Xnearest = Nearest(G(V,E),Xnew) //find nearest vertex
        //     Link = Chain(Xnew,Xnearest)
        //     G.append(Link)
        //     if Xnew in Qgoal:
        //         Return G
        // Return G
        explored_nodes_.clear();
        std::vector<sf::Vector2i> path;

        auto row = map.getMapConfig().row_num;
        auto col = map.getMapConfig().col_num;

        std::unordered_map<sf::Vector2i, sf::Vector2i, vector2i_hash> parents;
        parents[start] = sf::Vector2i(-1, -1);
        explored_nodes_.push_back(start);

        for (int i = 0; i < config_.max_iter; ++i)
        {
            sf::Vector2i random_node   = getRandomPosition(map);
            sf::Vector2i nearest_node  = getNearestNode(random_node, explored_nodes_);
            auto nearest_node_position = map.getPosition(nearest_node);
            auto random_node_position  = map.getPosition(random_node);

            auto getDirection = [&random_node_position, &nearest_node_position]()
            { return sf::Vector2f(random_node_position - nearest_node_position); };

            auto normalize = [](sf::Vector2f vec)
            {
                float norm = std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2));
                return sf::Vector2f(vec.x / norm, vec.y / norm);
            };

            auto direction    = normalize(getDirection());
            auto step         = sf::Vector2f(direction.x * config_.step_size,
                                     direction.y * config_.step_size);
            auto new_position = nearest_node_position + step;
            auto new_node     = map.getGridIndex(new_position);

            if (parents.count(new_node))
            {
                continue;
            }

            if (!map.isIndexWithinMap(new_node) || isVertexInObstacle(new_node, map) ||
                isEdgeInObstacle(nearest_node, new_node, map))
            {
                continue;
            }

            explored_nodes_.push_back(new_node);
            parents[new_node] = nearest_node;

            if (isVertexInGoalRegion(new_node, goal))
            {
                std::cout << "RRT Path Found within " << i << " iterations"
                          << "\n";
                // for(const auto& [key, value] : parents)
                // {
                //     std::cout << "Key: " << value.x << " " << value.y
                //               << " Value: " << key.x << " " << key.y << "\n";
                // }

                for (auto idx = new_node; idx != start; idx = parents[idx])
                {
                    // std::cout << "Parent: " << parents[idx].x << " " << parents[idx].y
                    //           << " Child: " << idx.x << " " << idx.y << "\n";
                    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    path.push_back(idx);
                }
                return path;
            }
        }
        return path;
    }

    sf::Vector2i RRTPathFinder::getRandomPosition(const Map& map) const
    {
        auto row = map.getMapConfig().row_num;
        auto col = map.getMapConfig().col_num;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> row_dis(0, row - 1);
        std::uniform_int_distribution<int> col_dis(0, col - 1);
        return sf::Vector2i(col_dis(gen), row_dis(gen));
    }

    sf::Vector2i
    RRTPathFinder::getNearestNode(const sf::Vector2i& new_node,
                                  const std::vector<sf::Vector2i>& nodes) const
    {
        sf::Vector2i nearest_node;
        double min_dist = std::numeric_limits<double>::max();
        for (const auto& node : nodes)
        {
            double dist = std::sqrt(std::pow(node.x - new_node.x, 2) +
                                    std::pow(node.y - new_node.y, 2));
            if (dist < min_dist)
            {
                min_dist     = dist;
                nearest_node = node;
            }
        }
        return nearest_node;
    }

    bool RRTPathFinder::isVertexInGoalRegion(const sf::Vector2i& vertex,
                                             const sf::Vector2i& goal) const
    {
        return (std::sqrt(std::pow(vertex.x - goal.x, 2) +
                          std::pow(vertex.y - goal.y, 2)) < config_.goal_radius);
    }

    bool RRTPathFinder::isVertexInObstacle(const sf::Vector2i& vertex,
                                           const Map& map) const
    {
        return map.isGridObstacle(vertex);
    }

    bool RRTPathFinder::isEdgeInObstacle(const sf::Vector2i& start,
                                         const sf::Vector2i& end,
                                         const Map& map) const
    {
        std::vector<sf::Vector2i> grids = map.getGridsBetweenIdx(start, end);
        for (const auto& grid : grids)
        {
            if (map.isGridObstacle(grid))
            {
                return true;
            }
        }
        return false;
    }
}  // namespace mas