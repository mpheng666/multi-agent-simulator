#ifndef MAS_CORE__WINDOW_HPP_
#define MAS_CORE__WINDOW_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
namespace mas
{
    struct WindowConfig
    {
        unsigned int width {};
        unsigned int height {};
        std::string name {};
    };

}  // namespace mas

#endif