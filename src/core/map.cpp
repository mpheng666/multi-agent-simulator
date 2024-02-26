#include "core/map.hpp"

namespace mas
{
    Map::Map(const MapConfig& map_config)
        : map_config_(map_config)
    {
        init();
    }

    void Map::init()
    {
        grids_.resize(map_config_.row_num);
        for (size_t i = 0; i < map_config_.row_num; ++i)
        {
            grids_[i].resize(map_config_.col_num);
            for (size_t j = 0; j < map_config_.col_num; ++j)
            {
                GridConfig grid_config;
                grid_config.position   = {static_cast<float>(j * map_config_.grid_size),
                                          static_cast<float>(i * map_config_.grid_size)};
                grid_config.size       = {static_cast<float>(map_config_.grid_size),
                                          static_cast<float>(map_config_.grid_size)};
                grid_config.fill_color = sf::Color::White;
                // grid_config.outline_color     = sf::Color::Black;
                // grid_config.outline_thickness = 1;
                grids_[i][j].setGridConfig(grid_config);
            }
        }
    }

    MapConfig Map::getMapConfig() const { return map_config_; }

    Grids& Map::getGrids() { return grids_; }

    void Map::addObstacle(const sf::Vector2i& index)
    {
        if (isIndexWithinMap(index) &&
            grids_[index.y][index.x].getType() == GridType::EMPTY)
        {
            grids_[index.y][index.x].setType(GridType::OBSTACLE);
        }
    }

    void Map::clearObstacle(const sf::Vector2i& index)
    {
        if (isIndexWithinMap(index) &&
            grids_[index.y][index.x].getType() == GridType::OBSTACLE)
        {
            grids_[index.y][index.x].setType(GridType::EMPTY);
        }
    }

    sf::Vector2i Map::getGridIndex(const sf::Vector2i& position) const
    {
        return sf::Vector2i(position.x / map_config_.grid_size,
                            position.y / map_config_.grid_size);
    }

    sf::Vector2f Map::getPosition(const sf::Vector2i& index) const
    {
        return sf::Vector2f(index.x * map_config_.grid_size,
                            index.y * map_config_.grid_size);
    }

    void Map::clearObstacles()
    {
        for (size_t i = 0; i < map_config_.row_num; ++i)
        {
            for (size_t j = 0; j < map_config_.col_num; ++j)
            {
                if (grids_[i][j].getType() == GridType::OBSTACLE)
                {
                    grids_[i][j].setType(GridType::EMPTY);
                }
            }
        }
    }

    void Map::clearPath()
    {
        for (size_t i = 0; i < map_config_.row_num; ++i)
        {
            for (size_t j = 0; j < map_config_.col_num; ++j)
            {
                if (grids_[i][j].getType() == GridType::PATH)
                {
                    grids_[i][j].setType(GridType::EMPTY);
                }
            }
        }
    }

    bool Map::isPositionWithinMap(const sf::Vector2f& position) const
    {
        return position.x >= 0.0f &&
               position.x <
                   static_cast<float>(map_config_.col_num * map_config_.grid_size) &&
               position.y >= 0.0f &&
               position.y <
                   static_cast<float>(map_config_.row_num * map_config_.grid_size);
    }

    bool Map::isIndexWithinMap(const sf::Vector2i& index) const
    {
        return index.x >= 0 && index.x < static_cast<int>(map_config_.col_num) &&
               index.y >= 0 && index.y < static_cast<int>(map_config_.row_num);
    }

    void Map::addRandomObstacles(size_t num)
    {
        for (size_t i = 0; i < num; ++i)
        {
            auto x = static_cast<int>(rand() % map_config_.col_num);
            auto y = static_cast<int>(rand() % map_config_.row_num);
            if (grids_[y][x].getType() == GridType::EMPTY)
            {
                grids_[y][x].setType(GridType::OBSTACLE);
            }
        }
    }

    bool Map::isGridObstacle(const sf::Vector2i& index) const
    {
        return grids_[index.y][index.x].getType() == GridType::OBSTACLE;
    }

}  // namespace mas