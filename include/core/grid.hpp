#ifndef MAS_CORE__GRID_HPP_
#define MAS_CORE__GRID_HPP_

#include "SFML/Graphics.hpp"
#include <vector>

namespace mas
{
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
        bool isObstacle() const;

        private:
        GridConfig grid_config_;
    };

}  // namespace mas

#endif