#include "simulator/simulator.hpp"

namespace mas {

    Simulator::Simulator(const int window_width,
                         const int window_height,
                         const std::string& window_name,
                         const int window_framerate_limit)
        : rwindow_(sf::VideoMode(window_width, window_height),
                   window_name,
                   sf::Style::Titlebar | sf::Style::Close)
        , map_(1000, 600, 50, window_width / 2.0f, window_height / 2.0f)
        , agent_(map_.getStepSize(), map_)
    {
        map_.spawnObstacles(30);
        agent_.internal_map_.addObstacles(map_.getObstacles());
        agent_.internal_map_.setGrids(map_.getGrids());
    }

    void Simulator::renderMap()
    {
        for (auto i = 0; i < map_.getColumnSize(); ++i) {
            for (auto j = 0; j < map_.getRowSize(); ++j) {
                float position_x = -map_.origin_x_ + map_.offset_x_ + i * map_.step_size_;
                float position_y = -map_.origin_y_ + map_.offset_y_ + j * map_.step_size_;
                rwindow_.draw(map_.getGrids().at(i).at(j));
            }
        }
    }

    void Simulator::processEvents()
    {
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
    }

    void Simulator::run()
    {
        rwindow_.setFramerateLimit(60);
        Grid goal;
        goal.setIndex({3, 5});
        agent_.setGoal(goal);
        agent_.searchPath();
        auto path = agent_.getFoundPath();
        map_.setPath(path);
        while (rwindow_.isOpen()) {
            processEvents();
            renderMap();
            rwindow_.draw(agent_);
            rwindow_.display();
            rwindow_.clear(sf::Color::Black);
        }
    }
} // namespace mas