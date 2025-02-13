// tt.h
// Author: Dereko
// Date: 2025-02-13
#include "../../Core/LG/check/check_line.h"
#ifndef TT_H
#define TT_H
// Your function prototypes and declarations go here
void smooth_motion(int32_t max_speed, int32_t acceleration, int32_t total_distance,
                   int32_t angle, int32_t dir, float load, int32_t target_position);
void set_motor_speed(int32_t speed, int32_t angle, int32_t dir);

#endif // TT_H