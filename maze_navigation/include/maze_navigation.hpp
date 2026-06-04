
#include "maze_api.hpp"
#include <vector>
#include <array>
#include <stack>




namespace micro_mouse
{

class Maze
{
    int width_;
    int height_;
    int robot_x_;
    int robot_y_;
    int robot_heading_;
    

    std::vector<bool> walls_;
    std::vector<bool> visited_;
    std::array<int, 4> goal_cells_;

public:

    Maze(); //: width_{MazeControlAPI::get_maze_width()}, height_{MazeControlAPI::get_maze_height()}, walls_(width_ * height_ * 4, false), visited_(width_ * height_, false) {}

    bool has_wall_front();
    bool has_wall_right();
    bool has_wall_left();
    
    void move_forward();
    void turn_left();
    void turn_right();


    int get_maze_width();
    int get_maze_height();

    int get_x();
    int get_y();
    int get_heading();

  


    bool is_at_goal();
    void set_goal();

    void set_wall(int x, int y, char direction);
    bool has_wall(int x, int y, int direction);

    void mark_visited(int x, int y);

    bool is_visited(int x, int y);
    

};

class Algorithm
{
   
public:
    
    virtual void solve(Maze& maze) = 0;

};

//DFS algorithm

class DFSAlgorithm : public Algorithm
{
private:

    std::stack<std::pair<int,int>> stk_;

public:
    void solve(Maze& maze) override;
};

class Robot
{
private:
    Maze maze;
    Algorithm& algo_;

public:

    Robot(Algorithm& algo_);

    void run();

};

}