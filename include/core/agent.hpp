#ifndef MAS_CORE_AGENT_HPP_
#define MAS_CORE_AGENT_HPP_

#include "SFML/Graphics.hpp"

namespace mas {
    class Agent : public sf::RectangleShape {
    public:
        Agent(const int step_size)
        {
            texture_.loadFromFile("/home/mpheng/workspace/mas_ws/multi-agent-simulator/"
                                  "images/agent_bug.png");
            setTexture(&texture_, true);
            setPosition(sf::Vector2f(step_size / 2.0f, step_size / 2.0f));
            setSize(sf::Vector2f(step_size, step_size));
            setOrigin(step_size / 2.0f, step_size / 2.0f);
        }

        // sf::Vector2f getSize() { return texture_.getSize(); }

    private:
        sf::Texture texture_;
    };
} // namespace mas

#endif