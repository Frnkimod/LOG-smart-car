// Servos.h
// Author: Franki
// Date: 2025-02-13

#ifndef SERVOS_H
#define SERVOS_H
#include "../BSP_conf.h"
typedef struct {
    gpio_Conf dev;//设备IO口信息
    int32_t angle;//转角(°)
}Servos;


extern Servos turntable;
// Your function prototypes and declarations go here
void Servos_Init(void);
void Servos_PWM_OUT();
void Servos_Control();

#endif // SERVOS_H