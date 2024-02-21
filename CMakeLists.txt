cmake_minimum_required(VERSION 3.10)
project(multi_robot_simulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
# set(CMAKE_BUILD_TYPE Debug)
include_directories(${GOOGLETEST_INCLUDE_DIR})

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

include_directories(include)

set(SOURCES
    src/core/simulator.cpp
    src/core/window.cpp
    src/core/map.cpp
    src/core/grid.cpp
    src/core/button.cpp
    src/core/agent.cpp
    src/main.cpp
)

add_executable(multi_robot_simulator ${SOURCES})
target_link_libraries(multi_robot_simulator sfml-graphics)

# add_executable(path_finder_node src/path_finder/path_finder_node.cpp)

# add_executable(BFSTest
#     test/path_finder/bfs_test.cpp
# )
# target_link_libraries(BFSTest gtest gtest_main gmock gmock_main)

# enable_testing()
# include(GoogleTest)
# gtest_discover_tests(BFSTest)