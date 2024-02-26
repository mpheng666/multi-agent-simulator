#ifndef MAS_CORE__GRID_HPP_
#define MAS_CORE__GRID_HPP_

#include "SFML/Graphics.hpp"

#include <vector>

namespace mas
{
    enum class GridType : int
    {
        EMPTY = 0,
        OBSTACLE,
        START,
        GOAL,
        PATH,
        EXPLORED,
    };

    struct GridConfig
    {
        sf::Vector2f position;
        sf::Vector2f size;
        sf::Color fill_color;
        sf::Color outline_color;
        float outline_thickness;
    };

    class Grid : public sf::RectangleShape
    {
        public:
        Grid() = default;
        Grid(const GridConfig& config);
        ~Grid() = default;

        void setGridConfig(const GridConfig& config);
        GridConfig getGridConfig() const { return grid_config_; }
        void setType(GridType type);
        GridType getType() const;

        private:
        GridConfig grid_config_;
        GridType type_ {GridType::EMPTY};
    };

}  // namespace mas

#endif