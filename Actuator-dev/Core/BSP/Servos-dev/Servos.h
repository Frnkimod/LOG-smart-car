// Servos.h
// Author: Franki
// Date: 2025-02-13

#ifndef SERVOS_H
#define SERVOS_H

#define T_X 330
#define T_Y 230
#define T_R 145



#include "../BSP_conf.h"
typedef struct {
    gpio_Conf dev;//设备IO口信息
    int32_t angle;//转角(°)
}Servos;


extern Servos turntable;
// Your function prototypes and declarations go here
void Servos_Init(void);
void Servo_SetAngle_270_1(uint16_t angle);//翻转舵机
void Servo_SetAngle_270_2(uint16_t angle);//转盘舵机
void Servo_SetAngle_180(uint16_t angle);
void control_servo(int direction);
#endif // SERVOS_H