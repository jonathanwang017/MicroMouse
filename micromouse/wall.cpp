/*
 * Wall Module
 *
 * This module is in charge of remembering where there are walls, and initiating
 * detection of previously unknown walls.
 */
#include "wall.h"
#include "maze.h"
#include "walldetection.h"

char walls[MAZE_SIZE][MAZE_SIZE] = {0};

/* initialize walls at borders of maze */
void initMazeBorder() {
  for (int x = 0; x < MAZE_SIZE; x++) {
    addWall(x, MAZE_SIZE - 1, NORTH);
    addWall(x, 0, SOUTH);
  }
  for (int y = 0; y < MAZE_SIZE; y++) {
    addWall(0, y, WEST);
  }
  for (int y = 0; y < MAZE_SIZE; y++) {
    addWall(MAZE_SIZE - 1, y, EAST);
  }
}

// marks that the cell at (x, y) has a wall in the direction given by dir
void addWall(int x, int y, int dir) {
  walls[x][y] |= (1 << dir);
  switch (dir) {
  case NORTH:
    if (y < MAZE_SIZE - 1) {
      walls[x][y + 1] |= (1 << SOUTH);
    }
    break;
  case SOUTH:
    if (y > 0) {
      walls[x][y - 1] |= (1 << NORTH);
    }
    break;
  case WEST:
    if (x > 0) {
      walls[x - 1][y] |= (1 << EAST);
    }
    break;
  case EAST:
    if (x < MAZE_SIZE - 1) {
      walls[x + 1][y] |= (1 << WEST);
    }
    break;
  }
}

// returns whether we know if there is a wall in the direction dir at (x, y)
bool hasKnownWall(int x, int y, int dir) {
  return walls[x][y] & (1 << dir);
}

bool hasUnknownWallAhead() {
  if (checkWall()) {
    addWall(cur_x, cur_y, facing);
    return true;
  }
  return false;
}
