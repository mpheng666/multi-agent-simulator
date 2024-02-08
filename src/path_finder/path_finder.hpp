#ifndef MAS_PATH_FINDER_HPP_
#define MAS_PATH_FINDER_HPP_

#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <optional>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct PoseT
{
    int x;
    int y;

    bool operator==(const PoseT& other) const { return x == other.x && y == other.y; }

    bool operator!=(const PoseT& other) const { return x != other.x || y != other.y; }

    bool operator<(const PoseT& other) const
    {
        return x < other.x || (x == other.x && y < other.y);
    }
};

namespace std
{
    template<>
    struct hash<PoseT>
    {
        size_t operator()(const PoseT& pose) const noexcept
        {
            size_t h1 = std::hash<int>()(pose.x);
            size_t h2 = std::hash<int>()(pose.y);
            // Use a bitwise shift and combine technique to mix hashes
            return h1 ^ (h2 << 1);  // Shift and combine
        }
    };
}  // namespace std

namespace mas
{
    static constexpr std::array<PoseT, 4> CARDINAL_STEP {
        {{0, 1}, {-1, 0}, {0, -1}, {1, 0}}};

    static constexpr std::array<PoseT, 8> ORDINAL_STEP {
        {{1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}}};

    using MapT = std::vector<std::vector<char>>;

    class PathFinder
    {
        public:
        PathFinder(const MapT& map)
            : map_(map)
        {
        }

        static const void printMap(const MapT& map)
        {
            for (int i = 0; i < map.size(); ++i)
            {
                for (int j = 0; j < map.front().size(); ++j)
                {
                    std::cout << map[i][j] << " ";
                }
                std::cout << "\n";
            }
            std::string separator_line;
            for (int i = 0; i < map.front().size(); ++i)
            {
                separator_line += "==";
            }
            std::cout << separator_line + "\n";
        }

        bool isOutOfBound(const PoseT& pose) const
        {
            if (map_.empty() || map_.front().empty())
            {
                return true;
            }
            return pose.x < 0 || pose.x >= map_.size() || pose.y < 0 ||
                   pose.y >= map_.front().size();
        }

        virtual std::optional<std::vector<PoseT>> planPath(const PoseT& start,
                                                           const PoseT& goal) = 0;

        MapT map_;
    };
}  // namespace mas

#endif