#ifndef MAS_SIMULATOR_HPP_
#define MAS_SIMULATOR_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "simulator/map.hpp"
#include <boost/range/adaptors.hpp>

namespace mas_simulator {
    class Simulator {
    public:
        Simulator(const int window_width,
                  const int window_height,
                  const std::string& window_name,
                  const int window_framerate_limit,
                  const int col,
                  const int row);
        void run();

    private:
        sf::RenderWindow rwindow_;
        mas_map::Map map_;
        float grid_w_{0.0f};
        float grid_h_{0.0f};

        void initialize_map_();

        void processEvents();
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    };
} // namespace mas_simulator

#endif