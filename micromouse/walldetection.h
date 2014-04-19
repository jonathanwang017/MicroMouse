/*
 * Wall Detection Module
 *
 * This module is used by the wall module. It operates the IR sensor, looking
 * for walls around us.
 */
#ifndef __WALLDETECTION_H_
#define __WALLDETECTION_H_

void initWallDetection();
bool checkWallFront();
bool checkWallLeft();
bool checkWallRight();

#endif
