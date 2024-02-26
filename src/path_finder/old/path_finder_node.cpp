
#include "bfs.hpp"
#include "path_finder.hpp"

#include <random>

using namespace mas;

int main()
{
    using namespace std::chrono_literals;
    static constexpr int MIN_MAP_SIZE = 40;
    static constexpr int MAX_MAP_SIZE = 50;
    static constexpr auto SLEEP_DURATION_MS = 50ms;
    static constexpr int AGENT_COUNT = 5;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(MIN_MAP_SIZE, MAX_MAP_SIZE);
    MapT map(dis(gen), std::vector<char>(dis(gen), ' '));

    // fill map with random obstacles up to X% of the map
    static constexpr int OBSTACLE_PERCENTAGE = 20;
    std::uniform_int_distribution<int> dis1(0, 100);
    for (auto& row : map)
    {
        for (auto& cell : row)
        {
            if (dis1(gen) < OBSTACLE_PERCENTAGE)
            {
                cell = '.';
            }
        }
    }

    PathFinder::printMap(map);

    std::uniform_int_distribution<int> disx(0, map.size() - 1);
    std::uniform_int_distribution<int> disy(0, map.front().size() - 1);

    for(int i = 0; i < AGENT_COUNT; ++i)
    {
        PoseT start;
        PoseT goal;
        start.x = disx(gen);
        start.y = disy(gen);
        goal.x  = disx(gen);
        goal.y  = disy(gen);

        map[start.x][start.y] = 's';
        map[goal.x][goal.y]   = 'g';

        BFS bfs(map, '1' + i);

        const auto path = bfs.planPath(start, goal);

        if (path)
        {
            for (const auto& pose : path.value())
            {
                if (map[pose.x][pose.y] != 's' && map[pose.x][pose.y] != 'g')
                {
                    map[pose.x][pose.y] = '1' + i;
                    PathFinder::printMap(map);
                    std::this_thread::sleep_for(SLEEP_DURATION_MS);
                }
            }
        }
        else
        {
            std::cout << "no path found!";
        }
    }
    return 0;
}