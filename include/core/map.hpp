#ifndef MAS_CORE_MAP_HPP_
#define MAS_CORE_MAP_HPP_

#include "core/grid.hpp"
#include <iostream>
#include <random>
#include <set>
#include <vector>

namespace mas {
    class Map {
    public:
        Map(sf::RenderWindow& rw)
            : rw_(rw)
        {
            initialiseMap();
        }

        Map(const unsigned int width,
            const unsigned int height,
            const unsigned int step_size,
            const float offset_x,
            const float offset_y,
            sf::RenderWindow& rw)
            : width_(width)
            , height_(height)
            , step_size_(step_size)
            , offset_x_(offset_x)
            , offset_y_(offset_y)
            , rw_(rw)

        {
            initialiseMap();
        }

        std::size_t getColumnSize() const { return col_num_; }
        std::size_t getRowSize() const { return row_num_; }
        float getStepSize() const { return step_size_; }

        void renderMap()
        {
            for (auto i = 0; i < col_num_; ++i) {
                for (auto j = 0; j < row_num_; ++j) {
                    float position_x = -origin_x_ + offset_x_ + i * step_size_;
                    float position_y = -origin_y_ + offset_y_ + j * step_size_;
                    rw_.draw(grids_.at(i).at(j));
                }
            }
        }

        void initialiseMap()
        {
            col_num_ = width_ / step_size_;
            row_num_ = height_ / step_size_;
            origin_x_ = width_ / 2.0f;
            origin_y_ = height_ / 2.0f;
            grids_.resize(col_num_, std::vector<Grid>(row_num_));
            obstacles_.clear();
            for (unsigned int i = 0; i < col_num_; ++i) {
                for (unsigned int j = 0; j < row_num_; ++j) {
                    grids_.at(i).at(j).index_ = {i, j};
                    grids_.at(i).at(j).space_state_ = SpaceState::EMPTY;
                    float position_x = -origin_x_ + offset_x_ + i * step_size_;
                    float position_y = -origin_y_ + offset_y_ + j * step_size_;
                    grids_.at(i).at(j).setPosition(position_x, position_y);
                    grids_.at(i).at(j).setSize(sf::Vector2f(step_size_, step_size_));
                    grids_.at(i).at(j).setFillColor(sf::Color::White);
                    grids_.at(i).at(j).setOutlineColor(sf::Color::Black);
                    grids_.at(i).at(j).setOutlineThickness(1.0f);
                }
            }
        }

        void spawnObstacles(const unsigned int num)
        {
            std::random_device rd;
            std::uniform_int_distribution<unsigned int> d_col(1, col_num_ - 1);
            std::uniform_int_distribution<unsigned int> d_row(1, row_num_ - 1);
            for (int i = 0; i < num; ++i) {
                unsigned int obstacle_x = d_col(rd);
                unsigned int obstacle_y = d_row(rd);
                grids_.at(obstacle_x).at(obstacle_y).space_state_ = SpaceState::OCCUPIED;
                grids_.at(obstacle_x).at(obstacle_y).setFillColor(sf::Color::Red);
                obstacles_.insert({obstacle_x, obstacle_y});
            }
            for (const auto& obstacle : obstacles_) {
                std::cout << "obstacle: " << obstacle.front() << "," << obstacle.back()
                          << " ";
            }
            std::cout << "\n";
        }

        std::set<Index> getObstacles() const { return obstacles_; }

        void addObstacle(const Index& new_obstacle) { obstacles_.insert(new_obstacle); }

        void addObstacles(const std::set<Index>& new_obstacles)
        {
            for (const auto& obstacle : new_obstacles) {
                addObstacle(obstacle);
            }
        }

    private:
        unsigned int width_{10};
        unsigned int height_{10};
        unsigned int step_size_{10};
        unsigned int col_num_{width_ / step_size_};
        unsigned int row_num_{height_ / step_size_};
        float offset_x_{0.0f};
        float offset_y_{0.0f};
        float origin_x_{width_ / 2.0f};
        float origin_y_{height_ / 2.0f};

        sf::RenderWindow& rw_;

        std::vector<std::vector<Grid>> grids_{};
        // Index empty_index{};
        std::set<Index> obstacles_;
    };
} // namespace mas

#endif