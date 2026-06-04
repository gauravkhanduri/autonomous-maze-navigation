#include <iostream>
#include <string>
#include "maze_navigation.hpp"


using MMS = micro_mouse::MazeControlAPI;
using namespace std;



micro_mouse::Maze::Maze() : width_{MMS::get_maze_width()}, 
            height_{MMS::get_maze_height()}, walls_(width_ * height_ * 4, false), 
            visited_(width_ * height_, false), goal_cells_{-1, -1, -1, -1}, robot_x_{0}, robot_y_{0}, robot_heading_{0}
{

    set_goal();
     

            
}


void micro_mouse::Maze::set_goal()
{
    /** for reference  MMS::set_text(7, 7, "(7,7)");
  MMS::set_text(7, 8, "(7,8)");
  MMS::set_text(8, 7, "(8,7)");
  MMS::set_text(8, 8, "(8,8)"); */

//   goal_cells_[0] = 119;
//   goal_cells_[1] = 120;
//   goal_cells_[2] = 135;
//   goal_cells_[3] = 136;

    goal_cells_[0] = (height_/2 - 1 ) * width_ + (width_/2 -1);
    goal_cells_[1] = (height_/2 - 1 ) * width_ + (width_/2);
    goal_cells_[2] = (height_/2) * width_ + (width_/2 -1);
    goal_cells_[3] = (height_/2) * width_ + (width_/2);

}

bool micro_mouse::Maze::is_at_goal()
{
    int current_cell_idx = (robot_y_ * width_) + robot_x_;

   for (int g : goal_cells_)
   {
        if(current_cell_idx == g) return true;
   }
   return false;

}

void micro_mouse::Maze::move_forward()
{
    //static const local array, initialized once, live for  the program lifetime.
    
    static const int dx[4] = {0,1,0,-1}; // N, E, S, W
    static const int dy[4] = {1, 0, -1, 0}; // N, E, S, W

    MMS::move_forward(); // calls move_forward api

    robot_x_ +=dx[robot_heading_]; // current heading is zero
    robot_y_ +=dy[robot_heading_];


}

void micro_mouse::Maze::turn_left()
{
    //if facing north , turn left would be heading in west direction 
    MMS::turn_left();
    robot_heading_  =  (robot_heading_ + 3)% 4; //robot_heading_ = (robot_heading_ + 3) % 4;

}
void micro_mouse::Maze::turn_right()
{
    MMS::turn_right();
    robot_heading_  = (robot_heading_ + 1) % 4;

}


bool micro_mouse::Maze::has_wall_front()
{
   bool wall = MMS::has_wall_front();
    walls_[(robot_y_ * width_ + robot_x_)  * 4 + robot_heading_] = wall; //walls_is vectors index will have true or false, so if next time robot will reach there it will know that index has the bool value true/false
    return wall;
   
}
bool micro_mouse::Maze::has_wall_left()
{
    bool wall = MMS::has_wall_left();
    walls_[(robot_y_ * width_ + robot_x_) * 4 + ((robot_heading_ + 3) % 4) ] = wall;
    return wall;


    
}
bool micro_mouse::Maze::has_wall_right()
{
    bool wall = MMS::has_wall_right();
    walls_[(robot_y_ * width_ + robot_x_) * 4 + ((robot_heading_ + 1) % 4)] = wall;
    return wall;

}
void micro_mouse::Maze::set_wall(int x, int y, char direction)
{

    int idx = -1;
   switch (direction)
   {
    case 'n':
        idx = (y * width_ + x) * 4 + 0;
        break;
    case 'e':
        idx = (y * width_ + x) * 4 + 1;
        break;
    case 's':
        idx = (y * width_ + x) * 4 + 2;
        break;
    case 'w':
        idx = (y * width_ + x) * 4 + 3;
        break;
    default:
        cerr << "Invalid direction: " << direction << endl;
        return;
   }

  walls_[idx] = true;   
  MMS::set_wall(x, y, direction); // call api to set wall in simulator

}
bool micro_mouse::Maze::has_wall(int x, int y, int direction)
{
   return walls_[(y * width_ + x) * 4 + direction];


}
int micro_mouse::Maze::get_x()
{
    return robot_x_;
}
int micro_mouse::Maze::get_y()
{
    return robot_y_;
}
int micro_mouse::Maze::get_heading()
{
    return robot_heading_;
}
int micro_mouse::Maze::get_maze_width()
{
    return width_;
}
int micro_mouse::Maze::get_maze_height()
{
    return height_;
}

void micro_mouse::Maze::mark_visited(int x, int y)
{
     visited_[y * width_ + x] = true;
}
bool micro_mouse::Maze::is_visited(int x, int y)
{
    return visited_[y * width_ + x];


}

//Robot class construction and initialisation of algo class as a reference. 
micro_mouse::Robot::Robot(Algorithm& algo) : algo_(algo)
{
    
}

void micro_mouse::Robot::run()
{
    algo_.solve(maze);
}

void micro_mouse::DFSAlgorithm::solve(micro_mouse::Maze& maze)
{   
    
   int x = maze.get_x();
   int y = maze.get_y();
   int heading = maze.get_heading();

    static const int dx[4] = {0,1,0,-1}; // N, E, S, W
    static const int dy[4] = {1, 0, -1, 0}; // N, E, S, W

   int idx = y * maze.get_maze_width() + x;
   maze.mark_visited(x,y);
   stk_.push({idx,-1});
  

while(!stk_.empty() && !maze.is_at_goal())
{
   int next_dir = -1;
   int nx;
   int ny;
   x = maze.get_x();
   y = maze.get_y();

    maze.has_wall_front();
    maze.has_wall_left();
    maze.has_wall_right();

    for (int dir=0; dir < 4; dir++)
    {
        nx = x + dx[dir];   //0 + 0
        ny = y + dy[dir];   // 0 + 1 = 1

        if(!maze.has_wall(x,y,dir) && !maze.is_visited(nx,ny))
        {
            next_dir = dir;
            break;
        }
       
    }
     if(next_dir != -1)
        {
            int turns_needed = (next_dir - maze.get_heading() + 4) % 4;
            if(turns_needed==3)
            {
                maze.turn_left();
            }
            else if(turns_needed==1)
            {
                maze.turn_right();
            }
            else if(turns_needed==2)
            {
                maze.turn_right();
                maze.turn_right();
            }
        

            maze.move_forward();
            maze.mark_visited(nx,ny);
            int new_idx = ny * maze.get_maze_width() + nx;

            stk_.push({idx,next_dir});
        }

        else{
            
        }
    

    


}
   

}