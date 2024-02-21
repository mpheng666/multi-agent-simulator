#include "core/simulator.hpp"

namespace mas
{

    Simulator::Simulator(Window& window, std::vector<Agent>& agents)
        : window_(window)
        , agents_(agents)
    {
    }

    void Simulator::run()
    {
        while (window_.getRenderWindow().isOpen())
        {
            window_.drawMap();
            for (auto& agent : agents_)
            {
                agent.draw(window_.getRenderWindow());
            }
            window_.run();
        }
    }
}  // namespace mas