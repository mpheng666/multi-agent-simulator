#include "core/window.hpp"

namespace mas
{
    Window::Window(const WindowConfig& window_config, const Map& map)
        : window_config_(window_config)
        , map_(map)
    {
        init();
    }

    void Window::init()
    {
        rwindow_.create(sf::VideoMode(window_config_.width, window_config_.height),
                        window_config_.name,
                        sf::Style::Close | sf::Style::Titlebar);
        rwindow_.setFramerateLimit(60);
        clear_map_button_.shape_.setSize(
            {static_cast<float>(window_config_.width - map_.getMapConfig().col_num *
                                                           map_.getMapConfig().grid_size),
             50.0f});
        clear_map_button_.shape_.setFillColor(sf::Color::Red);
        clear_map_button_.shape_.setPosition(
            static_cast<float>(map_.getMapConfig().col_num *
                               map_.getMapConfig().grid_size),
            0.0f);

        // clear_map_button_.text_.setFont(sf::Font::getDefaultFont());
        clear_map_button_.text_.setString("Clear Map");
        clear_map_button_.text_.setCharacterSize(24);
        clear_map_button_.text_.setFillColor(sf::Color::White);
        clear_map_button_.text_.setPosition(clear_map_button_.shape_.getPosition().x + 10,
                                            clear_map_button_.shape_.getPosition().y +
                                                10);
    }

    void Window::run()
    {
        processEvents();
        renderGraphics();
    }

    void Window::processEvents()
    {
        sf::Event event;
        while (rwindow_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                rwindow_.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                auto mouse_pos = sf::Mouse::getPosition(rwindow_);
                if (clear_map_button_.isMouseOnButton(mouse_pos))
                {
                    map_.clearObstacles();
                }
                if (isMouseOnMap(mouse_pos))
                {
                    auto grid_pos = map_.getGridIndex({mouse_pos.x, mouse_pos.y});
                    map_.addObstacle({grid_pos.x, grid_pos.y});
                }
            }
        }
    }

    void Window::renderGraphics()
    {
        clear_map_button_.draw(rwindow_);
        rwindow_.display();
        rwindow_.clear(sf::Color::Black);
    }

    void Window::drawMap()
    {
        for (size_t i = 0; i < map_.getGrids().size(); ++i)
        {
            for (size_t j = 0; j < map_.getGrids()[i].size(); ++j)
            {
                rwindow_.draw(map_.getGrids()[i][j]);
            }
        }
    }

    bool Window::isMouseOnMap(const sf::Vector2i& mouse_pos)
    {
        const auto map_config = map_.getMapConfig();
        return mouse_pos.x >= 0 &&
               mouse_pos.x < map_config.col_num * map_config.grid_size &&
               mouse_pos.y >= 0 &&
               mouse_pos.y < map_config.row_num * map_config.grid_size;
    }

}  // namespace mas