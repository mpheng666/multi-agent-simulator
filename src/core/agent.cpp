#include "core/agent.hpp"

namespace mas
{
    Agent::Agent(const AgentConfig& config, Map& map)
        : Grid(config.grid_config)
        , agent_config_(config.grid_config)
        , map_(map)
    {
    }

    void Agent::setAgentConfig(const GridConfig& config) { agent_config_ = config; }

    void Agent::setMap(Map& map) { map_ = map; }

    void Agent::move(const sf::Vector2f& direction)
    {
        sf::Vector2f new_position = getPosition() + direction;
        if (map_.isPositionWithinMap(new_position))
        {
            setPosition(new_position);
        }
    }

    void Agent::draw(sf::RenderWindow& window) const { window.draw(*this); }

}  // namespace mas