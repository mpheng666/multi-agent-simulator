#ifndef PATH_FINDING__DIJKSTRA_HPP_
#define PATH_FINDING__DIJKSTRA_HPP_

#include "path_finder.hpp"

#include <chrono>
#include <queue>

namespace mas
{
    class Dijkstra : public PathFinder
    {
        public:
        Dijkstra(MapT& map, char agent_symbol)
            : PathFinder(map, agent_symbol)
        {
        }

        std::optional<std::vector<PoseT>> planPath(const PoseT& start,
                                                   const PoseT& goal) override
        {
            if (isOutOfBound(start))
            {
                // std::cout << "start OOB!";
                return std::nullopt;
            }
            if (isOutOfBound(goal))
            {
                // std::cout << "goal OOB!";
                return std::nullopt;
            }

            std::vector<PoseT> path;
            std::queue<PoseT> q;
            std::unordered_set<PoseT> visited;
            std::unordered_map<PoseT, PoseT> parents;

            q.push(start);
            bool is_goal_found {false};

            while (q.size() && !is_goal_found)
            {
                auto curr = q.front();
                q.pop();

                for (const auto& step : CARDINAL_STEP)
                {
                    const PoseT next = {curr.x + step.x, curr.y + step.y};

                    if (isOutOfBound(next))
                    {
                        continue;
                    }

                    if (next == goal)
                    {
                        parents[next] = curr;
                        // std::cout << "found goal! \n";
                        is_goal_found = true;
                        break;
                    }

                    // auto prev_state      = map_[next.x][next.y];
                    // map_[next.x][next.y] = 'e';
                    // using namespace std::chrono_literals;
                    // std::this_thread::sleep_for(1ms);
                    // printMap(map_);
                    // map_[next.x][next.y] = prev_state;

                    if (map_[next.x][next.y] == ' ' && !visited.count(next))
                    {
                        visited.insert(next);
                        parents[next] = curr;
                        q.push(next);
                    }
                }
            }

            if (is_goal_found)
            {
                for (PoseT at = goal; at != start; at = parents[at])
                {
                    path.push_back(at);
                }
                path.push_back(start);
                std::reverse(path.begin(), path.end());
                return path;
            }

            return std::nullopt;
        }
    };
}  // namespace mas

#endif