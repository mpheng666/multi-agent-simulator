#ifndef MAS_SIMULATOR_HPP_
#define MAS_SIMULATOR_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "object/object_base.hpp"
#include "path_finding/dfs.hpp"
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
        mas_object::MASObject agent_;
        mas_dfs::MASDFS mas_path_finding_;
        float width_step_{0.0f};
        float height_step_{0.0f};

        void initialize_map();
        void initialize_objects(mas_object::MASObject& object);

        void processEvents();
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    };
} // namespace mas_simulator

#endif