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
    class Agent : public Grid
    {
        public:
        Agent(const AgentConfig& config, Map& map);
        ~Agent() = default;

        void setAgentConfig(const GridConfig& config);
        void setMap(Map& map);
        void move(const sf::Vector2f& direction);
        void draw(sf::RenderWindow& window) const;

        private:
        GridConfig agent_config_;
        Map& map_;
    };

}  // namespace mas

#endif