#ifndef MAS_SIMULATOR_HPP_
#define MAS_SIMULATOR_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace mas_simulator {
    class Simulator {
    public:
        Simulator();
        void run();
        void update();

    private:
        void processEvents();

        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

        static const sf::Time TimePerFrame;

        sf::RenderWindow window_;
    };
} // namespace mas_simulator

#endif