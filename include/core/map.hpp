#ifndef MAS_CORE_MAP_HPP_
#define MAS_CORE_MAP_HPP_

#include "core/grid.hpp"
#include <iostream>
#include <vector>

namespace mas {
    class Map {
    public:
        Map(const unsigned int width,
            const unsigned int height,
            const unsigned int col,
            const unsigned int row,
            const float offset_x,
            const float offset_y,
            sf::RenderWindow& rw)
            : width_(width)
            , height_(height)
            , col_num_(col)
            , row_num_(row)
            , offset_x_(offset_x)
            , offset_y_(offset_y)
            , rw_(rw)
        {
            step_size_ = width_ / col_num_;
            origin_x_ = width_ / 2.0f;
            origin_y_ = height_ / 2.0f;
            grids_.resize(col_num_, std::vector<Grid>(row_num_));
            initializeMap();
        }

        std::size_t getColumnSize() const { return grids_.size(); }

        std::size_t getRowSize() const { return grids_.front().size(); }

        void renderMap()
        {
            for (auto i = 0; i < col_num_; ++i) {
                for (auto j = 0; j < row_num_; ++j) {
                    float position_x = -origin_x_ + offset_x_ + i * step_size_;
                    float position_y = -origin_y_ + offset_y_ + j * step_size_;
                    grids_.at(i).at(j).setPosition(position_x, position_y);
                    grids_.at(i).at(j).setFillColor(sf::Color::White);
                    rw_.draw(grids_.at(i).at(j));
                }
            }
        }

        void initializeMap()
        {
            for (auto i = 0; i < col_num_; ++i) {
                for (auto j = 0; j < row_num_; ++j) {
                    float position_x = -origin_x_ + offset_x_ + i * step_size_;
                    float position_y = -origin_y_ + offset_y_ + j * step_size_;
                    grids_.at(i).at(j).setSize(sf::Vector2f(step_size_, step_size_));
                    grids_.at(i).at(j).setFillColor(sf::Color::White);
                    grids_.at(i).at(j).setOutlineColor(sf::Color::Black);
                    grids_.at(i).at(j).setOutlineThickness(1.0f);
                    grids_.at(i).at(j).setPosition(position_x, position_y);
                    rw_.draw(grids_.at(i).at(j));
                }
            }
        }

    private:
        unsigned int width_{10};
        unsigned int height_{10};
        unsigned int col_num_{1};
        unsigned int row_num_{1};
        unsigned int step_size_{10};
        float offset_x_{0.0f};
        float offset_y_{0.0f};
        float origin_x_{5};
        float origin_y_{5};

        sf::RenderWindow& rw_;

        std::vector<std::vector<Grid>> grids_{};
    };
} // namespace mas

#endif