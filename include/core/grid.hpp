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
            this->x = x;
            this->y = y;
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

        Grid(unsigned int x,
             unsigned int y,
             const SpaceState& space_state = SpaceState::UNKNOWN,
             const VisitedState& visited_state = VisitedState::NOT_VISITED)
            : index_(x, y)
            , space_state_(space_state)
            , visited_state_(visited_state)
        {
            updateSpaceColour();
            updateVisitColour();
            setOutlineThickness(1.0f);
        }

        Grid(Index index) { index_ = index; }

        void setIndex(const Index& index) { index_ = index; }
        Index getIndex() const { return index_; }
        void setText() { text_.setString("123"); }

        sf::Vector2f map_position_{0.0f, 0.0f};

        SpaceState getSpaceState() const { return space_state_; }

        void setSpaceState(const SpaceState& space_state)
        {
            space_state_ = space_state;
            updateSpaceColour();
        }

        VisitedState getVisitedState() const { return visited_state_; }

        void setVisitedState(const VisitedState& visited_state)
        {
            visited_state_ = visited_state;
            updateVisitColour();
        }

    private:
        Index index_{0, 0};
        sf::Texture texture_;
        sf::Text text_;
        SpaceState space_state_{SpaceState::UNKNOWN};
        VisitedState visited_state_{VisitedState::NOT_VISITED};

        void updateSpaceColour()
        {
            switch (space_state_) {
                case SpaceState::UNKNOWN:
                    setFillColor(sf::Color::White);
                    break;
                case SpaceState::EMPTY:
                    setFillColor(sf::Color::Green);
                    break;
                case SpaceState::OCCUPIED:
                    setFillColor(sf::Color::Red);
                    break;
            }
        }

        void updateVisitColour()
        {
            switch (visited_state_) {
                case VisitedState::VISITED:
                    setOutlineColor(sf::Color::Yellow);
                    break;
                case VisitedState::NOT_VISITED:
                    setOutlineColor(sf::Color::Black);
                    break;
            }
        }
    };
} // namespace mas

#endif