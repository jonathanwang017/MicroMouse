#include <cstdio>
#include "maze.h"

using namespace std;

int main() {
  initGrid();
  for (int y = 0; y < MAZE_SIZE; y++) {
    for (int x = 0; x < MAZE_SIZE; x++) {
      printf("%2d ", maze[x][y]);
    }
    putchar('\n');
  }
}
