#include "simulator/simulator.hpp"

int main(int argc, char** argv)
{
    std::string window_name = "Mutli-Agent-Simulator";
    int height = 600;
    int width = 1000;
    int map_row = 120;
    int map_col = 200;

    mas_simulator::Simulator simulator(width, height, window_name, 60, map_col,
                                       map_row);
    simulator.run();

    return 0;
}