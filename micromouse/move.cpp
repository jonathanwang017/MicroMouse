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

const int PIN_RIGHT_ENABLE = 19;
const int PIN_MOTOR_4 = 20;
const int PIN_MOTOR_3 = 21;
const int PIN_LEFT_ENABLE = 2;
const int PIN_MOTOR_1 = 3;
const int PIN_MOTOR_2 = 4;
const int PIN_LEFT_ENCODER_A = 9;
const int PIN_LEFT_ENCODER_B = 8;
const int PIN_RIGHT_ENCODER_A = 22;
const int PIN_RIGHT_ENCODER_B = 23;
const int PIN_LED = 13;

void initMove() {
  pinMode(PIN_RIGHT_ENABLE, OUTPUT);
  pinMode(PIN_MOTOR_3, OUTPUT);
  pinMode(PIN_MOTOR_4, OUTPUT);
  pinMode(PIN_LEFT_ENABLE, OUTPUT);
  pinMode(PIN_MOTOR_1, OUTPUT);
  pinMode(PIN_MOTOR_2, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
}

// move forward 1 space
void moveForward() {
  digitalWrite(PIN_LEFT_ENABLE, HIGH);
  digitalWrite(PIN_RIGHT_ENABLE, HIGH);
  digitalWrite(PIN_MOTOR_1, HIGH);
  digitalWrite(PIN_MOTOR_2, LOW);
  digitalWrite(PIN_MOTOR_3, HIGH);
  digitalWrite(PIN_MOTOR_4, LOW);
  delay(215);
  digitalWrite(PIN_LEFT_ENABLE, LOW);
  digitalWrite(PIN_RIGHT_ENABLE, LOW);
}

// turn 90 degrees right
void turnRight() {
  digitalWrite(PIN_LEFT_ENABLE, HIGH);
  digitalWrite(PIN_RIGHT_ENABLE, HIGH);
  digitalWrite(PIN_MOTOR_1, HIGH);
  digitalWrite(PIN_MOTOR_2, LOW);
  digitalWrite(PIN_MOTOR_3, LOW);
  digitalWrite(PIN_MOTOR_4, HIGH);
  delay(90);
  digitalWrite(PIN_LEFT_ENABLE, LOW);
  digitalWrite(PIN_RIGHT_ENABLE, LOW);
}

// turn 90 degrees left
void turnLeft() {
  digitalWrite(PIN_LEFT_ENABLE, HIGH);
  digitalWrite(PIN_RIGHT_ENABLE, HIGH);
  digitalWrite(PIN_MOTOR_1, LOW);
  digitalWrite(PIN_MOTOR_2, HIGH);
  digitalWrite(PIN_MOTOR_3, HIGH);
  digitalWrite(PIN_MOTOR_4, LOW);
  delay(90);
  digitalWrite(PIN_LEFT_ENABLE, LOW);
  digitalWrite(PIN_RIGHT_ENABLE, LOW);
}

// turn 180 degrees
void turn180() {
  digitalWrite(PIN_LEFT_ENABLE, HIGH);
  digitalWrite(PIN_RIGHT_ENABLE, HIGH);
  digitalWrite(PIN_MOTOR_1, LOW);
  digitalWrite(PIN_MOTOR_2, HIGH);
  digitalWrite(PIN_MOTOR_3, HIGH);
  digitalWrite(PIN_MOTOR_4, LOW);
  delay(195);
  digitalWrite(PIN_LEFT_ENABLE, LOW);
  digitalWrite(PIN_RIGHT_ENABLE, LOW);
}

#else // GROUND_TEST
// Use stubs

void moveForward() {}
void turnRight() {}
void turnLeft() {}
void turn180() {}

#endif // GROUND_TEST
