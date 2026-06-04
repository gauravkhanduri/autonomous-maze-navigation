cmake_minimum_required(VERSION 3.22.1)
project(maze_navigation VERSION 1.0 LANGUAGES C CXX)

add_executable(maze_navigation src/main.cpp src/maze_navigation.cpp src/maze_api.cpp)

target_include_directories(maze_navigation PRIVATE include)

# Set C++17 standard for the targets
set_property(TARGET maze_navigation PROPERTY CXX_STANDARD 17)
set_property(TARGET maze_navigation PROPERTY CXX_STANDARD_REQUIRED ON)