#include "simulator/simulator.hpp"

namespace mas {

    Simulator::Simulator(const int window_width,
                         const int window_height,
                         const std::string& window_name,
                         const int window_framerate_limit)
        : rwindow_(sf::VideoMode(window_width, window_height),
                   window_name,
                   sf::Style::Titlebar | sf::Style::Close)
        , map_(1000, 600, 20, 12, window_width / 2.0f, window_height / 2.0f, rwindow_)
        , agent_(map_.getStepSize())
    {
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
                        switch (event.key.code) {
                            case sf::Keyboard::Up: {
                                const sf::Vector2f offset(0, agent_.getSize().y);
                                if (agent_.getRotation() == 0) {
                                    agent_.move(-offset);
                                }
                                else {
                                    agent_.setRotation(0);
                                }
                            } break;
                            case sf::Keyboard::Down: {
                                const sf::Vector2f offset(0, agent_.getSize().y);
                                if (agent_.getRotation() == 180) {
                                    agent_.move(offset);
                                }
                                else {
                                    agent_.setRotation(180);
                                }
                            } break;
                            case sf::Keyboard::Left: {
                                const sf::Vector2f offset(agent_.getSize().x, 0);
                                if (agent_.getRotation() == 270) {
                                    agent_.move(-offset);
                                }
                                else {
                                    agent_.setRotation(270);
                                }
                            } break;
                            case sf::Keyboard::Right: {
                                const sf::Vector2f offset(agent_.getSize().x, 0);
                                if (agent_.getRotation() == 90) {
                                    agent_.move(offset);
                                }
                                else {
                                    agent_.setRotation(90);
                                }
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
            rwindow_.clear(sf::Color::Black);
        }
    }
} // namespace mas