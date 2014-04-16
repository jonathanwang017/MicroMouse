/*
 * Direction selection module
 *
 * This module is responsible for deciding which direction to move in and moving
 * the mouse in the appropriate direction.
 */
#include "maze.h"
#include <stdlib.h> // abs
#include "move.h"
#include "stack.h"
#include "utils_and_consts.h"
#include "wall.h"

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

// unsigned char path_x[MAZE_SIZE * MAZE_SIZE];
// unsigned char path_y[MAZE_SIZE * MAZE_SIZE];
// int pathLength = 0;
int cur_x = 0;
int cur_y = 0;
// Distances range from 0 to 254, so just perfect
unsigned char maze[MAZE_SIZE][MAZE_SIZE];
int facing = NORTH;

// calculate manhattan distance between 2 points
int manhattanDist(int x1, int y1, int x2, int y2) {
  return abs(x1-x2) + abs(y1-y2);
}

// create initial maze with default values
void initGrid() {
  int m1 = (MAZE_SIZE - 1) / 2;
  int m2 = MAZE_SIZE / 2;
  for (int i=0; i<MAZE_SIZE; i++) {
    for (int j=0; j<MAZE_SIZE; j++) {
      maze[i][j] = min4(manhattanDist(i, j, m1, m1),
			manhattanDist(i, j, m1, m2),
			manhattanDist(i, j, m2, m1),
			manhattanDist(i, j, m2, m2));
    }
  }
}

coord getNeighborCoord(int x, int y, int dir) {
  coord ret;
  switch (dir) {
  case NORTH:
    ret.x = x;
    ret.y = y + 1;
    return ret;
  case SOUTH:
    ret.x = x;
    ret.y = y - 1;
    return ret;
  case EAST:
    ret.x = x + 1;
    ret.y = y;
    return ret;
  case WEST:
    ret.x = x - 1;
    ret.y = y;
    return ret;
  }
}

// Distance of neighbor in the direction dir if not blocked, otherwise INT_MAX
int distOfNeighbor(int x, int y, int dir) {
  if (hasKnownWall(x, y, dir)) {
    return INT_MAX;
  }
  coord neighborCoord = getNeighborCoord(x, y, dir);
  return maze[neighborCoord.x][neighborCoord.y];
}

void updateDistances(int x, int y) {
  static const int dirs[] = {NORTH, SOUTH, EAST, WEST};
  Stack<coord> stack;
  coord init(x, y);
  stack.push(init);
  while (!stack.empty()) {
    coord target = stack.pop();
    int dists[4];
    for (int i = 0; i < 4; i++) {
      dists[i] = distOfNeighbor(target.x, target.y, dirs[i]);
    }
    int desiredDistance = min4(dists[0], dists[1], dists[2], dists[3]) + 1;
    if (maze[target.x][target.y] != desiredDistance) {
      for (int i = 0; i < 4; i++) {
	if (dists[i] != INT_MAX) {
	  stack.push(getNeighborCoord(target.x, target.y, dirs[i]));
	}
      }
      maze[target.x][target.y] = desiredDistance;
    }
  }
}

void turnToDirection(int moveDir) {
  int change = moveDir - facing;
  // Coerce into range [-2, 2]
  if (change < -2) {
    change += 4;
  } else if (change > 2) {
    change -= 4;
  }

  // Note: Only one of these two blocks will (and should) be executed
  while (change < 0) {
    turnLeft();
    change++;
  }
  while (change > 0) {
    turnRight();
    change--;
  }

  facing = moveDir;
}

// Finds the direction that minimizes the distance, subject to the following:
// 1. If there is a tie between going forward and turning, go forward
// 2. Avoid turning around
int minimizingDirection() {
  int forward = facing;
  int right = (facing + 1) % 4;
  int backward = (facing + 2) % 4;
  int left = (facing + 3) % 4;
  int forwardVal = distOfNeighbor(cur_x, cur_y, forward);
  int rightVal = distOfNeighbor(cur_x, cur_y, right);
  int backwardVal = distOfNeighbor(cur_x, cur_y, backward);
  int leftVal = distOfNeighbor(cur_x, cur_y, left);

  int minVal = forwardVal;
  int minDir = forward;
  if (rightVal < minVal) {
    minVal = rightVal;
    minDir = right;
  }
  if (leftVal < minVal) {
    minVal = leftVal;
    minDir = left;
  }
  if (backwardVal < minVal) {
    minVal = backwardVal;
    minDir = backward;
  }
  return minDir;
}

void turnToMinNeighbor() {
  while (true) {
    int targetDir = minimizingDirection();
    turnToDirection(targetDir);
    // If there is a wall ahead of us, we must redo our distance chart and
    // go back to the beginning of the loop
    if (hasWallAhead()) {
      updateDistances(cur_x, cur_y);
    } else {
      break;
    }
  }
}

// add current location to path
void trackPath() {
  switch(facing) {
  case NORTH:
    cur_y++;
    break;
  case SOUTH:
    cur_y--;
    break;
  case EAST:
    cur_x++;
    break;
  case WEST:
    cur_x--;
    break;
  }
  // path_x[pathLength] = cur_x;
  // path_y[pathLength] = cur_y;
  // pathLength++;
}

// Make a move in the direction
void makeMove() {
  turnToMinNeighbor();
  moveForward();
  trackPath();
}
