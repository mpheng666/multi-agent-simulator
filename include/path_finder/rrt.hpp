#ifndef MAS_PATH_FINDER__RRT_HPP_
#define MAS_PATH_FINDER__RRT_HPP_

#include "path_finder/path_finder.hpp"

namespace mas
{
    class RRTPathFinder : public IPathFinder
    {
        public:
        enum class RRTType
        {
            RRT,
            RRT_STAR,
        };
        
        struct RRTConfig
        {
            RRTType type {RRTType::RRT_STAR};
            double step_size {};
            double goal_bias {};
            double goal_radius {};
            int max_iter {};
        };

        RRTPathFinder(RRTConfig config);

        void setRRTConfig(const RRTConfig& config) { config_ = config; }

        std::vector<sf::Vector2i> findPath(const Map& map,
                                           const sf::Vector2i& start,
                                           const sf::Vector2i& goal) override;

        std::vector<sf::Vector2i> getExploredNodes() const { return explored_nodes_; }

        private:
        RRTConfig config_;
        std::vector<sf::Vector2i> explored_nodes_;

        sf::Vector2i getRandomPosition(const Map& map);
        sf::Vector2i getNearestNode(const sf::Vector2i& new_node,
                                    const std::vector<sf::Vector2i>& nodes);
        bool isVertexInGoalRegion(const sf::Vector2i& vertex, const sf::Vector2i& goal);
        bool isVertexInObstacle(const sf::Vector2i& vertex, const Map& map);
    };

}  // namespace mas

#endif