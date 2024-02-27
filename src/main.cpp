#include "core/simulator.hpp"
#include "path_finder/astar.hpp"
#include "path_finder/rrt.hpp"

int main(int argc, char** argv)
{
    using namespace mas;

    WindowConfig window_config;
    window_config.width  = 1500;
    window_config.height = 1000;
    window_config.name   = "Multi-Agent-Simulator";
    
    static constexpr int mapResolutionFactor = 1;

    MapConfig map_config;
    map_config.col_num   = 120 * mapResolutionFactor;
    map_config.row_num   = 80 * mapResolutionFactor;
    map_config.grid_size = 10 / mapResolutionFactor;
    Map map(map_config);

    std::vector<Agent> agents;
    AgentConfig agent_config;
    agent_config.grid_config            = map.getGrids()[0][0].getGridConfig();
    agent_config.grid_config.fill_color = sf::Color::Green;
    auto start                          = map.getPosition({0, 0});
    agent_config.grid_config.position   = start;
    agents.emplace_back(agent_config, map);

    // AStarPathFinder path_finder {
    //     AStarPathFinder::AstarType::ASTAR,
    //     IPathFinder::DirectionType::EIGHT,
    // };

    RRTPathFinder::RRTConfig rrt_config;
    rrt_config.max_iter = 2000 * mapResolutionFactor;
    rrt_config.step_size = 20 * mapResolutionFactor;
    rrt_config.goal_bias = 0.1;
    rrt_config.goal_radius = 3 * mapResolutionFactor;
    rrt_config.type = RRTPathFinder::RRTType::RRT_STAR;
    RRTPathFinder path_finder(rrt_config);

    Simulator simulator(window_config, map, agents, path_finder);
    simulator.run();

    return 0;
}