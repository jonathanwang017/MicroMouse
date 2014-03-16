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
 
void reverse() {
  //stuff

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

int manhattanDist(int x1, int y1, int x2, int y2) {
  return abs(x1-x2) + abs(y1-y2);
}

void initializeGrid() {
   for (int i=0; i<16; i++) {
    for (int j=0; j<16; j++) {
      maze[i][j] = minimize(manhattanDist(i, j, 7, 7), manhattanDist(i, j, 7, 8), manhattanDist(i, j, 8, 7), manhattanDist(i, j, 8, 8));
    }
  }
}

void trackPath() {
   path_x[pathLength] = cur_x;
   path_y[pathLength] = cur_y;
   pathLength++;
}

char minNeighbor() {
  int N = maze[cur_x+1][cur_y];
  int S = maze[cur_x-1][cur_y];
  int E = maze[cur_x][cur_y+1];
  int W = maze[cur_x][cur_y-1];

  int minimum = minimize(N, S, E, W);
  char closestNeighbors[4];
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

char chooseMove() {
  char moveDir = minNeighbor();
  switch(facing) {
    case 'N':
      switch(moveDir) {
        case 'N':
          moveForward();
          break;
        case 'S':
          turnRight();
          turnRight();
          moveForward();
          break;
        case 'E':
          turnRight();
          moveForward();
          break;
        case 'W':
          turnLeft();
          moveForward();
          break;  
      }
    case 'S':
      switch(moveDir) {
        case 'N':
          turnRight();
          turnRight();
          moveForward();
          break;
        case 'S':
          moveForward();
          break;
        case 'E':
          turnLeft();
          moveForward();
          break;
        case 'W':
          turnRight();
          moveForward();
          break;  
      }
    case 'E':
      switch(moveDir) {
        case 'N':
          turnLeft();
          moveForward();
          break;
        case 'S':
          turnRight();
          moveForward();
          break;
        case 'E':
          moveForward();
          break;
        case 'W':
          turnRight();
          turnRight();
          moveForward();
          break;  
      }
    case 'W':
      switch(moveDir) {
        case 'N':
          turnRight();
          moveForward();
          break;
        case 'S':
          turnLeft();
          moveForward();
          break;
        case 'E':
          turnRight();
          turnRight();
          moveForward();
          break;
        case 'W':
          moveForward();
          break;  
      }
  }
}


void loop() {

}
