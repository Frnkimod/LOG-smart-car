// check_line.h
// Author: Init
// Date: 2025-02-09
#include "../../Core/BSP/Control/control.h"


#ifndef CHECK_LINE_H
#define CHECK_LINE_H
float BOUNDARY_VALUE[4];
float BOUNDARY_RATE(int flag);
int QR_NUM[6];
void check_line_Init();
void TT_motion(int32_t speed,int16_t dir,int32_t angle);
void car_in_Init();
void angle_check(int mode);
void pos_check(int mode);
void ac_motion(int need);
// Your function prototypes and declarations go here

#endif // CHECK_LINE_H