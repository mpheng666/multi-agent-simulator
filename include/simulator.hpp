#ifndef MULTI_AGENT_SIMULATOR_SIMULATOR_HPP_
#define MULTI_AGENT_SIMULATOR_SIMULATOR_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace simulator {
class Simulator : private sf::NonCopyable {
public:
    Simulator();
    void run();
    void update();

private:
    void processEvents();
    void update(sf::Time elapsedTime);
    void render();

    void updateStatistics(sf::Time elapsedTime);
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    static const sf::Time TimePerFrame;

    sf::RenderWindow mWindow;
    World mWorld;

    sf::Font mFont;
    sf::Text mStatisticsText;
    sf::Time mStatisticsUpdateTime;
    std::size_t mStatisticsNumFrames;
};
} // namespace simulator

#endif