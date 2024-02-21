#include "core/simulator.hpp"

int main(int argc, char** argv)
{
    using namespace mas;

    WindowConfig window_config;
    window_config.width  = 1000;
    window_config.height = 600;
    window_config.name   = "Multi-Agent-Simulator";

    MapConfig map_config;
    map_config.col_num   = 40;
    map_config.row_num   = 30;
    map_config.grid_size = 20;
    Map map(map_config);

    std::vector<Agent> agents;
    AgentConfig agent_config;
    agent_config.grid_config = map.getGrids()[0][0].getGridConfig();
    agent_config.grid_config.fill_color = sf::Color::Green;
    auto start = map.getPosition({0,10});
    agent_config.grid_config.position = start;
    agents.emplace_back(agent_config, map);

    Simulator simulator(window_config, map, agents);
    simulator.run();

    return 0;
}