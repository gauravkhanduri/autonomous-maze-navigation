#include <iostream>
#include <string>

#include "maze_navigation.hpp"



using MMS = micro_mouse::MazeControlAPI;

int main() {
    micro_mouse::DFSAlgorithm dfs;
    micro_mouse::Robot robot(dfs);
    robot.run();
}