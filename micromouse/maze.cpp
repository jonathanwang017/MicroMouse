/*
 * Direction selection module
 *
 * This module is responsible for deciding which direction to move in and moving
 * the mouse in the appropriate direction.
 */
#include "maze.h"
#include <stdlib.h> // abs
#include <string.h> // memset
#include "move.h"
#include "stack.h"
#include "utils_and_consts.h"
#include "wall.h"

int cur_x = 0;
int cur_y = 0;
// Distances range from 0 to 254, so just perfect
unsigned char maze[MAZE_SIZE][MAZE_SIZE];
int facing = NORTH;
coord CENTER_SQUARES[4];
coord *destSquares;
int destSquaresLen;

// calculate manhattan distance between 2 points
int manhattanDist(int x1, int y1, int x2, int y2) {
  return abs(x1-x2) + abs(y1-y2);
}

// create initial maze with default values
void initMaze() {
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
  CENTER_SQUARES[0].x = CENTER_SQUARES[1].x = m1;
  CENTER_SQUARES[2].x = CENTER_SQUARES[3].x = m2;
  CENTER_SQUARES[0].y = CENTER_SQUARES[2].y = m1;
  CENTER_SQUARES[1].y = CENTER_SQUARES[3].y = m2;
  destSquares = CENTER_SQUARES;
  destSquaresLen = 4;
}

// Returns the coordinates of the neighbor of (x, y) in the direction dir
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

// If there is not a known wall between the cell (x, y) and its neighbor in the
// direction `dir`, returns the neighbor's distance from the destination.
// Otherwise returns `INT_MAX`.
int distOfNeighbor(int x, int y, int dir) {
  if (hasKnownWall(x, y, dir)) {
    return INT_MAX;
  }
  coord neighborCoord = getNeighborCoord(x, y, dir);
  return maze[neighborCoord.x][neighborCoord.y];
}

// Update distances. The stack is a stack of squares to process. Other items
// are added to and removed from the stack routinely. destSq is an array of
// squares whose distances should be ensured to be 0.
void updateDistances(Stack<coord> &stack, coord destSq[], int numDestSq) {
  static const int dirs[] = {NORTH, SOUTH, EAST, WEST};
  // Now calculate all distances (starting with destination squares)
  while (!stack.empty()) {
    coord target = stack.pop();
    int dists[4];
    bool isDestSq = false;

    for (int i = 0; i < 4; i++) {
      dists[i] = distOfNeighbor(target.x, target.y, dirs[i]);
    }

    // Are we a destination square?
    for (int i = 0; i < numDestSq; i++) {
      if (target.x == destSq[i].x && target.y == destSq[i].y) {
	isDestSq = true;
	break;
      }
    }

    int desiredDistance = (isDestSq
			   ? 0
			   : min4(dists[0], dists[1], dists[2], dists[3]) + 1);
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

// Look for new walls at the current square and update distances if there are
// new walls.
void updateDistancesIfNeeded() {
  int dirs[] = {facing, (facing + 3) % 4, (facing + 1) % 4};
  bool dirty = false;
  bool dirtyDirs[4] = {false};
  // Check every direction for new walls. (Remember, we must continue even if we discover walls.)
  for (int i = 0; i < 3; i++) {
    if (!hasKnownWall(cur_x, cur_y, dirs[i]) && !knownNotWall(cur_x, cur_y, dirs[i])) {
      if (detectWall(dirs[i])) {
	dirty = true;
	dirtyDirs[i] = true;
      }
    }
  }
  // Do update if necessary. Push current cell's former neighbors and itself onto stack.
  if (dirty) {
    Stack<coord> stack;
    coord cur(cur_x, cur_y);
    for (int i = 0; i < 4; i++) {
      if (dirtyDirs[i]) {
	stack.push(getNeighborCoord(cur_x, cur_y, dirs[i]));
      }
    }
    stack.push(cur);
    updateDistances(stack, destSquares, destSquaresLen);  
  }
}

// Updates distances if necessary, and then finds the direction that minimizes
// the distance, subject to the following:
// 1. If there is a tie between going forward and turning, go forward
// 2. Avoid turning around
int minimizingDirection() {
  int forward = facing;
  int right = (facing + 1) % 4;
  int backward = (facing + 2) % 4;
  int left = (facing + 3) % 4;

  updateDistancesIfNeeded();
  // The minimizing distance will be maze[cur_x][cur_y] - 1, due to the fact
  // that each cell's distance is the distance of its neighbor closest to the
  // destination plus one.
  int minVal = maze[cur_x][cur_y] - 1;
  if (distOfNeighbor(cur_x, cur_y, forward) == minVal) {
    return forward;
  } else if (distOfNeighbor(cur_x, cur_y, right) == minVal) {
    return right;
  } else if (distOfNeighbor(cur_x, cur_y, left) == minVal) {
    return left;
  } else {
    return backward;
  }
}

// Turns the mouse to the direction moveDir
void turnToDirection(int moveDir) {
  int change = moveDir - facing;
  // Coerce into range [-2, 2)
  if (change < -2) {
    change += 4;
  } else if (change >= 2) {
    change -= 4;
  }

  switch (change) {
  case -2:
    turn180();
    break;
  case -1:
    turnLeft();
    break;
  case 1:
    turnRight();
    break;
  }

  facing = moveDir;
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
}

// Make a move in the direction
void makeMove() {
  turnToDirection(minimizingDirection());
  moveForward();
  trackPath();
}

// Switches the destination to the center squares and resets the board
// accordingly.
void switchDestinationToCenter() {
  int m1 = (MAZE_SIZE - 1) / 2;
  int m2 = MAZE_SIZE / 2;

  // Wipe all distances
  // Fortunately maze is unsigned...
  memset(maze, UCHAR_MAX, sizeof(**maze) * MAZE_SIZE * MAZE_SIZE);

  // Push one destination square onto stack. (updateDistances will end up
  // pushing the other three anyway.)
  Stack<coord> stack;
  coord c(m1, m1);
  stack.push(c);

  destSquares = CENTER_SQUARES;
  destSquaresLen = 4;
  updateDistances(stack, CENTER_SQUARES, 4);
}

// Switches the destination to (0, 0) and resets the board accordingly.
void switchDestinationToCorner() {
  // Wipe all distances
  // Fortunately maze is unsigned...
  memset(maze, UCHAR_MAX, sizeof(**maze) * MAZE_SIZE * MAZE_SIZE);

  // Push one destination square onto stack. (updateDistances will end up
  // pushing the other three anyway.)
  Stack<coord> stack;
  coord c(0, 0);
  stack.push(c);

  // Hack: Treat c as one-element array
  destSquares = &c;
  destSquaresLen = 1;
  updateDistances(stack, &c, 1);
}
