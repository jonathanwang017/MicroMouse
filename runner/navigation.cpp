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

// Prints the walls recorded between (x, y) and (x, y-1) as follows:
// (Y = has wall, U = unknown, N = doesn't have wall)
// (YY, NN, and UU should be the only states observed)
// (x, y) South    (x, y-1) North    Printed    Comment
//       Y                Y            ---
//       Y                N            SSS      Only south wall exists
//       Y                U            ^^^
//       N                Y            NNN      Only north wall exists
//       N                N                     Spaces
//       N                U            '''
//       U                Y            vvv
//       U                N            ,,,
//       U                U             ?
void printNSWall(int x, int y) {
  if (hasKnownWall(x, y, SOUTH)) {
    if (hasKnownWall(x, y - 1, NORTH)) {
      cout << "---";
    } else if (knownNotWall(x, y - 1, NORTH)) {
      cout << "SSS";
    } else {
      cout << "^^^";
    }
  } else if (knownNotWall(x, y, SOUTH)) {
    if (hasKnownWall(x, y - 1, NORTH)) {
      cout << "NNN";
    } else if (knownNotWall(x, y - 1, NORTH)) {
      cout << "   ";
    } else {
      cout << "'''";
    }
  } else {
    if (hasKnownWall(x, y - 1, NORTH)) {
      cout << "vvv";
    } else if (knownNotWall(x, y - 1, NORTH)) {
      cout << ",,,";
    } else {
      cout << " ? ";
    }
  }
}

// Prints the walls recorded between (x, y) and (x+1, y) as follows:
// (Y = has wall, U = unknown, N = doesn't have wall)
// (YY, NN, and UU should be the only states observed)
// (x, y) East    (x+1, y) West    Printed    Comment
//      Y               Y             | 
//      Y               N             E       Only east wall exists
//      Y               U             < 
//      N               Y             W       Only west wall exists
//      N               N                     Spaces
//      N               U             [ 
//      U               Y             > 
//      U               N             ] 
//      U               U             ?
void printWEWall(int x, int y) {
  if (hasKnownWall(x, y, EAST)) {
    if (hasKnownWall(x + 1, y, WEST)) {
      cout << "|";
    } else if (knownNotWall(x + 1, y, WEST)) {
      cout << "E";
    } else {
      cout << "<";
    }
  } else if (knownNotWall(x, y, EAST)) {
    if (hasKnownWall(x + 1, y, WEST)) {
      cout << "W";
    } else if (knownNotWall(x + 1, y, WEST)) {
      cout << " ";
    } else {
      cout << "[";
    }
  } else {
    if (hasKnownWall(x + 1, y, WEST)) {
      cout << ">";
    } else if (knownNotWall(x + 1, y, WEST)) {
      cout << "]";
    } else {
      cout << "?";
    }
  }
}

void printGrid() {
  // Print north walls of top row
  for (int x = 0; x < MAZE_SIZE; x++) {
    cout << " ";
    if (hasKnownWall(x, MAZE_SIZE - 1, NORTH)) {
      cout << "---";
    } else if (knownNotWall(x, MAZE_SIZE - 1, NORTH)) {
      cout << "   ";
    } else {
      cout << " ? ";
    }
  }
  cout << "\n";

  // Print contents and south walls
  for (int y = MAZE_SIZE - 1; y >= 0; y--) {
    // Print west walls of first column
    if (hasKnownWall(0, y, WEST)) {
      cout << "|";
    } else if (knownNotWall(0, y, WEST)) {
      cout << " ";
    } else {
      cout << "?";
    }

    // Print contents and side walls
    for (int x = 0; x < MAZE_SIZE; x++) {
      // Print columns
      if (x == cur_x && y == cur_y) { // Our position
	cout << "  *";
      } else {
	cout << setw(3) << (int) maze[x][y] << setw(0);
      }
      // Print side walls
      if (x != MAZE_SIZE - 1) { // Side wall between columns
	printWEWall(x, y);
      } else { // Eastern border
	if (hasKnownWall(MAZE_SIZE - 1, y, EAST)) {
	  cout << "|";
	} else if (knownNotWall(MAZE_SIZE - 1, y, EAST)) {
	  cout << " ";
	} else {
	  cout << "?";
	}
      }
    }
    cout << "\n";

    // Print south walls
    for (int x = 0; x < MAZE_SIZE; x++) {
      cout << " ";
      if (y != 0) { // Horizontal wall between rows
	printNSWall(x, y);
      } else { // South walls of bottom row
	if (hasKnownWall(x, 0, SOUTH)) {
	  cout << "---";
	} else if (knownNotWall(x, 0, SOUTH)) {
	  cout << "   ";
	} else {
	  cout << " ? ";
	}
      }
    }
    cout << "\n";
  }
  cout << "Current: (" << cur_x << ", " << cur_y << ") "
       << (int) maze[cur_x][cur_y] << "\n";
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
