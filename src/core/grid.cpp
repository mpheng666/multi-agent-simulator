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

    void Grid::setType(GridType type)
    {
        switch (type)
        {
            case GridType::EMPTY:
                setFillColor(sf::Color::White);
                break;
            case GridType::OBSTACLE:
                setFillColor(sf::Color::Black);
                break;
            case GridType::START:
                setFillColor(sf::Color::Green);
                break;
            case GridType::GOAL:
                setFillColor(sf::Color::Red);
                break;
            case GridType::PATH:
                setFillColor(sf::Color::Blue);
                break;
            case GridType::EXPLORED:
                setFillColor(sf::Color::Magenta);
                break;
        }
        type_ = type;
    }

    GridType Grid::getType() const { return type_; }

}  // namespace mas