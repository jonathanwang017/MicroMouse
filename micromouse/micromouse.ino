// Pin 13 has an LED connected on most Arduino boards.
int led = 13;
int motorLeft = 1;
int motorRight = 3;

// the setup routine runs once when you press reset:
void setup() {                
  pinMode(led, OUTPUT);    
  pinMode(motorLeft, OUTPUT); 
  pinMode(motorRight, OUTPUT);
}

void turnRight() {
  digitalWrite(motorLeft, HIGH);
  delay(1000);
  digitalWrite(motorLeft, LOW);
}
void turnLeft() {
  digitalWrite(motorRight, HIGH);
  delay(1000);
  digitalWrite(motorRight, LOW);
}
void moveForward() {
  digitalWrite(motorRight, HIGH);
  digitalWrite(motorLeft, HIGH);
  delay(1000);
  digitalWrite(motorRight, LOW);
  digitalWrite(motorLeft, LOW);
}
void moveBackward() {
  //stuff
}
 
void turn180() {
  //stuff

}

int manhattanDist(int x1, int y1, int x2, int y2) {
  return abs(x1-x2) + abs(y1-y2);
}


/*Given current point in maze, return neighbor {N,S,E,W} that 
should take the mouse closer to the center.*/
char[4] closestNeighbor(int maze[16][16], int currentSpace[2]) {
  int N = maze[currentSpace[0]+1][currentSpace[1]];
  int S = maze[currentSpace[0]-1][currentSpace[1]];
  int E = maze[currentSpace[0]][currentSpace[1]+1];
  int W = maze[currentSpace[0]][currentSpace[1]-1];
  //There's definitely more C++ ways to do this... but it's
  //late and I don't want to think about new syntax
  //char arrays are initalized to zeros, right?
  int neighborVals[4] = {N, S, E, W};
  char neighborDirections[4] = {'N', 'S', 'E', 'W'};
  int closest = minimize(N, S, E, W);
  char closestNeighbors[4];
  for (int i=0; i<4; i++) { 
    if (neighborVals[i] == closest) {
      closestNeighbors[i] = neighborDirections[i];
    }
  }
  return closestNeighbors;
}

char chooseMove(char fwdDir, int curSpace[2], map<char, char> directions) {
  //start this with face N
  char facing = fwdDir;
  char moves[4] = closestNeighbor(curspace);
  for (int i=0; i<4; i++) {
    if (moves[i] == facing) {
      return 'F';
    }
  }
  //chose arbitrary from moves, would need to iterate through again
}

void makeMove(char action) {
  if (action == "L") {
    turnLeft();
  }
  else if (action == "R") {
    turnRight();
  }
  else if (action == "B") {
    turn180();
  }
  moveForward();
}
map<char, char> updateMoves(char curFacing){
  //stuff
  //return the new set of ways to move, eg if now facing S, then {"S":"F", "E":"L"} etc
}

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

/* ***Outline*** of algorithm for navigating to center of 16x16 maze
1) Move to cell which it has gone to least
2) Move to the cell that has minimum cell value
3) If possible the robot must try to go straight.
*/

void floodFill() {
  int maze[16][16];

  
  // initialize distance from center as if there are no walls
  for (int i=0; i<16; i++) {
    for (int j=0; j<16; j++) {
      maze[i][j] = minimize(manhattanDist(i, j, 8, 8), manhattanDist(i, j, 8, 9), manhattanDist(i, j, 9, 8), manhattanDist(i, j, 9, 9));
    }
  }
  
  /* Assume mouse is always in the SW corner of maze and that it is
  facing the opening to the North */
  int curSpace[2] = {0, 16};
  char facing = 'N';
  map<char, char> moves;// = calcMoves('N');
  while (maze[curSpace[0]][curSpace[1]] != 0) {
    char nextMove = choseMove(facing, curSpace, moves);
//    facing = //how to update this
//    moves = //also this
//    curSpace = //and this  
  }
  
}
// the loop routine runs over and over again forever:
void loop() {

}
