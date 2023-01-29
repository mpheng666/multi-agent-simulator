#ifndef MAS_SIMULATOR_HPP_
#define MAS_SIMULATOR_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "core/agent.hpp"
#include "core/object.hpp"

// #include "path_finding/dfs.hpp"
#include "core/map.hpp"
#include "core/time.hpp"

namespace mas {
    class Simulator {
    public:
        Simulator(const int window_width,
                  const int window_height,
                  const std::string& window_name,
                  const int window_framerate_limit);
        void run();

    private:
        sf::RenderWindow rwindow_;
        Map map_;

        Agent agent_;

        TimeHandler time_handler{60.0};

        void processEvents();
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    };
} // namespace mas

#endif