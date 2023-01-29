#ifndef MAS_CORE_WINDOWS_HPP_
#define MAS_CORE_WINDOWS_HPP_

#include <string>
#include <SFML/Graphics.hpp>
#include <core/time.hpp>

namespace mas{
    class WindowsHandler{
        public:
            WindowsHandler(const unsigned int width, const unsigned int height, const std::string& name)
            {

            }

            unsigned int width_ {10};
            unsigned int height_ {10};
            std::string name_{"MAS"};

            unsigned int col_num {10};
            unsigned int row_num {10};
            unsigned int w_step_ {1};

        private:
            sf::RenderWindow rwindow_;
            mas::TimeHandler time_handler_{60.0};    

    };
}

#endif