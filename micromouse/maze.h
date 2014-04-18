/*
 * Direction selection module
 *
 * This module is responsible for deciding which direction to move in and moving
 * the mouse in the appropriate direction.
 */
#ifndef __MAZE_H_
#define __MAZE_H_

const int MAZE_SIZE = 16;
const int NORTH = 0;
const int EAST = 1;
const int SOUTH = 2;
const int WEST = 3;

struct coord {
  int x;
  int y;

  coord(int x, int y) {
    this->x = x;
    this->y = y;
  }

  coord() {
  }
};

extern int cur_x;
extern int cur_y;
extern unsigned char maze[MAZE_SIZE][MAZE_SIZE];
extern int facing;

void initMaze();
void makeMove();
void switchDestinationToCenter();
void switchDestinationToCorner();

#endif // __MAZE_H_
