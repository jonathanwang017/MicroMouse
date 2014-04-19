#include "maze.h"
#include "move.h"
#include "wall.h"
#include "walldetection.h"

// the setup routine runs once when you press reset:

//initialize pins and setup maze with initial values
void setup() {
  initMaze();
  initWall();
  initMove();
  initWallDetection();
  delay(3000);
}

void loop() {
  // Go there for the first time
  while (maze[cur_x][cur_y] != 0) {
    makeMove();
  }

  while (true) {
    // Now go back
    switchDestinationToCorner();
    while (maze[cur_x][cur_y] != 0) {
      makeMove();
    }

    // Now go there again
    switchDestinationToCenter();
    while (maze[cur_x][cur_y] != 0) {
      makeMove();
    }
  }
}
