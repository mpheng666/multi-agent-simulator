#ifndef MAS_PATH_FINDER__ASTAR_HPP_
#define MAS_PATH_FINDER__ASTAR_HPP_

#include "path_finder/path_finder.hpp"

namespace mas
{
    class AStarPathFinder : public IPathFinder
    {
        public:
        enum class AstarType
        {
            DIJKSTRA,
            GREEDY,
            ASTAR,
        };

        AStarPathFinder(AstarType type          = AstarType::ASTAR,
                        DirectionType direction = DirectionType::EIGHT);

        std::vector<sf::Vector2i> findPath(const Map& map,
                                           const sf::Vector2i& start,
                                           const sf::Vector2i& goal) override;

        std::vector<sf::Vector2i> getExploredNodes() const { return explored_nodes_; }

        private:
        struct Node
        {
            sf::Vector2i idx;
            double g_cost;
            double h_cost;
            double f_cost;

            Node(const sf::Vector2i& idx, double g_cost, double h_cost)
                : idx(idx)
                , g_cost(g_cost)
                , h_cost(h_cost)
                , f_cost(g_cost + h_cost)
            {
            }

            bool operator<(const Node& other) const { return f_cost > other.f_cost; }
        };

        AstarType type_ {AstarType::ASTAR};
        DirectionType direction_type {DirectionType::EIGHT};
        std::vector<sf::Vector2i> explored_nodes_;

        double getGCost(const sf::Vector2i& a, const sf::Vector2i& b) const;
        double getHCost(const sf::Vector2i& a, const sf::Vector2i& b) const;
    };

}  // namespace mas

#endif