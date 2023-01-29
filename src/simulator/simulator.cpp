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
    , map_(300, 300, 10, 10, rwindow_)
    , width_step_(window_width / col)
    , height_step_(window_height / row)
{
}

void Simulator::run()
{
    initialize_objects(agent_);
    rwindow_.setFramerateLimit(60);
    // mas_path_finding_.start(map_, 10, 10, 50, 60, grid_w_, grid_h_);

    while (rwindow_.isOpen()) {
        sf::Event event;
        while (rwindow_.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    rwindow_.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Up: {
                            const sf::Vector2f offset(0, -height_step_);
                            agent_.move(offset);
                        } break;
                        case sf::Keyboard::Down: {
                            const sf::Vector2f offset(0, height_step_);
                            agent_.move(offset);
                        } break;
                        case sf::Keyboard::Left: {
                            const sf::Vector2f offset(-width_step_, 0);
                            agent_.move(offset);
                        } break;
                        case sf::Keyboard::Right: {
                            const sf::Vector2f offset(width_step_, 0);
                            agent_.move(offset);
                        } break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }

        map_.renderMap();
        rwindow_.draw(agent_);
        rwindow_.display();
        rwindow_.clear();
    }
}

void Simulator::initialize_objects(mas_object::MASObject& object)
{
    object.setSize(sf::Vector2f(grid_w_, grid_h_));
    object.setFillColor(sf::Color::Red);
    object.setPosition(sf::Vector2f(50, 50));
}