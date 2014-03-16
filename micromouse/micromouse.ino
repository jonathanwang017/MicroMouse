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
char facing = 'N';

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

//find neighboring space with smallest value
char minNeighbor() {
  int N = maze[cur_x][cur_y-1];
  int S = maze[cur_x][cur_y+1];
  int E = maze[cur_x+1][cur_y];
  int W = maze[cur_x-1][cur_y];
  int minimum = minimize(N, S, E, W);
  char closestNeighbors[4];
  
  //return char corresponding to smallest value
  if (minimum == N) {
    return 'N';
  }
  else if (minimum == S) {
    return 'S';
  }
  else if (minimum == E) {
    return 'E';
  }
  else if (minimum == W) {
    return 'W';
  }
}

//check if there is a wall in front of mouse
boolean checkWall() {
  return false;
}


//I'm pretty sure multiple switch statements is a sub optimal method so feel free to improve:

//!!!!uggh actually this does not take walls into account well...so needs fixing

//turn to optimal direction
//update facing direction
char chooseDirection() {
  char moveDir = minNeighbor();
  switch(facing) {
    case 'N':
      switch(moveDir) {
        case 'N':
          facing = 'N';
          break;
        case 'S':
          turnRight();
          turnRight();
          facing = 'S';
          break;
        case 'E':
          turnRight();
          facing = 'E';
          break;
        case 'W':
          turnLeft();
          facing = 'W';
          break;  
      }
    case 'S':
      switch(moveDir) {
        case 'N':
          turnRight();
          turnRight();
          facing = 'N';
          break;
        case 'S':
          facing = 'S';
          break;
        case 'E':
          turnLeft();
          facing = 'E';
          break;
        case 'W':
          turnRight();
          facing = 'W';
          break;  
      }
    case 'E':
      switch(moveDir) {
        case 'N':
          turnLeft();
          facing = 'N';
          break;
        case 'S':
          turnRight();
          facing = 'S';
          break;
        case 'E':
          facing = 'E';
          break;
        case 'W':
          turnRight();
          turnRight();
          facing = 'W';
          break;  
      }
    case 'W':
      switch(moveDir) {
        case 'N':
          turnRight();
          facing = 'N';
          break;
        case 'S':
          turnLeft();
          facing = 'S';
          break;
        case 'E':
          turnRight();
          turnRight();
          facing = 'E';
          break;
        case 'W':
          facing = 'W';
          break;  
      }
  }
}


//double check selected move and move forward
void makeMove() {
  moveForward();
}

void loop() {

}
