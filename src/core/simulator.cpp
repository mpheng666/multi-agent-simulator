#include "core/simulator.hpp"

namespace mas
{

    Simulator::Simulator(WindowConfig& window_config,
                         Map& map,
                         std::vector<Agent>& agents,
                         IPathFinder& path_finder)
        : window_config_(window_config)
        , map_(map)
        , agents_(agents)
        , path_finder_(path_finder)
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
        Button run_button;
        Button stop_button;
        Button clear_path_button;

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

        run_button.shape_.setSize(
            {static_cast<float>(window_config_.width - map_.getMapConfig().col_num *
                                                           map_.getMapConfig().grid_size),
             50.0f});
        run_button.shape_.setFillColor(sf::Color::Green);
        run_button.shape_.setPosition(static_cast<float>(map_.getMapConfig().col_num *
                                                         map_.getMapConfig().grid_size),
                                      100.0f);

        run_button.text_.setFont(font_);
        run_button.text_.setString("Run");
        run_button.text_.setCharacterSize(16);
        run_button.text_.setFillColor(sf::Color::Black);
        run_button.text_.setPosition(run_button.shape_.getPosition().x + 10,
                                     run_button.shape_.getPosition().y + 10);

        stop_button.shape_.setSize(
            {static_cast<float>(window_config_.width - map_.getMapConfig().col_num *
                                                           map_.getMapConfig().grid_size),
             50.0f});
        stop_button.shape_.setFillColor(sf::Color::Blue);
        stop_button.shape_.setPosition(static_cast<float>(map_.getMapConfig().col_num *
                                                          map_.getMapConfig().grid_size),
                                       150.0f);

        stop_button.text_.setFont(font_);
        stop_button.text_.setString("Stop");
        stop_button.text_.setCharacterSize(16);
        stop_button.text_.setFillColor(sf::Color::White);
        stop_button.text_.setPosition(stop_button.shape_.getPosition().x + 10,
                                      stop_button.shape_.getPosition().y + 10);

        clear_path_button.shape_.setSize(
            {static_cast<float>(window_config_.width - map_.getMapConfig().col_num *
                                                           map_.getMapConfig().grid_size),
             50.0f});
        clear_path_button.shape_.setFillColor(sf::Color::Magenta);
        clear_path_button.shape_.setPosition(
            static_cast<float>(map_.getMapConfig().col_num *
                               map_.getMapConfig().grid_size),
            200.0f);

        clear_path_button.text_.setFont(font_);
        clear_path_button.text_.setString("Clear Path");
        clear_path_button.text_.setCharacterSize(16);
        clear_path_button.text_.setFillColor(sf::Color::White);
        clear_path_button.text_.setPosition(clear_path_button.shape_.getPosition().x + 10,
                                            clear_path_button.shape_.getPosition().y +
                                                10);

        clear_map_button.setOnClick([this]() { map_.clearObstacles(); });
        random_obstacles_button.setOnClick([this]() { map_.addRandomObstacles(50); });
        run_button.setOnClick(
            [this]()
            {
                std::cout << "Run" << std::endl;
                map_.clearPath();
                findPath();
            });
        stop_button.setOnClick([this]() { std::cout << "Stop" << std::endl; });
        clear_path_button.setOnClick(
            [this]()
            {
                std::cout << "Clear Path" << std::endl;
                map_.clearPath();
            });

        buttons_.push_back(clear_map_button);
        buttons_.push_back(random_obstacles_button);
        buttons_.push_back(run_button);
        buttons_.push_back(stop_button);
        buttons_.push_back(clear_path_button);
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
                    auto grid_idx = map_.getGridIndex({mouse_pos.x, mouse_pos.y});
                    if (map_.isGridObstacle(grid_idx))
                    {
                        map_.clearObstacle(grid_idx);
                    }
                    else
                    {
                        map_.addObstacle(grid_idx);
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    for (auto& agent : agents_)
                    {
                        agent.move(MoveDirection::UP);
                    }
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    for (auto& agent : agents_)
                    {
                        agent.move(MoveDirection::DOWN);
                    }
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    for (auto& agent : agents_)
                    {
                        agent.move(MoveDirection::LEFT);
                    }
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    for (auto& agent : agents_)
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

    void Simulator::findPath(const sf::Vector2i& start, const sf::Vector2i& goal)
    {
        // map_.getGrids()[start.y][start.x].setType(GridType::START);
        // path_finder_.direction_type = IPathFinder::DIRECTIONS::FOUR;

        map_.getGrids()[goal.y][goal.x].setType(GridType::GOAL);
        auto agent_pos = agents_[0].getPosition();
        auto start_idx = map_.getGridIndex({static_cast<int>(agent_pos.x),
                                           static_cast<int>(agent_pos.y)});
        auto path = path_finder_.findPath(map_, start_idx, goal);
        for (const auto& grid : path)
        {
            std::cout << grid.x << " " << grid.y << std::endl;
            if (map_.getGrids()[grid.y][grid.x].getType() != GridType::START &&
                map_.getGrids()[grid.y][grid.x].getType() != GridType::GOAL)
            {
                map_.getGrids()[grid.y][grid.x].setType(GridType::PATH);
            }
        }
    }

}  // namespace mas