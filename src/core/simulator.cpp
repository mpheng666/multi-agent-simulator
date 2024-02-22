#include "core/simulator.hpp"

namespace mas
{

    Simulator::Simulator(WindowConfig& window_config,
                         Map& map,
                         std::vector<Agent>& agents)
        : window_config_(window_config)
        , map_(map)
        , agents_(agents)
    {
        init();
    }

    void Simulator::init()
    {
        rwindow_.create(sf::VideoMode(window_config_.width, window_config_.height),
                        window_config_.name,
                        sf::Style::Close | sf::Style::Titlebar);
        rwindow_.setFramerateLimit(60);

        font_.loadFromFile("./../assets/fonts/arial.ttf");

        Button clear_map_button;
        Button random_obstacles_button;

        clear_map_button.shape_.setSize(
            {static_cast<float>(window_config_.width - map_.getMapConfig().col_num *
                                                           map_.getMapConfig().grid_size),
             50.0f});
        clear_map_button.shape_.setFillColor(sf::Color::Red);
        clear_map_button.shape_.setPosition(
            static_cast<float>(map_.getMapConfig().col_num *
                               map_.getMapConfig().grid_size),
            0.0f);

        clear_map_button.text_.setFont(font_);
        clear_map_button.text_.setString("Clear Map");
        clear_map_button.text_.setCharacterSize(16);
        clear_map_button.text_.setFillColor(sf::Color::White);
        clear_map_button.text_.setPosition(clear_map_button.shape_.getPosition().x + 10,
                                           clear_map_button.shape_.getPosition().y + 10);

        random_obstacles_button.shape_.setSize(
            {static_cast<float>(window_config_.width - map_.getMapConfig().col_num *
                                                           map_.getMapConfig().grid_size),
             50.0f});
        random_obstacles_button.shape_.setFillColor(sf::Color::Yellow);
        random_obstacles_button.shape_.setPosition(
            static_cast<float>(map_.getMapConfig().col_num *
                               map_.getMapConfig().grid_size),
            50.0f);

        random_obstacles_button.text_.setFont(font_);
        random_obstacles_button.text_.setString("Random Obstacles");
        random_obstacles_button.text_.setCharacterSize(16);
        random_obstacles_button.text_.setFillColor(sf::Color::Black);
        random_obstacles_button.text_.setPosition(
            random_obstacles_button.shape_.getPosition().x + 10,
            random_obstacles_button.shape_.getPosition().y + 10);

        clear_map_button.setOnClick([this]() { map_.clearObstacles(); });
        random_obstacles_button.setOnClick([this]() { map_.addRandomObstacles(50); });

        buttons_.push_back(clear_map_button);
        buttons_.push_back(random_obstacles_button);
    }

    void Simulator::run()
    {
        while (rwindow_.isOpen())
        {
            for (const auto& button : buttons_)
            {
                button.draw(rwindow_);
            }
            drawMap();
            processEvents();
            for (auto& agent : agents_)
            {
                agent.draw(rwindow_);
            }
            rwindow_.display();
            rwindow_.clear(sf::Color::Black);
        }
    }

    void Simulator::processEvents()
    {
        sf::Event event;
        while (rwindow_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                rwindow_.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                auto mouse_pos = sf::Mouse::getPosition(rwindow_);
                for (auto& button : buttons_)
                {
                    if (button.isMouseOnButton(mouse_pos))
                    {
                        if (button.onclick_ != nullptr)
                        {
                            button.onclick_();
                        }
                    }
                }
                if (isMouseOnMap(mouse_pos))
                {
                    auto grid_pos = map_.getGridIndex({mouse_pos.x, mouse_pos.y});
                    map_.addObstacle({grid_pos.x, grid_pos.y});
                }
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Up)
                {
                    for(auto& agent : agents_)
                    {
                        agent.move(MoveDirection::UP);
                    }
                }
                if(event.key.code == sf::Keyboard::Down)
                {
                    for(auto& agent : agents_)
                    {
                        agent.move(MoveDirection::DOWN);
                    }
                }
                if(event.key.code == sf::Keyboard::Left)
                {
                    for(auto& agent : agents_)
                    {
                        agent.move(MoveDirection::LEFT);
                    }
                }
                if(event.key.code == sf::Keyboard::Right)
                {
                    for(auto& agent : agents_)
                    {
                        agent.move(MoveDirection::RIGHT);
                    }
                }
            }
        }
    }

    bool Simulator::isMouseOnMap(const sf::Vector2i& mouse_pos)
    {
        const auto map_config = map_.getMapConfig();
        return mouse_pos.x >= 0 &&
               mouse_pos.x < map_config.col_num * map_config.grid_size &&
               mouse_pos.y >= 0 &&
               mouse_pos.y < map_config.row_num * map_config.grid_size;
    }

    void Simulator::drawMap()
    {
        for (size_t i = 0; i < map_.getGrids().size(); ++i)
        {
            for (size_t j = 0; j < map_.getGrids()[i].size(); ++j)
            {
                rwindow_.draw(map_.getGrids()[i][j]);
            }
        }
    }
    
}  // namespace mas