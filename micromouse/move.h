/*
 * Motion Module
 *
 * This module implements translational movement and turning, as well as keeping
 * the micromouse going in a straight line.
 */
#ifndef __MOVE_H_
#define __MOVE_H_

void initMove();
void moveForward();
void turnLeft();
void turnRight();
void turn180();

#endif
