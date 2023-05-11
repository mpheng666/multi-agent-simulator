#include <chrono>
#include <iostream>
#include <random>
#include <stack>
#include <thread>
#include <tuple>
#include <vector>

static constexpr char OBSTACLE = '#';
static constexpr char SPACE    = ' ';
static constexpr char START    = 's';
static constexpr char GOAL     = 'g';
static constexpr char STEP     = '*';
static constexpr char VISITING = 'o';
static constexpr char PATH     = '$';

std::stack<std::pair<int, int>> found_path {};

std::vector<std::vector<char>> createMap(size_t row, size_t col)
{
    std::vector<std::vector<char>> map;
    map.resize(row, std::vector<char>(col));

    for (auto i = 0; i < row; ++i)
    {
        for (auto j = 0; j < col; ++j)
        {
            if (i == 0 || j == 0 || i == (row - 1) || j == (col - 1))
            {
                map.at(i).at(j) = OBSTACLE;
            }
            else
            {
                map.at(i).at(j) = SPACE;
            }
        }
    }
    map.at(1).at(1)             = START;
    map.at(row - 2).at(col - 2) = GOAL;
    for (auto i = 1; i < 5; ++i)
    {
        map.at(3).at(i) = OBSTACLE;
    }
    for (auto i = 3; i < col - 1; ++i)
    {
        map.at(row - 3).at(i) = OBSTACLE;
    }
    for (auto i = 4; i < 8; ++i)
    {
        map.at(5).at(i) = OBSTACLE;
    }
    for (auto i = 2; i < 8; ++i)
    {
        map.at(i).at(7) = OBSTACLE;
    }
    return map;
}

void printMap(std::vector<std::vector<char>>& map)
{
    std::cout << "  ";
    for (auto i = 0; i < map.front().size(); ++i)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
    for (auto i = 0; i < map.size(); ++i)
    {
        std::cout << i << " ";
        for (auto j = 0; j < map.front().size(); ++j)
        {
            std::cout << map.at(i).at(j) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool navigate(std::vector<std::vector<char>>& map, size_t row, size_t col)
{
    found_path.emplace(row, col);
    char previous_state = map.at(row).at(col);
    map.at(row).at(col) = VISITING;
    std::cout << "Visiting cell at row " << row << " col " << col << "\n";
    printMap(map);
    if (map.at(row).at(col) != SPACE)
    {
        map.at(row).at(col) = previous_state;
    }

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(200ms);

    if (row == map.size() - 1 || col == map.front().size() - 1 || row == 0 || col == 0)
    {
        std::cout << "WALL! \n";
        found_path.pop();
        return false;
    }
    if (map.at(row).at(col) == OBSTACLE)
    {
        std::cout << "OBSTACLE! \n";
        found_path.pop();
        return false;
    }
    if (map.at(row).at(col) == STEP)
    {
        std::cout << "VISITED! \n";
        found_path.pop();
        return false;
    }
    if (map.at(row).at(col) == GOAL)
    {
        std::cout << "GOAL! \n";
        map.at(row).at(col) = STEP;
        return true;
    }
    if (map.at(row).at(col) == SPACE)
    {
        std::cout << "SPACE! \n";
        map.at(row).at(col) = STEP;
    }

    // go right
    if ((col + 1) < map.front().size() && navigate(map, row, col + 1))
    {
        return true;
    }
    // go down
    if ((row + 1) < map.size() && navigate(map, row + 1, col))
    {
        return true;
    }
    // go left
    if ((col - 1) >= 0 && navigate(map, row, col - 1))
    {
        return true;
    }
    // go up
    if ((row - 1) >= 0 && navigate(map, row - 1, col))
    {
        return true;
    }
    found_path.pop();
    return false;
}

int main()
{
    auto map = createMap(10, 12);
    if (navigate(map, 1, 1))
    {
        while (!found_path.empty())
        {
            map.at(found_path.top().first).at(found_path.top().second) = PATH;
            printMap(map);
            found_path.pop();
        }
    }

    return 0;
}