#ifndef MAS_GRID_HPP_
#define MAS_GRID_HPP_

#include "SFML/Graphics.hpp"
#include <array>
namespace mas {
    using Index = std::array<unsigned int, 2>;
    enum class SpaceState : int { UNKNOWN, EMPTY, OCCUPIED };
    class Grid : public sf::RectangleShape {
    public:
        SpaceState space_state_{SpaceState::UNKNOWN};
        Index index_{0, 0};
        sf::Vector2f map_position_{0.0f, 0.0f};

    private:
        sf::Texture texture_;
    };
} // namespace mas

#endif