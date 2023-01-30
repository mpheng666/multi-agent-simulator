#ifndef MAS_CORE_AGENT_HPP_
#define MAS_CORE_AGENT_HPP_

#include "SFML/Graphics.hpp"
#include <core/map.hpp>
#include <iostream>

namespace mas {
    class Agent : public sf::RectangleShape {
    public:
        Agent(const int step_size, sf::RenderWindow& rw)
            : step_size_(step_size)
            , rw_(rw)
            , internal_map_(rw)
        {
            initialiseAgent();
        }

        void processKeyPressed(const sf::Event& event)
        {
            switch (event.key.code) {
                case sf::Keyboard::Up: {
                    const Index next_index{current_idx_.front(), --current_idx_.back()};
                    if (getRotation() != 0) {
                        setRotation(0);
                    }
                    else if (!isCollide(next_index)) {
                        const sf::Vector2f offset(0, getSize().y);
                        move(-offset);
                    }
                } break;
                case sf::Keyboard::Down: {
                    const Index next_index{current_idx_.front(), ++current_idx_.back()};
                    if (getRotation() != 180) {
                        setRotation(180);
                    }
                    else if (!isCollide(next_index)) {
                        const sf::Vector2f offset(0, getSize().y);
                        move(offset);
                    }
                } break;
                case sf::Keyboard::Left: {
                    const Index next_index{--current_idx_.front(), current_idx_.back()};
                    if (getRotation() != 270) {
                        setRotation(270);
                    }
                    else if (!isCollide(next_index)) {
                        const sf::Vector2f offset(getSize().x, 0);
                        move(-offset);
                    }
                } break;
                case sf::Keyboard::Right: {
                    const Index next_index{++current_idx_.front(), current_idx_.back()};
                    if (getRotation() != 90) {
                        setRotation(90);
                    }
                    else if (!isCollide(next_index)) {
                        const sf::Vector2f offset(getSize().x, 0);
                        move(offset);
                    }
                } break;
                default:
                    break;
            }
            updateCurrentIndex();
            std::cout << "Current index: " << current_idx_.front() << ","
                      << current_idx_.back() << "\n";
        }

        void initialiseAgent()
        {
            texture_.loadFromFile("/home/mpheng/workspace/mas_ws/multi-agent-simulator/"
                                  "images/agent_bug.png");
            setTexture(&texture_, true);
            setPosition(sf::Vector2f(step_size_ / 2.0f, step_size_ / 2.0f));
            setSize(sf::Vector2f(step_size_, step_size_));
            setOrigin(step_size_ / 2.0f, step_size_ / 2.0f);
        }

        Map internal_map_;

    private:
        sf::Texture texture_;
        int step_size_{};
        sf::RenderWindow& rw_;
        Index current_idx_;

        void updateCurrentIndex()
        {
            current_idx_.front() = getPosition().x / step_size_;
            current_idx_.back() = getPosition().y / step_size_;
        }

        bool isCollide(const Index& next_index)
        {
            // std::cout << "Next index: " << next_index.front() << "," << next_index.back()
            //           << "\n";
            for (const auto& obstacle : internal_map_.getObstacles()) {
                if (obstacle.front() == next_index.front())
                    if (obstacle.back() == next_index.back())
                        return true;
            }
            return false;
        }
    };
} // namespace mas

#endif