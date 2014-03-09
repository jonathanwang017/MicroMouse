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


int manhattanDist(int x1, int y1, int x2, int y2) {
  return abs(x1-x2) + abs(y1-y2);
}


/*Given current point in maze, return neighbor {N,S,E,W} that 
should take the mouse closer to the center.*/
char closestNeighbor(int x, int y) {
  //To-do
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
  
  
}
// the loop routine runs over and over again forever:
void loop() {

}
