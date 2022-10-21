cmake_minimum_required(VERSION 3.10)
project(multi_robot_simulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

include_directories(include)

add_executable(multi_robot_simulator src/simulator/simulator.cpp src/main.cpp)
target_link_libraries(multi_robot_simulator sfml-graphics)