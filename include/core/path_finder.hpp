#ifndef MAS_CORE__PATH_FINDER_HPP_
#define MAS_CORE__PATH_FINDER_HPP_

#include "map.hpp"

#include <array>
#include <functional>
#include <memory>

namespace mas
{
    class IPathFinder
    {
        public:
        virtual ~IPathFinder() = default;
        virtual std::vector<sf::Vector2i>
        findPath(const Map& map, const sf::Vector2i& start, const sf::Vector2i& goal) = 0;

        struct pair_hash
        {
            template<class T1, class T2>
            std::size_t operator()(const std::pair<T1, T2>& pair) const
            {
                auto hash1 = std::hash<T1> {}(pair.first);
                auto hash2 = std::hash<T2> {}(pair.second);
                return hash1 ^ hash2;
            }
        };

        struct vector2i_hash
        {
            std::size_t operator()(const sf::Vector2i& vector) const
            {
                auto hash1 = std::hash<int> {}(vector.x);
                auto hash2 = std::hash<int> {}(vector.y);
                return hash1 ^ (hash2 << 1);
            }
        };

        enum class DIRECTIONS
        {
            FOUR,
            EIGHT,
        };

        using DirectionT = std::vector<std::pair<int, int>>;

        const std::vector<std::pair<int, int>> DIRECTIONS4 = {
            std::make_pair(0, 1),
            std::make_pair(1, 0),
            std::make_pair(0, -1),
            std::make_pair(-1, 0),
        };

        const std::vector<std::pair<int, int>> DIRECTIONS8 = {
            std::make_pair(0, 1),
            std::make_pair(1, 0),
            std::make_pair(0, -1),
            std::make_pair(-1, 0),
            std::make_pair(1, 1),
            std::make_pair(1, -1),
            std::make_pair(-1, -1),
            std::make_pair(-1, 1),
        };

        DIRECTIONS direction_type                                = DIRECTIONS::EIGHT;
        std::unordered_map<DIRECTIONS, DirectionT> direction_map = {
            {DIRECTIONS::FOUR, DIRECTIONS4},
            {DIRECTIONS::EIGHT, DIRECTIONS8},
        };
    };

    class AStarPathFinder : public IPathFinder
    {
        public:
        std::vector<sf::Vector2i> findPath(const Map& map,
                                           const sf::Vector2i& start,
                                           const sf::Vector2i& goal) override;

        using HeuristicT = std::function<int(const sf::Vector2i&, const sf::Vector2i&)>;

        private:
        struct Node
        {
            sf::Vector2i idx;
            int g_cost;
            int h_cost;
            int f_cost;

            Node(const sf::Vector2i& idx, int g_cost, int h_cost)
                : idx(idx)
                , g_cost(g_cost)
                , h_cost(h_cost)
                , f_cost(g_cost + h_cost)
            {
            }

            bool operator<(const Node& other) const { return f_cost > other.f_cost; }
        };
    };

    class DijkstraPathFinder : public IPathFinder
    {
        public:
        std::vector<sf::Vector2i> findPath(const Map& map,
                                           const sf::Vector2i& start,
                                           const sf::Vector2i& goal) override;
    };

    class BFSPathFinder : public IPathFinder
    {
        public:
        std::vector<sf::Vector2i> findPath(const Map& map,
                                           const sf::Vector2i& start,
                                           const sf::Vector2i& goal) override;
    };

    class DFSPathFinder : public IPathFinder
    {
        public:
        std::vector<sf::Vector2i> findPath(const Map& map,
                                           const sf::Vector2i& start,
                                           const sf::Vector2i& goal) override;
    };

    class GreedyPathFinder : public IPathFinder
    {
        public:
        std::vector<sf::Vector2i> findPath(const Map& map,
                                           const sf::Vector2i& start,
                                           const sf::Vector2i& goal) override;
    };

    class BestFirstPathFinder : public IPathFinder
    {
        public:
        std::vector<sf::Vector2i> findPath(const Map& map,
                                           const sf::Vector2i& start,
                                           const sf::Vector2i& goal) override;
    };

    class JumpPointPathFinder : public IPathFinder
    {
        public:
        std::vector<sf::Vector2i> findPath(const Map& map,
                                           const sf::Vector2i& start,
                                           const sf::Vector2i& goal) override;
    };

    class ThetaStarPathFinder : public IPathFinder
    {
        public:
        std::vector<sf::Vector2i> findPath(const Map& map,
                                           const sf::Vector2i& start,
                                           const sf::Vector2i& goal) override;
    };

}  // namespace mas

#endif