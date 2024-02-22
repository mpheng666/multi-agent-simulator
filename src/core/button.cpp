#include "core/button.hpp"

namespace mas
{
    bool Button::isMouseOnButton(const sf::Vector2i& mouse_pos) const
    {
        return shape_.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y);
    }

    void Button::draw(sf::RenderWindow& window) const
    {
        window.draw(shape_);
        window.draw(text_);
    }

    void Button::setOnClick(const std::function<void()>& onClickT)
    {
        onclick_ = onClickT;
    }
}  // namespace mas