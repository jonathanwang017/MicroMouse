Module Descriptions
===================

High-Level Modules
------------------

### Main Module ###
File: micromouse.ino

This module takes care of initialization and the main methods. It is in charge
of initializing all the other modules during the initialization stage.

Methods:
-   void setup()
-   void loop()

### Direction Selection Module ###
File: maze.cpp

This module is responsible for deciding which direction to move in and moving
the mouse in the appropriate direction.

Constants:
-   MAZE_SIZE
-   NORTH
-   EAST
-   SOUTH
-   WEST

Global variables:
-   cur_x - Current x coordinate
-   cur_y - Current y coordinate
-   maze - MAZE_SIZE × MAZE_SIZE array. `maze[x][y]` gives the presumed distance
    from (x, y) to the destination.
-   facing - the direction the mouse is facing

Structures:
coord: (x, y) pair
-   x
-   y

External Methods:
-   initMaze() - Initializes maze module
-   makeMove() - Moves the mouse by one square
-   switchDestinationToCenter()
-   switchDestinationToCorner()

Internal Methods:
-   manhattanDist(int x1, int y1, int x2, int y2) - finds Manhattan distance
    between (x1, y1) and (x2, y2)
-   getNeighborCoord(int x, int y, int dir) - Returns coordinates of neighbor
    of (x, y) in direction `dir`
-   distOfNeighbor(int x, int y, int dir) - If there is not a wall between the
    cell (x, y) and its neighbor in the direction `dir`, returns the neighbor's
    distance from the destination. Otherwise returns `INT_MAX`.
-   updateDistances(Stack<coord> &stack, coord destSq[], int numDestSq) - 
    Updates the recorded distances of each cell to the destination. Usually run
    when a new wall has been discovered.
-   turnToDirection(int moveDir) - turns the mouse to the direction `moveDir`
-   int minimizingDirection() - finds the direction of the neighbor with the
    least distance
-   turnToMinNeighbor() - turns to the neighbor with the least distance
-   trackPath() - Updates position of mouse on grid

### Wall Module ###
File: wall.cpp

This module is in charge of remembering where there are walls, and initiating
detection of previously unknown walls.

Global variables:
-   walls - `walls[x][y]` equals the number with bits `abcdefgh`, where:
        h - 1 if there is a wall to the north, 0 otherwise
        g - " "    "   "  "  "   "   "  south, "    "
        f - " "    "   "  "  "   "   "  east,  "    "
        e - " "    "   "  "  "   "   "  west,  "    "
        d - " "    "   is known to be no wall to the north, 0 otherwise
        c - " "    "   "    "   "  "  "   "    "  "  east,  "    " 
        b - " "    "   "    "   "  "  "   "    "  "  south, "     "
        a - " "    "   "    "   "  "  "   "    "  "  west,  "     "

External Methods:
-   hasKnownWall(int x, int y, int dir) - does (x, y) have a known wall in the
    direction `dir`?
-   knownNotWall(int x, int y, int dir) - is (x, y) known to not have a wall in
    the direction `dir`?
-   initWall() - initializes the module
-   hasWallAhead() - is there a wall in front of the mouse. Convenience method.

Internal Methods:
-   markWall(int x, int y, int dir, bool hasWall) - marks that (x, y) has or
    doesn't have a wall in the direction `dir`

Device Drivers
--------------

### Motion Module ###
File: move.cpp

This module implements translational movement and turning, as well as keeping
the micromouse going in a straight line.

Methods:
-   initMove() - initializes the module
-   moveForward()
-   turnLeft()
-   turnRight()
-   turn180()

### Wall Detection Module ###
File: walldetection.cpp

This module is used by the wall module. It operates the IR sensor, looking for
walls around us.

Methods:
-   checkWall() - Checks if there is a wall in front of the mouse
-   initWallDetection() - Initializes the module


Utilities
---------

### Utility Module ###
File: utils_and_consts.cpp

This file contains some utilities and constants.

Constants:
-   INT_MAX - 2^15 - 1 (largest int on Arduino/Teensy)
-   UCHAR_MAX - 255 (largest unsigned char)

Methods:
-   max4(int a, int b, int c, int d)
