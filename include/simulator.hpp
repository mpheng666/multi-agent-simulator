#ifndef MULTI_AGENT_SIMULATOR_SIMULATOR_HPP_
#define MULTI_AGENT_SIMULATOR_SIMULATOR_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace simulator {
class Simulator {
public:
    Simulator();
    virtual ~Simulator();
    void update();
    void render();

private:
    void initWindow();

    sf::RenderWindow *window_{nullptr};
    sf::Event event{};
};
} // namespace simulator

#endif