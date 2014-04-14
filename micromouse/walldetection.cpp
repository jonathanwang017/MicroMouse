/*
 * Wall Detection Module
 *
 * This module is used by the wall module. It operates the IR sensor, looking for
 * walls around us.
 */
#include "walldetection.h"

#ifndef GROUND_TEST
// TODO
#else // GROUND_TEST

#include "maze.h"

char realWalls[MAZE_SIZE][MAZE_SIZE] = {0};

//check if there is a wall in front of mouse
bool checkWall() {
  return realWalls[cur_x][cur_y] & (1 << facing);
}

#endif
