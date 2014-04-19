/*
 * Wall Module
 *
 * This module is in charge of remembering where there are walls, and initiating
 * detection of previously unknown walls.
 */
#include "wall.h"
#include "maze.h"
#include "walldetection.h"

// Format: for each element at index x, y, bit 0 (LSB) is whether we know if
// there is a wall at (x, y) in the north direction, likewise bit 1 is for 
// east, bit 2 for south, bit 3 for west. Bit 4 is whether we know if there
// isn't a wall at (x, y) in the north direction. Bit 5 is ...
char walls[MAZE_SIZE][MAZE_SIZE] = {0};

// marks that the cell at (x, y) has or doesn't have a wall in the direction
// dir
void markWall(int x, int y, int dir, bool hasWall) {
  int off = hasWall ? 0 : 4;
  walls[x][y] |= (1 << off << dir);
  switch (dir) {
  case NORTH:
    if (y < MAZE_SIZE - 1) {
      walls[x][y + 1] |= (1 << off << SOUTH);
    }
    break;
  case SOUTH:
    if (y > 0) {
      walls[x][y - 1] |= (1 << off << NORTH);
    }
    break;
  case WEST:
    if (x > 0) {
      walls[x - 1][y] |= (1 << off << EAST);
    }
    break;
  case EAST:
    if (x < MAZE_SIZE - 1) {
      walls[x + 1][y] |= (1 << off << WEST);
    }
    break;
  }
}

// initialize walls at borders of maze and to right of (0, 0)
void initWall() {
  for (int x = 0; x < MAZE_SIZE; x++) {
    markWall(x, MAZE_SIZE - 1, NORTH, true);
    markWall(x, 0, SOUTH, true);
  }
  for (int y = 0; y < MAZE_SIZE; y++) {
    markWall(0, y, WEST, true);
  }
  for (int y = 0; y < MAZE_SIZE; y++) {
    markWall(MAZE_SIZE - 1, y, EAST, true);
  }
  markWall(0, 0, EAST, true);
}

// returns whether we know if there is a wall in the direction dir at (x, y)
bool hasKnownWall(int x, int y, int dir) {
  return walls[x][y] & (1 << dir);
}

// Returns whether we know if there isn't a wall in the direction dir at (x, y)
bool knownNotWall(int x, int y, int dir) {
  return walls[x][y] & (1 << 4 << dir);
}

// Returns whether there is a wall in the given direction. Updates the wall
// table too.
bool detectWall(int direction) {
  bool hasWall;
  if (direction == facing) {
    hasWall = checkWallFront();
  } else if (direction == (facing + 3) % 4) {
    hasWall = checkWallLeft();
  } else if (direction == (facing + 1) % 4) {
    hasWall = checkWallRight();
  } else {
    // No sensor behind, just return false. This shouldn't be called anyway.
    return false;
  }
  markWall(cur_x, cur_y, direction, hasWall);
  return hasWall;
}
