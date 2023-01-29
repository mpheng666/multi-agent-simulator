#include "simulator/simulator.hpp"

namespace mas {

    Simulator::Simulator(const int window_width,
                         const int window_height,
                         const std::string& window_name,
                         const int window_framerate_limit)
        : rwindow_(sf::VideoMode(window_width, window_height),
                   window_name,
                   sf::Style::Titlebar | sf::Style::Close)
        , map_(1000, 600, 10, 6, window_width / 2.0f, window_height / 2.0f, rwindow_)
        , agent_(map_.getStepSize(), map_)
    {
        map_.spawnObstacles(10);
        agent_.updateMapObstacles(map_.getObstacles());
    }

    void Simulator::run()
    {
        rwindow_.setFramerateLimit(60);

        while (rwindow_.isOpen()) {
            sf::Event event;
            while (rwindow_.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        rwindow_.close();
                        break;
                    case sf::Event::KeyPressed:
                        agent_.processKeyPressed(event);
                    default:
                        break;
                }
            }
            map_.renderMap();
            rwindow_.draw(agent_);
            rwindow_.display();
            rwindow_.clear(sf::Color::Black);
        }
    }
} // namespace mas