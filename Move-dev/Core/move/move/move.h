// move.h
// Author: Dereko
// Date: 2025-02-13

#ifndef MOVE_H
#define MOVE_H
#include "../../BSP/42-dev/Emm_V5.h"
#include "../../Core/LG/check/check_line.h"
// Your function prototypes and declarations go here
void take_check(Motor *motor1, Motor *motor2, Motor *motor3, Motor *motor4,int32_t dir,int32_t speed, float cam_distance) ;
void take_move(int32_t mit);
void Emm_V5ControlX(Motor *motor1,Motor *motor2,Motor *motor3,Motor *motor4, uint8_t dir, int32_t speed, double distance);
double calculate_circle(double distance);
void set_motor_speed(uint16_t speed);
void linearMovement(Motor *motor1, Motor *motor2, Motor *motor3, Motor *motor4, uint8_t dir, double distance, int max_speed, int acceleration_steps);
int  move_main();
#endif // MOVE_H