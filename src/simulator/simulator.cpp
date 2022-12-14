#include "simulator/simulator.hpp"

using namespace mas_simulator;

Simulator::Simulator(const int window_width,
                     const int window_height,
                     const std::string& window_name,
                     const int window_framerate_limit,
                     const int col,
                     const int row)
    : rwindow_(sf::VideoMode(window_width, window_height),
               window_name,
               sf::Style::Titlebar | sf::Style::Close)
    , map_(col, row)
{
}

void Simulator::run()
{
    initialize_map();
    initialize_objects();
    rwindow_.setFramerateLimit(60);
    mas_path_finding_.start(map_, 10, 10, 50, 60, grid_w_, grid_h_);

    while (rwindow_.isOpen()) {

        sf::Event event;
        while (rwindow_.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                rwindow_.close();
            }
        }

        rwindow_.clear(sf::Color::Black);


        // Rendering
        for (auto i = 0; i < map_.getColumnSize(); ++i) {
            for (auto j = 0; j < map_.getRowSize(); ++j) {
                float position_x = i * grid_w_;
                float position_y = j * grid_h_;
                map_.grid_map.at(i).at(j).setPosition(position_x, position_y);
                rwindow_.draw(map_.grid_map.at(i).at(j));
            }
        }

        rwindow_.draw(agent_);
        
        rwindow_.display();
    }
}

void Simulator::initialize_map()
{
    grid_w_ = rwindow_.getSize().x / map_.getColumnSize();
    grid_h_ = rwindow_.getSize().y / map_.getRowSize();

    for (auto i = 0; i < map_.getColumnSize(); ++i) {
        for (auto j = 0; j < map_.getRowSize(); ++j) {
            map_.grid_map.at(i).at(j).setSize(sf::Vector2f(grid_w_, grid_h_));
            map_.grid_map.at(i).at(j).setFillColor(sf::Color::White);
            map_.grid_map.at(i).at(j).setOutlineColor(sf::Color::Black);
            map_.grid_map.at(i).at(j).setOutlineThickness(1.0f);
        }
    }
}

void Simulator::initialize_objects()
{
    agent_.setSize(sf::Vector2f(grid_w_, grid_h_));
    agent_.setFillColor(sf::Color::Red);
    agent_.setPosition(sf::Vector2f(50, 50));
}