#include "simulator/simulator.hpp"

int main(int argc, char** argv)
{
    std::string window_name = "Mutli-Agent-Simulator";
    int height = 600;
    int width = 1000;

    mas::Simulator simulator(width, height, window_name, 60);
    simulator.run();

    return 0;
}