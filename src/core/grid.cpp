#include "core/grid.hpp"

namespace mas
{
    Grid::Grid(const GridConfig& config)
        : grid_config_(config)
    {
        setPosition(grid_config_.position);
        setSize(grid_config_.size);
        setFillColor(grid_config_.fill_color);
        setOutlineColor(grid_config_.outline_color);
        setOutlineThickness(grid_config_.outline_thickness);
    }

    void Grid::setGridConfig(const GridConfig& config)
    {
        grid_config_ = config;
        setPosition(grid_config_.position);
        setSize(grid_config_.size);
        setFillColor(grid_config_.fill_color);
        setOutlineColor(grid_config_.outline_color);
        setOutlineThickness(grid_config_.outline_thickness);
    }

    bool Grid::isObstacle() const
    {
        return getFillColor() == sf::Color::Black;
    }
}  // namespace mas