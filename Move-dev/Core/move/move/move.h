// move.h
// Author: Dereko
// Date: 2025-02-13

#ifndef MOVE_H
#define MOVE_H
#include "../../BSP/42-dev/Emm_V5.h"
#include "../../Core/LG/check/check_line.h"
// Your function prototypes and declarations go here
void move_motion(int32_t dir, double distance);
void main_move();
double calculate_circle(double distance);
void set_motor_speed(uint16_t speed);
#endif // MOVE_H