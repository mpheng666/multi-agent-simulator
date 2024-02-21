#ifndef MAS_CORE__BUTTON_HPP_
#define MAS_CORE__BUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

namespace mas
{
    class Button
    {
        public:
        Button() = default;
        ~Button() = default;

        sf::RectangleShape shape_;
        sf::Text text_;
        sf::Font font_;

        bool isMouseOnButton(const sf::Vector2i& mouse_pos) const;
        void draw(sf::RenderWindow& window) const;
    };
}  // namespace mas

#endif
