#ifndef MAS_CORE__AGENT_HPP_
#define MAS_CORE__AGENT_HPP_

#include "SFML/Graphics.hpp"
#include "core/map.hpp"
namespace mas
{
    struct AgentConfig
    {
        GridConfig grid_config;
    };

    enum class MoveDirection : int8_t
    {
        UP    = 1,
        DOWN  = 2,
        LEFT  = 3,
        RIGHT = 4,
    };

    class Agent : public Grid
    {
        public:
        Agent(const AgentConfig& config, Map& map);
        ~Agent() = default;

        void setAgentConfig(const GridConfig& config);
        void setMap(Map& map);
        void move(MoveDirection direction);
        void draw(sf::RenderWindow& window) const;

        private:
        GridConfig agent_config_;
        Map& map_;
    };

}  // namespace mas

#endif