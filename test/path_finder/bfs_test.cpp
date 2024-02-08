#include "../../src/path_finder/bfs.hpp"
#include <gtest/gtest.h>

TEST(BFS, PlanPath)
{
    using namespace mas;
    MapT map(5, std::vector<char>(5, ' '));
    BFS bfs(map, '1');
    PoseT start {0, 0};
    PoseT goal {4, 4};
    auto path = bfs.planPath(start, goal);
    ASSERT_TRUE(path);
    ASSERT_EQ(path.value().size(), 9);
    ASSERT_EQ(path.value().at(0), start);
    ASSERT_EQ(path.value().at(8), goal);
}

TEST(BFS, PlanPathOutOfBound)
{
    using namespace mas;
    MapT map(5, std::vector<char>(5, ' '));
    BFS bfs(map, '1');
    PoseT start {0, 0};
    PoseT goal {5, 5};
    auto path = bfs.planPath(start, goal);
    ASSERT_FALSE(path);
}

TEST(BFS, PlanPathNoPath)
{
    using namespace mas;
    MapT map(5, std::vector<char>(5, ' '));
    BFS bfs(map, '1');
    PoseT start {0, 0};
    PoseT goal {4, 4};
    map[1][1] = '.';
    map[1][2] = '.';
    map[1][3] = '.';
    map[2][1] = '.';
    map[2][2] = '.';
    map[2][3] = '.';
    map[3][1] = '.';
    map[3][2] = '.';
    map[3][3] = '.';
    PathFinder::printMap(map);
    auto path = bfs.planPath(start, goal);
    ASSERT_TRUE(path);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
