#include <limits.h>

// Pin 13 has an LED connected on most Arduino boards.
int led = 13;
int motorLeft = 1;
int motorRight = 3;

int path_x[256];
int path_y[256];
int pathLength = 0;
int cur_x = 0;
int cur_y = 0;
int maze[16][16];

const int NORTH = 0;
const int EAST = 1;
const int SOUTH = 2;
const int WEST = 3;
int facing = NORTH;

// the setup routine runs once when you press reset:

//initialize pins and setup maze with initial values
void setup() {       
  pinMode(led, OUTPUT);
  pinMode(motorLeft, OUTPUT); 
  pinMode(motorRight, OUTPUT);
  initializeGrid();
}

//turn 90 degrees right (use gyro or calculate turning ratio)
void turnRight() {
  digitalWrite(motorLeft, HIGH);
  delay(1000);
  digitalWrite(motorLeft, LOW);
}

//turn 90 degrees left
void turnLeft() {
  digitalWrite(motorRight, HIGH);
  delay(1000);
  digitalWrite(motorRight, LOW);
}

//move forward 1 space (figure out distance)
//add space to path
//update direction facing
void moveForward() {
  digitalWrite(motorRight, HIGH);
  digitalWrite(motorLeft, HIGH);
  delay(1000);
  digitalWrite(motorRight, LOW);
  digitalWrite(motorLeft, LOW);
  trackPath();
  switch(facing) {
    case 'N':
      cur_y--;
      break;
    case 'S':
      cur_y++;
      break;
    case 'E':
      cur_x++;
      break;
    case 'W':
      cur_x--;
      break;
  }
}

//min function that takes in 4 argument
int minimize(int left, int right, int forward, int backward) {
  int directions[4] = {left, right, forward, backward};
  int min = 0;
  for (int i=0; i<4; i++) {
    if (directions[i] < min) {
      min = directions[i];
    }
  }
  return min;
}

int minIndex(int items[], int length) {
  int minIndex = 0;
  int minVal = INT_MAX;
  for (int i = 0; i < length; i++) {
    if (items[i] < minVal) {
      minVal = items[i];
      minIndex = i;
    }
  }
  return minIndex;
}

//calculate manhattan distance between 2 points
int manhattanDist(int x1, int y1, int x2, int y2) {
  return abs(x1-x2) + abs(y1-y2);
}

//create initial maze with default values
void initializeGrid() {
   for (int i=0; i<16; i++) {
    for (int j=0; j<16; j++) {
      maze[i][j] = minimize(manhattanDist(i, j, 7, 7), manhattanDist(i, j, 7, 8), manhattanDist(i, j, 8, 7), manhattanDist(i, j, 8, 8));
    }
  }
}

//add current location to path
void trackPath() {
   path_x[pathLength] = cur_x;
   path_y[pathLength] = cur_y;
   pathLength++;
}

void turnToMinNeighbor() {
  // XXX check for out of bounds
  int dists[] = {maze[cur_x][cur_y-1], maze[cur_x][cur_y+1],
		 maze[cur_x+1][cur_y], maze[cur_x-1][cur_y]};
  int dirs[] = {NORTH, SOUTH, EAST, WEST};

  while (true) {
    int targetDirIdx = minIndex(dists, 4);
    turnToDirection(dirs[targetDirIdx]);
    if (checkWall()) {
      dists[targetDirIdx] = INT_MAX;
    } else {
      break;
    }
  }
}

//check if there is a wall in front of mouse
boolean checkWall() {
  return false;
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

//double check selected move and move forward
void makeMove() {
  moveForward();
}

void loop() {

}
