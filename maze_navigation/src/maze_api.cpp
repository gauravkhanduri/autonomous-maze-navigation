#include "maze_api.hpp"

#include <cstdlib>
#include <iostream>

int micro_mouse::MazeControlAPI::get_maze_width() {
    std::cout << "mazeWidth" << std::endl;
    std::string response;
    std::cin >> response;
    return atoi(response.c_str());
}

int micro_mouse::MazeControlAPI::get_maze_height() {
    std::cout << "mazeHeight" << std::endl;
    std::string response;
    std::cin >> response;
    return atoi(response.c_str());
}

bool micro_mouse::MazeControlAPI::has_wall_front() {
    std::cout << "wallFront" << std::endl;
    std::string response;
    std::cin >> response;
    return response == "true";
}

bool micro_mouse::MazeControlAPI::has_wall_right() {
    std::cout << "wallRight" << std::endl;
    std::string response;
    std::cin >> response;
    return response == "true";
}

bool micro_mouse::MazeControlAPI::has_wall_left() {
    std::cout << "wallLeft" << std::endl;
    std::string response;
    std::cin >> response;
    return response == "true";
}

void micro_mouse::MazeControlAPI::move_forward(int distance) {
    std::cout << "moveForward ";
    // Don't print distance argument unless explicitly specified, for
    // backwards compatibility with older versions of the simulator
    if (distance != 1) {
        std::cout << distance;
    }
    std::cout << std::endl;
    std::string response;
    std::cin >> response;
    if (response != "ack") {
        std::cerr << response << std::endl;
        throw;
    }
}

void micro_mouse::MazeControlAPI::turn_right() {
    std::cout << "turnRight" << std::endl;
    std::string ack;
    std::cin >> ack;
}

void micro_mouse::MazeControlAPI::turn_left() {
    std::cout << "turnLeft" << std::endl;
    std::string ack;
    std::cin >> ack;
}

void micro_mouse::MazeControlAPI::set_wall(int x, int y, char direction) {
    std::cout << "setWall " << x << " " << y << " " << direction << std::endl;
}

void micro_mouse::MazeControlAPI::clear_wall(int x, int y, char direction) {
    std::cout << "clearWall " << x << " " << y << " " << direction << std::endl;
}

void micro_mouse::MazeControlAPI::set_color(int x, int y, char color) {
    std::cout << "setColor " << x << " " << y << " " << color << std::endl;
}

void micro_mouse::MazeControlAPI::clear_color(int x, int y) {
    std::cout << "clearColor " << x << " " << y << std::endl;
}

void micro_mouse::MazeControlAPI::clear_all_color() {
    std::cout << "clearAllColor" << std::endl;
}

void micro_mouse::MazeControlAPI::set_text(int x, int y, const std::string& text) {
    std::cout << "setText " << x << " " << y << " " << text << std::endl;
}

void micro_mouse::MazeControlAPI::clear_text(int x, int y) {
    std::cout << "clearText " << x << " " << y << std::endl;
}

void micro_mouse::MazeControlAPI::clear_all_text() {
    std::cout << "clearAllText" << std::endl;
}

bool micro_mouse::MazeControlAPI::was_reset() {
    std::cout << "wasReset" << std::endl;
    std::string response;
    std::cin >> response;
    return response == "true";
}

void micro_mouse::MazeControlAPI::ack_reset() {
    std::cout << "ackReset" << std::endl;
    std::string ack;
    std::cin >> ack;
}