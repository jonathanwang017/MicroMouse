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

extern unsigned char path_x[MAZE_SIZE * MAZE_SIZE];
extern unsigned char path_y[MAZE_SIZE * MAZE_SIZE];
extern int pathLength;
extern int cur_x;
extern int cur_y;
extern unsigned char maze[MAZE_SIZE][MAZE_SIZE];
extern int facing;

void initGrid();
void makeMove();

#endif // __MAZE_H_
