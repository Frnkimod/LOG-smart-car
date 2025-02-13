// move.h
// Author: Dereko
// Date: 2025-02-13

#ifndef MOVE_H
#define MOVE_H
#include "../../Core/LG/check/check_line.h"
// Your function prototypes and declarations go here
void move_motion(int32_t dir, int32_t circle);
void main_move();
void set_motor_speed(uint16_t speed);
#endif // MOVE_H