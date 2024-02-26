#ifndef MAS_PATH_FINDER__PATH_FINDER_HPP_
#define MAS_PATH_FINDER__PATH_FINDER_HPP_

#include "core/map.hpp"

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

        enum class DirectionType
        {
            FOUR,
            EIGHT,
        };

        using DirectionT = std::vector<std::pair<int, int>>;

        const DirectionT DIRECTIONS4 = {
            {0, 1},
            {1, 0},
            {0, -1},
            {-1, 0},
        };

        const DirectionT DIRECTIONS8 = {
            {0, 1},
            {1, 0},
            {0, -1},
            {-1, 0},
            {1, 1},
            {1, -1},
            {-1, -1},
            {-1, 1},
        };

        std::unordered_map<DirectionType, DirectionT> direction_map = {
            {DirectionType::FOUR, DIRECTIONS4},
            {DirectionType::EIGHT, DIRECTIONS8},
        };
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