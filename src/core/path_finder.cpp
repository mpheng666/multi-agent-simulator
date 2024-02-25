#include "core/path_finder.hpp"

#include <chrono>
#include <cmath>
#include <iostream>
#include <queue>
#include <thread>
#include <unordered_map>
#include <unordered_set>

namespace mas
{
    std::vector<sf::Vector2i> AStarPathFinder::findPath(const Map& map,
                                                        const sf::Vector2i& start,
                                                        const sf::Vector2i& goal)
    {
        auto row = map.getMapConfig().row_num;
        auto col = map.getMapConfig().col_num;

        HeuristicT manhattan = [](const sf::Vector2i& a, const sf::Vector2i& b)
        {
            return std::abs(a.x - b.x) + std::abs(a.y - b.y);
        };

        HeuristicT euclidean = [](const sf::Vector2i& a, const sf::Vector2i& b)
        {
            return static_cast<int>(std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2)));
        };

        DirectionT step_directions = direction_map[direction_type];

        HeuristicT getHCost;
        if (direction_type == DIRECTIONS::FOUR)
        {
            getHCost = manhattan;
        }
        else
        {
            getHCost = euclidean;
        }

        auto isWithinMap = [&map](const sf::Vector2i& idx)
        { return map.isIndexWithinMap(idx); };
        auto isObstacle = [&map](const sf::Vector2i& idx)
        { return map.isGridObstacle(idx); };

        std::priority_queue<Node> open_set;
        std::unordered_set<sf::Vector2i, vector2i_hash> closed_set;
        std::unordered_map<sf::Vector2i, sf::Vector2i, vector2i_hash> parents;

        parents[start] = sf::Vector2i(-1, -1);
        open_set.push(Node(start, 0, getHCost(start, goal)));

        while (!open_set.empty())
        {
            auto current = open_set.top();
            open_set.pop();

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

            closed_set.insert(current.idx);

            for (const auto& dir : step_directions)
            {
                auto next =
                    sf::Vector2i(current.idx.x + dir.first, current.idx.y + dir.second);

                if (!isWithinMap(next) || isObstacle(next) || closed_set.count(next))
                {
                    continue;
                }

                auto g_cost = current.g_cost + 1;
                auto h_cost = getHCost(next, goal);
                auto f_cost = g_cost + h_cost;

                if (parents.count(next) && f_cost >= open_set.top().f_cost)
                {
                    continue;
                }
                open_set.push(Node(next, g_cost, h_cost));
                parents[next] = current.idx;
            }
        }
        return {};
    }
}  // namespace mas