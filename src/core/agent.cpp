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

    void Agent::move(MoveDirection direction)
    {
        const sf::Vector2i position = sf::Vector2i(getPosition().x, getPosition().y);
        sf::Vector2i index          = map_.getGridIndex(position);
        switch (direction)
        {
            case MoveDirection::UP:
                if (map_.isIndexWithinMap({index.x, index.y - 1}) &&
                    !map_.isGridObstacle({index.x, index.y - 1}))
                {
                    setPosition(map_.getPosition({index.x, index.y - 1}));
                }
                break;
            case MoveDirection::DOWN:
                if (map_.isIndexWithinMap({index.x, index.y + 1}) && !map_.isGridObstacle({index.x, index.y + 1}))
                {
                    setPosition(map_.getPosition({index.x, index.y + 1}));
                }
                break;
            case MoveDirection::LEFT:
                if (map_.isIndexWithinMap({index.x - 1, index.y}) && !map_.isGridObstacle({index.x - 1, index.y}))
                {
                    setPosition(map_.getPosition({index.x - 1, index.y}));
                }
                break;
            case MoveDirection::RIGHT:
                if (map_.isIndexWithinMap({index.x + 1, index.y}) && !map_.isGridObstacle({index.x + 1, index.y}))
                {
                    setPosition(map_.getPosition({index.x + 1, index.y}));
                }
                break;
        }
    }

    void Agent::draw(sf::RenderWindow& window) const { window.draw(*this); }

}  // namespace mas