#ifndef MAS_CORE__SIMULATOR_HPP_
#define MAS_CORE__SIMULATOR_HPP_

#include "core/window.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "core/agent.hpp"

namespace mas
{
    class Simulator
    {
        public:
        Simulator(Window& window, std::vector<Agent>& agents);
        void run();

        private:
        Window& window_;
        std::vector<Agent>& agents_;
    };
}  // namespace mas

#endif