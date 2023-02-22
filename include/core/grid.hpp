#ifndef MAS_GRID_HPP_
#define MAS_GRID_HPP_

#include "SFML/Graphics.hpp"
#include <array>
#include <iostream>
namespace mas {
    struct Index {
        Index() = default;

        Index(unsigned int x, unsigned int y)
        {
            x = x;
            y = y;
        }
        unsigned int x{0};
        unsigned int y{0};

        bool operator==(const Index& other) const
        {
            return (x == other.x && y == other.y);
        }

        std::ostream& operator<<(std::ostream& os) const
        {
            std::cout << "x: " << x << " "
                      << "y: " << y << " | ";
            return os;
        }
    };

    struct IndexComparator {
        bool operator()(const Index& lhs, const Index& rhs) const
        {
            return lhs.x < rhs.x;
        }
    };

    enum class SpaceState : int { UNKNOWN, EMPTY, OCCUPIED };
    enum class VisitedState : int { NOT_VISITED, VISITED };
    class Grid : public sf::RectangleShape {
    public:
        Grid() = default;

        Grid(unsigned int x, unsigned int y)
        {
            index_.x = x;
            index_.y = y;
        }

        Grid(Index index) { index_ = index; }

        SpaceState space_state_{SpaceState::UNKNOWN};
        VisitedState visited_state{VisitedState::NOT_VISITED};

        sf::Vector2f map_position_{0.0f, 0.0f};

        void setIndex(const Index& index) { index_ = index; }

        Index getIndex() const { return index_; }

        void setText() { text_.setString("123"); }

    private:
        Index index_{0, 0};
        sf::Texture texture_;
        sf::Text text_;
    };
} // namespace mas

#endif