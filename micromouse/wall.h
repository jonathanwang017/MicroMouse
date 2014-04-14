/*
 * Wall Module
 *
 * This module is in charge of remembering where there are walls, and initiating
 * detection of previously unknown walls.
 */
#ifndef __WALL_H_
#define __WALL_H_

#include "maze.h"

extern char walls[MAZE_SIZE][MAZE_SIZE];

void initMazeBorder();
void addWall(int x, int y, int dir);
bool hasKnownWall(int x, int y, int dir);
bool hasUnknownWallAhead();

#endif // __WALL_H_
