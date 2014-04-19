<<<<<<< HEAD
// Pin 13 has an LED connected on most Arduino boards.
int led = 13;
int motorLeft = 1;
int motorRight = 3;
char compass[4] = {'N','E','S','W'};

int path_x[256]; //track path x-coords
int path_y[256]; //track path y-coords
int pathLength = 0;
int cur_x = 0;
int cur_y = 0;
int maze[16][16]; //[y][x]
char facing = 0; //cur direction (N:0,E:1,S:2,W:3)
char sequenced[4]; //neighbors sequenced

=======
#include "maze.h"
#include "move.h"
#include "wall.h"
#include "walldetection.h"
>>>>>>> master

// the setup routine runs once when you press reset:

//initialize pins and setup maze with initial values
<<<<<<< HEAD
void setup() {       
  pinMode(led, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  initializeGrid();
  Serial.begin(57600);
}

//turn 90 degrees right (use gyro or calculate turning ratio)
void turnRight() {
  digitalWrite(motorLeft, HIGH);
  delay(1000);
  digitalWrite(motorLeft, LOW);
  if (facing < 3) {
    facing++;
  }
  else {
    facing = 0;
  }
}

//turn 90 degrees left
void turnLeft() {
  digitalWrite(motorRight, HIGH);
  delay(1000);
  digitalWrite(motorRight, LOW);
  if (facing > 0) {
    facing--;
  }
  else {
    facing = 3;
  }
}

//move forward 1 space (figure out distance)
//add space to path
//update direction facing
//sequence neighbors
void moveForward() {
  digitalWrite(motorRight, HIGH);
  digitalWrite(motorLeft, HIGH);
  delay(1000);
  digitalWrite(motorRight, LOW);
  digitalWrite(motorLeft, LOW);
  trackPath();
  orderNeighbors();
  switch(compass[facing]) {
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
=======
void setup() {
  initMaze();
  initWall();
  initMove();
  initWallDetection();
}

void loop() {
  // Go there for the first time
  while (maze[cur_x][cur_y] != 0) {
    makeMove();
>>>>>>> master
  }

<<<<<<< HEAD
void increasePath() {
  for (int i=0; i<pathLength; i++) {
    maze[path_y[i]][path_x[i]]++;
  }
}

int minimize(int left, int right, int up, int down) {
  int dir[4] = {left, right, up, down};
  int min = 256;
  for (int i=0; i<4; i++) {
    if (dir[i] < min) {
      min = dir[i];
=======
  while (true) {
    // Now go back
    switchDestinationToCorner();
    while (maze[cur_x][cur_y] != 0) {
      makeMove();
>>>>>>> master
    }

<<<<<<< HEAD
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

void orderNeighbors() {
  int N;
  int S;
  int E;
  int W;
  if (cur_x == 0) {
    N = maze[cur_y-1][cur_x];
    S = maze[cur_y+1][cur_x];
    E = maze[cur_y][cur_x+1];
    W = 258;
  }
  else if (cur_x == 15) {
    N = maze[cur_y-1][cur_x];
    S = maze[cur_y+1][cur_x];
    E = 258;
    W = maze[cur_y][cur_x-1];
  }
  else if (cur_y == 0) {
    N = 258;
    S = maze[cur_y+1][cur_x];
    E = maze[cur_y][cur_x+1];
    W = maze[cur_y][cur_x-1];
  }
  else if (cur_y == 15) {
    N = maze[cur_y-1][cur_x];
    S = 258;
    E = maze[cur_y][cur_x+1];
    W = maze[cur_y][cur_x-1];
  }
  else {
    N = maze[cur_y-1][cur_x];
    S = maze[cur_y+1][cur_x];
    E = maze[cur_y][cur_x+1];
    W = maze[cur_y][cur_x-1];
  }
  int directions[4] = {N, S, E, W};
  int temp = 0;
 
  for (int i=0; i<4; i++) {
    for (int j=i+1; j<4; j++) {
      if (directions[j] < directions[i]) {
        temp = directions[i];
        directions[i] = directions[j];
        directions[j] = temp;
      }
    }
  }
  
  for (int k=0; k<4; k++) {
    if (directions[k] == N) {
      sequenced[k] = 'N';
      N = 257;
    }
    else if (directions[k] == S) {
      sequenced[k] = 'S';
      S = 257;
    }
    else if (directions[k] == E) {
      sequenced[k] = 'E';
      E = 257;
    }
    else if (directions[k] == W) {
      sequenced[k] = 'W';
      W = 257;
    }
  }
}

//check if there is a wall in front of mouse
boolean checkWall() {
  return false;
}

void turnDirection(char dir) {
  while (facing!=dir) {
    turnRight();
  }
}
    
void chooseDirection() {
  char moveDir;
  for (int i=0; i<4; i++) {
    moveDir = sequenced[i];
    if (!checkWall()) {
      break;
    }
  } 
  turnDirection(moveDir);
}

void makeMove() {
  moveForward();
}


void loop() {

}

=======
    // Now go there again
    switchDestinationToCenter();
    while (maze[cur_x][cur_y] != 0) {
      makeMove();
    }
  }
}
>>>>>>> master
