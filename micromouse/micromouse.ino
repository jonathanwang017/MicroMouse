#include "maze.h"
#include "utils_and_consts.h"
#include "wall.h"

// the setup routine runs once when you press reset:

//initialize pins and setup maze with initial values
void setup() {       
  pinMode(led, OUTPUT);
  pinMode(motorLeft, OUTPUT); 
  pinMode(motorRight, OUTPUT);
  initGrid();
  initMazeBorder();
}

void loop() {

}
