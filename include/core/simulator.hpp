#ifndef MAS_CORE__SIMULATOR_HPP_
#define MAS_CORE__SIMULATOR_HPP_

#include "core/agent.hpp"
#include "core/button.hpp"
#include "core/map.hpp"
#include "core/path_finder.hpp"
#include "core/window.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace mas
{
    class Simulator
    {
        public:
        Simulator(WindowConfig& window_config,
                  Map& map,
                  std::vector<Agent>& agents,
                  IPathFinder& path_finder);
        void run();

        private:
        WindowConfig window_config_;
        sf::RenderWindow rwindow_;
        Map& map_;
        std::vector<Agent>& agents_;
        std::vector<Button> buttons_;
        sf::Font font_;
        IPathFinder& path_finder_;

        void init();
        void drawMap();
        void processEvents();
        bool isMouseOnMap(const sf::Vector2i& mouse_pos);
        void findPath(const sf::Vector2i& start = {0, 0},
                      const sf::Vector2i& goal  = {10, 10});
    };
}  // namespace mas

#endif