#include "simulator.hpp"

int main()
{
    srand(time(0));
    int height = 600;
    int width = 600;
    int num_row = 10;
    int num_col = 10;
    double scale_for_line = 0.9;
    double scale_for_offset = (1 - scale_for_line) / 2;

    sf::RenderWindow window(sf::VideoMode(width, height), "Mutli-Agent-Simulator",
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

    return 0;
}