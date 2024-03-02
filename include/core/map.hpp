#ifndef MAS_CORE__MAP_HPP_
#define MAS_CORE__MAP_HPP_

#include <SFML/Graphics.hpp>
#include "core/grid.hpp"

namespace mas
{

    struct MapConfig
    {
        size_t row_num {};
        size_t col_num {};
        size_t grid_size {};
    };

    using Grids = std::vector<std::vector<Grid>>;

    class Map
    {
        public:
        Map(const MapConfig& config);
        ~Map() = default;

        MapConfig getMapConfig() const;
        Grids& getGrids();
        sf::Vector2i getGridIndex(const sf::Vector2f& position) const;
        sf::Vector2f getPosition(const sf::Vector2i& index) const;
        void addObstacle(const sf::Vector2i& index);
        void clearObstacle(const sf::Vector2i& index);
        void clearObstacles();
        void clearPath();
        bool isIndexWithinMap(const sf::Vector2i& index) const;
        bool isPositionWithinMap(const sf::Vector2f& position) const;
        void addRandomObstacles(size_t num);
        bool isGridObstacle(const sf::Vector2i& index) const;
        std::vector<sf::Vector2i> getGridsBetweenIdx(const sf::Vector2i& start,
                                                    const sf::Vector2i& end) const;

        private:
        MapConfig map_config_;
        Grids grids_;

        void init();
    };
}  // namespace mas

#endif