#ifndef MAS_CORE_AGENT_HPP_
#define MAS_CORE_AGENT_HPP_

#include "SFML/Graphics.hpp"

namespace mas {
    class Agent : public sf::Sprite {
    public:
        Agent()
        {
            texture_.loadFromFile("/home/mpheng/workspace/mas_ws/multi-agent-simulator/"
                                  "images/agent_lizard.png");
            setTexture(texture_);
            setOrigin(texture_.getSize().x / 2.0f, texture_.getSize().y / 2.0f);
        }

        sf::Vector2u getSize() { return texture_.getSize(); }

    private:
        sf::Texture texture_;
    };
} // namespace mas

#endif