#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "maze.h"
#include "wall.h"

using namespace std;

extern char realWalls[MAZE_SIZE][MAZE_SIZE];

bool hasKnownRealWall(int x, int y, int dir) {
  return walls[x][y] & (1 << dir);
}

void usage(char *myName) {
  cout << "Usage: " << myName << " FILE\n";
  cout << "\n";
  cout << "Tests the micromouse navigation on the specified maze.\n";
  exit(1);
}

void readFile(char *progName, char *filename) {
  ifstream fin;

  fin.open(filename);
  if (fin.fail()) {
    cerr << progName << ": Could not open file " << filename << ": "
	 << strerror(errno) << "\n";
    exit(1);
  }

  fin.read(reinterpret_cast<char *>(realWalls), MAZE_SIZE * MAZE_SIZE);
  if (fin.eof()) {
    cerr << progName << ": Premature end of file\n";
    exit(1);
  }
  if (fin.fail()) {
    cerr << progName << ": Could not read file: " << strerror(errno) << "\n";
    exit(1);
  }

  fin.close();
}

// Prints S if (x, y) has a south wall, N if (x, y - 1) has a north wall,
// - if both, or spaces if none.
void printNSWall(int x, int y) {
  if (hasKnownRealWall(x, y, SOUTH) && hasKnownRealWall(x, y - 1, NORTH)) {
    cout << "--";
  } else if (hasKnownRealWall(x, y, SOUTH)) {
    cout << "SS";
  } else if (hasKnownRealWall(x, y - 1, NORTH)) {
    cout << "NN";
  } else {
    cout << "  ";
  }
}

// Prints E if (x, y) has an east wall, W if (x + 1, y) has a west wall,
// - if both, spaces if none
void printWEWall(int x, int y) {
  if (hasKnownRealWall(x, y, EAST) && hasKnownRealWall(x + 1, y, WEST)) {
    cout << "|";
  } else if (hasKnownRealWall(x, y, EAST)) {
    cout << "E";
  } else if (hasKnownRealWall(x + 1, y, WEST)) {
    cout << "W";
  } else {
    cout << " ";
  }
}

void printGrid() {
  // Print north walls of top row
  for (int x = 0; x < MAZE_SIZE; x++) {
    cout << " ";
    if (hasKnownRealWall(x, MAZE_SIZE - 1, NORTH)) {
      cout << "--";
    } else {
      cout << "  ";
    }
  }
  cout << "\n";

  // Print contents and south walls
  for (int y = MAZE_SIZE - 1; y >= 0; y--) {
    // Print west walls of first column
    if (hasKnownRealWall(0, y, WEST)) {
      cout << "|";
    } else {
      cout << " ";
    }

    // Print contents and side walls
    for (int x = 0; x < MAZE_SIZE; x++) {
      // Print columns
      if (x == cur_x && y == cur_y) {
	cout << " *";
      } else {
	cout << setw(2) << (int) maze[x][y] << setw(0);
      }
      // Print side walls
      if (x != MAZE_SIZE - 1) {
	printWEWall(x, y);
      } else {
	if (hasKnownRealWall(MAZE_SIZE - 1, y, EAST)) {
	  cout << "|";
	} else {
	  cout << " ";
	}
      }
    }
    cout << "\n";

    // Print south walls
    for (int x = 0; x < MAZE_SIZE; x++) {
      cout << " ";
      if (y != 0) {
	printNSWall(x, y);
      } else {
	if (hasKnownRealWall(x, 0, SOUTH)) {
	  cout << "--";
	} else {
	  cout << "  ";
	}
      }
    }
    cout << "\n";
  }
  cout << "Current: (" << cur_x << ", " << cur_y << ") "
       << setw(2) << (int) maze[cur_x][cur_y] << setw(0) << "\n";
  cout << "\n";
}

int main(int argc, char **argv) {
  ifstream fin;

  if (argc == 1) {
    usage(argv[0]);
  }

  readFile(argv[0], argv[1]);

  int m1 = (MAZE_SIZE - 1) / 2;
  int m2 = MAZE_SIZE / 2;

  initGrid();
  initMazeBorder();
  printGrid();
  while (maze[cur_x][cur_y] != 0) {
    makeMove();
    printGrid();
  }
}
