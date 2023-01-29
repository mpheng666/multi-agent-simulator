#ifndef MAS_CORE_AGENT_HPP_
#define MAS_CORE_AGENT_HPP_

#include "SFML/Graphics.hpp"
#include <core/map.hpp>
#include <iostream>

namespace mas {
    class Agent : public sf::RectangleShape {
    public:
        Agent(const int step_size, const Map& map)
            : step_size_(step_size)
            , map_(map)
        {
            texture_.loadFromFile("/home/mpheng/workspace/mas_ws/multi-agent-simulator/"
                                  "images/agent_bug.png");
            setTexture(&texture_, true);
            setPosition(sf::Vector2f(step_size / 2.0f, step_size / 2.0f));
            setSize(sf::Vector2f(step_size, step_size));
            setOrigin(step_size / 2.0f, step_size / 2.0f);
        }

        void updateMapObstacles(const std::vector<sf::Vector2u>& obstacles)
        {
            map_.setObstacles(obstacles);
        }

        void processKeyPressed(const sf::Event& event)
        {
            switch (event.key.code) {
                case sf::Keyboard::Up: {
                    const sf::Vector2f offset(0, getSize().y);
                    sf::Vector2u next_index(current_idx_.x, --current_idx_.y);
                    if (getRotation() != 0) {
                        setRotation(0);
                    }
                    else if (!isCollide(next_index)) {
                        move(-offset);
                    }
                } break;
                case sf::Keyboard::Down: {
                    const sf::Vector2f offset(0, getSize().y);
                    sf::Vector2u next_index(current_idx_.x, ++current_idx_.y);
                    if (getRotation() != 180) {
                        setRotation(180);
                    }
                    else if (!isCollide(next_index)) {
                        move(offset);
                    }
                } break;
                case sf::Keyboard::Left: {
                    const sf::Vector2f offset(getSize().x, 0);
                        sf::Vector2u next_index(--current_idx_.x, current_idx_.y);
                    if (getRotation() != 270) {
                        setRotation(270);
                    }
                    else if (!isCollide(next_index)) {
                        move(-offset);
                    }
                } break;
                case sf::Keyboard::Right: {
                    const sf::Vector2f offset(getSize().x, 0);
                        sf::Vector2u next_index(++current_idx_.x, current_idx_.y);
                    if (getRotation() != 90) {
                        setRotation(90);
                    }
                    else if (!isCollide(next_index)) {
                        move(offset);
                    }
                } break;
                default:
                    break;
            }
            calculateCurrentIndex();
            std::cout << "Current index: " << current_idx_.x << "," << current_idx_.y
                      << "\n";
        }

    private:
        sf::Texture texture_;
        int step_size_{};
        Map map_;
        sf::Vector2u current_idx_;

        void calculateCurrentIndex()
        {
            current_idx_ =
            sf::Vector2u(getPosition().x / step_size_, getPosition().y / step_size_);
        }

        bool isCollide(const sf::Vector2u& next_index)
        {
            std::cout << "Next index: " << next_index.x << "," << next_index.y << "\n";
            for (const auto& obstacle : map_.getObstacles()) {
                std::cout << "obstacle: " << obstacle.x << "," << obstacle.y << " ";
                if (next_index.x == obstacle.x)
                    if (next_index.y == obstacle.y) {
                        std::cout << "Collide! \n";
                        return true;
                    }
            }
            std::cout << "\n";
            return false;
        }
    };
} // namespace mas

#endif