#include "path_finder/astar.hpp"

#include <chrono>
#include <cmath>
#include <iostream>
#include <queue>
#include <thread>
#include <unordered_map>
#include <unordered_set>

namespace mas
{
    AStarPathFinder::AStarPathFinder(AstarType type, DirectionType direction)
        : type_ {type}
        , direction_type_ {direction}
    {
    }

    std::vector<sf::Vector2i> AStarPathFinder::findPath(const Map& map,
                                                        const sf::Vector2i& start,
                                                        const sf::Vector2i& goal)
    {
        auto row                         = map.getMapConfig().row_num;
        auto col                         = map.getMapConfig().col_num;
        const DirectionT step_directions = direction_map[direction_type_];

        auto isWithinMap = [&map](const sf::Vector2i& idx)
        { return map.isIndexWithinMap(idx); };
        auto isObstacle = [&map](const sf::Vector2i& idx)
        { return map.isGridObstacle(idx); };

        explored_nodes_.clear();
        std::vector<Node> open_set;
        std::unordered_set<sf::Vector2i, vector2i_hash> closed_set;
        std::unordered_map<sf::Vector2i, sf::Vector2i, vector2i_hash> parents;

        parents[start] = sf::Vector2i(-1, -1);
        open_set.push_back(Node(start, 0, getHCost(start, goal)));

        while (!open_set.empty())
        {
            auto current_it = open_set.begin();
            auto current    = *current_it;

            for (auto it = open_set.begin(); it != open_set.end(); ++it)
            {
                if (it->f_cost < current.f_cost)
                {
                    current    = *it;
                    current_it = it;
                }
            }
            explored_nodes_.push_back(current.idx);

            if (current.idx == goal)
            {
                std::vector<sf::Vector2i> path;
                for (auto idx = goal; idx != start; idx = parents[idx])
                {
                    path.push_back(idx);
                }

                path.push_back(start);
                std::reverse(path.begin(), path.end());
                return path;
            }

            open_set.erase(current_it);
            closed_set.insert(current.idx);

            for (const auto& dir : step_directions)
            {
                auto next =
                    sf::Vector2i(current.idx.x + dir.first, current.idx.y + dir.second);
                
                if (!isWithinMap(next) || isObstacle(next) || closed_set.count(next))
                {
                    continue;
                }
                
                explored_nodes_.push_back(next);

                const double g_cost =
                    (type_ == AstarType::GREEDY) ? 0.0 : getGCost(current.idx, next);
                const double h_cost =
                    (type_ == AstarType::DIJKSTRA) ? 0.0 : getHCost(next, goal);
                const double f_cost = g_cost + h_cost;

                auto it =
                    std::find_if(open_set.begin(),
                                 open_set.end(),
                                 [&next](const Node& node) { return node.idx == next; });

                if (it == open_set.end())
                {
                    open_set.push_back(Node(next, g_cost, h_cost));
                    parents[next] = current.idx;
                }
                else
                {
                    if (g_cost < it->g_cost)
                    {
                        it->g_cost    = g_cost;
                        it->f_cost    = f_cost;
                        parents[next] = current.idx;
                    }
                }
            }
        }
        return {};
    }

    double AStarPathFinder::getGCost(const sf::Vector2i& a, const sf::Vector2i& b) const
    {
        return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    }

    double AStarPathFinder::getHCost(const sf::Vector2i& a, const sf::Vector2i& b) const
    {
        using HeuristicT =
            std::function<double(const sf::Vector2i&, const sf::Vector2i&)>;

        HeuristicT manhattan = [](const sf::Vector2i& a, const sf::Vector2i& b)
        { return (std::abs(a.x - b.x) + std::abs(a.y - b.y)); };

        HeuristicT euclidean = [](const sf::Vector2i& a, const sf::Vector2i& b)
        { return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2)); };

        if (direction_type_ == DirectionType::FOUR)
        {
            return manhattan(a, b);
        }
        else
        {
            return euclidean(a, b);
        }
    }
}  // namespace mas