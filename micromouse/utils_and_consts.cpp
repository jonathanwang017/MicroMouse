/*
 * Utilities
 */
#include "utils_and_consts.h" // Constants

//min function that takes in 4 argument
int min4(int a, int b, int c, int d) {
  int min = a;
  if (b < min) {
    min = b;
  }
  if (c < min) {
    min = c;
  }
  if (d < min) {
    min = d;
  }
  return min;
}
