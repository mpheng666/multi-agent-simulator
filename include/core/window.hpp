#ifndef MAS_CORE__WINDOW_HPP_
#define MAS_CORE__WINDOW_HPP_

#include <SFML/Graphics.hpp>
#include <core/button.hpp>
#include <core/map.hpp>
#include <iostream>
namespace mas
{
    struct WindowConfig
    {
        unsigned int width {};
        unsigned int height {};
        std::string name {};
    };

    class Window
    {
        public:
        Window(const WindowConfig& window_config, const Map& map);
        ~Window() = default;
        void run();

        Map& getMap() { return map_; }
        sf::RenderWindow& getRenderWindow() { return rwindow_; }
        std::vector<sf::Drawable> drawables_;
        void drawMap();

        private:
        WindowConfig window_config_;
        sf::RenderWindow rwindow_;
        Button clear_map_button_;

        Map map_;
        void init();
        void processEvents();
        void renderGraphics();
        bool isMouseOnMap(const sf::Vector2i& mouse_pos);
    };
}  // namespace mas

#endif