#include "simulator.hpp"

using namespace mas_simulator;

Simulator::Simulator()
{

}

Simulator::~Simulator()
{

}

void Simulator::run() {

    while (window_.isOpen()) {
        sf::Vector2i pos = sf::Mouse::getPosition(window_);

        sf::Event event;
        while (window_.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window_.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == sf::Mouse::Left) {
                    // sgrid[x][y] = grid[x][y];
                }
                else if (event.key.code == sf::Mouse::Right) {
                    // sgrid[x][y] = 11;
                }
            }
        }

        window_.clear(sf::Color::Black);

        window_.display();
    }
}

void Simulator::update()
{

}

void Simulator::render()
{
    
}