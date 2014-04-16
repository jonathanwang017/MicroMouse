/*
 * Wall Module
 *
 * This module is in charge of remembering where there are walls, and initiating
 * detection of previously unknown walls.
 */
#ifndef __WALL_H_
#define __WALL_H_

#include "maze.h" // MAZE_SIZE

extern char walls[MAZE_SIZE][MAZE_SIZE];

void initMazeBorder();
bool hasKnownWall(int x, int y, int dir);
bool knownNotWall(int x, int y, int dir);
bool hasWallAhead();

#endif // __WALL_H_
