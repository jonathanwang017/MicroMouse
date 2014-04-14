/*
 * Utilities
 */
#ifndef __UTILS_AND_CONSTS_H_
#define __UTILS_AND_CONSTS_H_

// Pin 13 has an LED connected on most Arduino boards.
const int led = 13;
const int motorLeft = 1;
const int motorRight = 3;

const int INT_MAX = 32767; // 2^15 - 1

int min4(int a, int b, int c, int d);

#endif // __UTILS_AND_CONSTS_H_
