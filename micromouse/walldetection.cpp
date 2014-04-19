/*
 * Wall Detection Module
 *
 * This module is used by the wall module. It operates the IR sensor, looking
 * for walls around us.
 */
#include "walldetection.h"

#ifndef GROUND_TEST

#include <Arduino.h>

const int PIN_IR_SENSOR_FRONT = A4;
const int PIN_IR_SENSOR_LEFT = A3;
const int PIN_IR_SENSOR_RIGHT = A2;

void initWallDetection() {
  pinMode(PIN_IR_SENSOR_FRONT, INPUT);
  pinMode(PIN_IR_SENSOR_LEFT, INPUT);
  pinMode(PIN_IR_SENSOR_RIGHT, INPUT);
}

bool checkWallFront() {
  return (analogRead(PIN_IR_SENSOR_FRONT) < 900);
}

bool checkWallLeft() {
  return (analogRead(PIN_IR_SENSOR_LEFT) < 900);
}

bool checkWallRight() {
  return (analogRead(PIN_IR_SENSOR_RIGHT) < 900);
}

#else // GROUND_TEST

#include "maze.h"

char realWalls[MAZE_SIZE][MAZE_SIZE] = {0};

void initWallDetection() {
}

//check if there is a wall in front of mouse
bool checkWallFront() {
  return realWalls[cur_x][cur_y] & (1 << facing);
}

bool checkWallLeft() {
  return realWalls[cur_x][cur_y] & (1 << ((facing + 3) % 4));
}

bool checkWallRight() {
  return realWalls[cur_x][cur_y] & (1 << ((facing + 1) % 4));
}

#endif
