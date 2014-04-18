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
-   path_x
-   path_y
-   pathLength
-   cur_x
-   cur_y
-   maze
-   facing

Methods:
-   manhattanDist(int x1, int y1, int x2, int y2)
-   initGrid()
-   chooseMove()
-   distOfNeighbor()
-   turnToMinNeighbor()
-   turnToDirection(int direction)
-   updateDistances() - how to do this?
-   trackPath() - Updates position of mouse on grid

### Wall Module ###
File: wall.cpp

This module is in charge of remembering where there are walls, and initiating
detection of previously unknown walls.

Global variables:
-   walls

Methods:
-   addWall(int x, int y, int dir)
-   hasKnownWall(int x, int y, int dir)
-   initMazeBorder()


Device Drivers
--------------

### Motion Module ###
File: move.cpp

This module implements translational movement and turning, as well as keeping
the micromouse going in a straight line.

Methods:
-   moveForward()
-   turnLeft()
-   turnRight()
-   turn180()

### Wall Detection Module ###
File: walldetection.ino

This module is used by the wall module. It operates the IR sensor, looking for
walls around us.

Methods:
-   checkWall()


Utilities
---------

### Utility Module ###
File: util.cpp

This file contains some utilities.

Methods:
-   max4(int a, int b, int c, int d)
-   minIndex(int items[], int length)
