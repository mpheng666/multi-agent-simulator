#include "core/simulator.hpp"

#include "path_finder/astar.hpp"
#include "path_finder/rrt.hpp"
#include "path_finder/bfs.hpp"

#include <chrono>
#include <iostream>
#include <thread>

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
        random_obstacles_button.setOnClick(
            [this]()
            {
                const size_t num_obstacles =
                    map_.getMapConfig().col_num * map_.getMapConfig().row_num / 5;
                map_.addRandomObstacles(num_obstacles);
            });
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
                    auto grid_idx = map_.getGridIndex({static_cast<float>(mouse_pos.x),
                                                       static_cast<float>(mouse_pos.y)});
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

    void Simulator::drawLines(const std::vector<sf::Vector2i>& path)
    {
        for (int i = 1; i < path.size() - 1; i++)
        {
            sf::Vertex line[] = {
                sf::Vertex(map_.getPosition(path[i - 1]), sf::Color::Red),
                sf::Vertex(map_.getPosition(path[i]), sf::Color::Red)};

            rwindow_.draw(line, 2, sf::Lines);
        }
    }

    void Simulator::findPath(const sf::Vector2i& start, const sf::Vector2i& goal)
    {
        // map_.getGrids()[start.y][start.x].setType(GridType::START);
        map_.getGrids()[goal.y][goal.x].setType(GridType::GOAL);
        auto agent_pos = agents_[0].getPosition();
        auto start_idx = map_.getGridIndex({agent_pos.x, agent_pos.y});
        try
        {
            // AStarPathFinder& path_finder = static_cast<AStarPathFinder&>(path_finder_);
            // RRTPathFinder& path_finder = static_cast<RRTPathFinder&>(path_finder_);
            BFS& path_finder = static_cast<BFS&>(path_finder_);
            const auto start_time      = std::chrono::high_resolution_clock::now();
            auto path                  = path_finder.findPath(map_, start_idx, goal);
            const auto end_time        = std::chrono::high_resolution_clock::now();
            std::cout << "Path finding time: "
                      << std::chrono::duration_cast<std::chrono::microseconds>(end_time -
                                                                               start_time)
                             .count()
                      << "us" << std::endl;

            const auto explored_nodes = path_finder.getExploredNodes();
            std::cout << "Explored nodes: " << explored_nodes.size() << std::endl;
            for (const auto& grid : explored_nodes)
            {
                // std::cout << grid.x << " " << grid.y << std::endl;
                if (map_.getGrids()[grid.y][grid.x].getType() != GridType::START &&
                    map_.getGrids()[grid.y][grid.x].getType() != GridType::GOAL)
                {
                    map_.getGrids()[grid.y][grid.x].setType(GridType::EXPLORED);
                }
            }
            std::cout << "Path length: " << path.size() << std::endl;
            for(const auto& p : path)
            {
                if(map_.getGrids()[p.y][p.x].getType() != GridType::START &&
                   map_.getGrids()[p.y][p.x].getType() != GridType::GOAL)
                {
                    map_.getGrids()[p.y][p.x].setType(GridType::PATH);
                }
            }
        }
        catch (const std::bad_cast& e)
        {
            std::cerr << "Failed to cast path_finder_ to AstarPathFinder: " << e.what()
                      << std::endl;
        }
    }

}  // namespace mas