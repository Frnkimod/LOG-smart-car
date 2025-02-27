#ifndef INC_PID_H
#define INC_PID_H
#include "../42-dev/Emm_V5.h"
#include "../Inc/usart.h"
// 定义PID控制器结构体
typedef struct {
    float Kp, Ki, Kd;  // PID参数
    float integral;    // 积分项
    float prev_error;  // 上一次误差
} PID_Controller;


void PID_Init(PID_Controller *pid, float Kp, float Ki, float Kd);
float GetSensorValue();
void PID_Angle_Check(void);
void PID_Pos_Check(void);
#endif //INC_PID_H
