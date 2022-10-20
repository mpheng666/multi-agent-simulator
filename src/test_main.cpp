#include <SFML/Graphics.hpp>
#include "grid.hpp"

int main() {
    srand(time(0));
    int height = 600;
    int width = 600;
    int num_row = 10;
    int num_col = 10;
    double scale_for_line = 0.9;
    double scale_for_offset = (1 - scale_for_line) / 2;

    sf::RenderWindow window(sf::VideoMode(width, height),
                            "Mutli-Agent-Simulator",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    int grid_w = width / num_col;
    int grid_h = height / num_row;

    sf::Texture blue_texture;
    blue_texture.loadFromFile("../images/rainbow_square.png");
    sf::Sprite sprite_blue(blue_texture);

    sf::Texture texture_agent;
    texture_agent.loadFromFile("../images/agent_lizard.png");
    sf::Sprite sprite_agent(texture_agent);
    auto agent_size = texture_agent.getSize();
    double agent_scale_w = grid_w / agent_size.x;
    double agent_scale_h = grid_h / agent_size.y;
    sprite_agent.scale(agent_scale_w, agent_scale_h);

    while (window.isOpen()) {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        // int x = pos.x / w;
        // int y = pos.y / w;

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == sf::Mouse::Left)
                {
                    // sgrid[x][y] = grid[x][y];
                }
                else if (event.key.code == sf::Mouse::Right)
                {
                    // sgrid[x][y] = 11;
                }
            }
        }

        window.clear(sf::Color::Black);

        for (int i = 0; i <= num_col; i++) {
            for (int j = 0; j <= num_row; j++) {
                sprite_blue.setTextureRect(sf::IntRect(
                        i * grid_w, j * grid_h, grid_w * scale_for_line,
                        grid_h * scale_for_line));

                sprite_blue.setPosition(i * grid_w + scale_for_offset * grid_w,
                                        j * grid_h + scale_for_offset * grid_h);

                window.draw(sprite_blue);
            }
        }

        sprite_agent.setTextureRect(sf::IntRect(0, 0,
                                                agent_size.x * scale_for_line,
                                                agent_size.y * scale_for_line));
        sprite_agent.setPosition(scale_for_offset * grid_w,
                                 scale_for_offset * grid_h);

        window.draw(sprite_agent);

        window.display();
    }

    return 0;
}