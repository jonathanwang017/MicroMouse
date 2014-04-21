/*
 * Wall Detection Module
 *
 * This module is used by the wall module. It operates the IR sensor, looking
 * for walls around us.
 */
#include "walldetection.h"

#ifndef GROUND_TEST

#include <Arduino.h>

const int PIN_IR_SENSOR = A4;

void initWallDetection() {
  pinMode(PIN_IR_SENSOR, INPUT);
}

/** returns whether there is a wall in front of the mouse */
bool checkWall() {
  return (analogRead(PIN_IR_SENSOR) < 1000);
}

#else // GROUND_TEST

#include "maze.h"

char realWalls[MAZE_SIZE][MAZE_SIZE] = {0};

void initWallDetection() {
}

bool checkWall() {
  return realWalls[cur_x][cur_y] & (1 << facing);
}

#endif
