/*
 * Motion Module
 *
 * This module implements translational movement and turning, as well as keeping
 * the micromouse going in a straight line.
 */
#ifndef GROUND_TEST

#include "move.h"
#include <Arduino.h>
#include "maze.h" // trackPath, direction constants
#include "utils_and_consts.h" // motorRight, motorLeft

//move forward 1 space (figure out distance)
//add space to path
//update direction facing
void moveForward() {
  digitalWrite(motorRight, HIGH);
  digitalWrite(motorLeft, HIGH);
  delay(1000);
  digitalWrite(motorRight, LOW);
  digitalWrite(motorLeft, LOW);
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

#else // GROUND_TEST
// Use stubs

void moveForward() {}
void turnRight() {}
void turnLeft() {}

#endif // GROUND_TEST
