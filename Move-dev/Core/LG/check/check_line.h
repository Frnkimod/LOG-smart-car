// check_line.h
// Author: Init
// Date: 2025-02-09
#include "../../Core/BSP/Control/control.h"

#ifndef CHECK_LINE_H
#define CHECK_LINE_H
float BOUNDARY_VALUE[4];
int QR_NUM[6];
void check_line_Init();
void car_in_Init();
float BOUNDARY_RATE();
float ACTION_MODE();
// Your function prototypes and declarations go here

#endif // CHECK_LINE_H