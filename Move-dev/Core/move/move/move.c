// move.c
// Author: Dereko
// Date: 2025-02-13
#include "move.h"

// Your C functions and implementation go here
#include <stdint.h>
double WHEEL_CIRCUMFERENCE =235.5; // 轮子的周长 (mm)
double calculate_circle(double distance) {
    return (distance * 0.707) / WHEEL_CIRCUMFERENCE;
}
void Emm_V5ControlX(Motor *motor1,Motor *motor2,Motor *motor3,Motor *motor4, uint8_t dir, int32_t speed, double distance)
{
    int32_t angle = (int32_t)((distance / WHEEL_CIRCUMFERENCE) * 360);
    int32_t steps=(int32_t)(angle/STPE_ANGLE);
    int32_t cnt = (speed > 0) ? (60*1000000)/(speed*STPES_PER_REVOLUTION) : 0;
    //如果 speed == 0，这个计算会 除以 0，导致程序崩溃

    if (speed == 0) {
        set_motor_speed(0);
        Emm_PWM_OUT(motor3->dev.IO_Stp, 0, 0);
        return;
    }
    // 设置电机方向
    switch (dir)
    {
        case 0:
            motor1->dir=1;
            motor2->dir=0;
            motor3->dir=0;
            motor4->dir=1;
            break;
        case 4:
            motor1->dir = 1;
            motor2->dir = 1;
            motor3->dir = 1;
            motor4->dir = 1;
            break;
        case 5:
            motor1->dir= 0;
            motor2->dir= 0;
            motor3->dir= 0;
            motor4->dir= 0;
            break;
        default:
            RU.dir = LU.dir = RL.dir = LL.dir = 0;
            set_motor_speed(0); // 停止所有电机
            Emm_PWM_OUT(motor3->dev.IO_Stp,0,0);
            return;
    }

    // 计算并更新每个电机的转动圈数
    double circle = calculate_circle(distance);
    RU.circle = LU.circle = RL.circle = LL.circle = circle;
    HAL_GPIO_WritePin(motor1->dev.IO_Dir.def,
                      motor1->dev.IO_Dir.pin,
                      motor1->dir);
    HAL_GPIO_WritePin(motor2->dev.IO_Dir.def,
                      motor2->dev.IO_Dir.pin,
                      motor2->dir);
    HAL_GPIO_WritePin(motor3->dev.IO_Dir.def,
                      motor3->dev.IO_Dir.pin,
                      motor3->dir);
    HAL_GPIO_WritePin(motor4->dev.IO_Dir.def,
                      motor4->dev.IO_Dir.pin,
                      motor4->dir);
    // 产生步进信号
    Emm_PWM_OUT(motor1->dev.IO_Stp, steps, cnt);
}

void main_move(Motor *motor1,Motor *motor2,Motor *motor3,Motor *motor4) {
    // 向前 20 圈
    Emm_V5ControlX(motor1,motor2,motor3,motor4
                   , 0, 20, 27000);  // 向前移动 20 圈
    HAL_Delay(5000);

    // 到扫码区
    Emm_V5ControlX(motor1,motor2,motor3,motor4
                   , 0, 20, 31000);  // 再次向前 20 圈
    HAL_Delay(5000);

    // 到物料区夹取物料
    Emm_V5ControlX(motor1,motor2,motor3,motor4
                   , 0, 20, 15000);  // 向前移动 10000 圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
                   , 4, 20, 11100);     // 左转 90°
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
                   , 0, 20, 73000);     // 向前移动 50 圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
                   , 4, 20, 11100);  // 左转 90°
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
                   , 0, 20, 32500);  // 向前移动 30 圈
    HAL_Delay(5000);

    // 到加工区放置
    Emm_V5ControlX(motor1,motor2,motor3,motor4
                   , 4, 20, 22200);  // 掉头（向后 20 圈）
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
    ,0, 20, 32500);  // 向前移动 30 圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
                   , 5, 20, 11100);  // 右转 90°
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
                   , 0, 20, 34000);  // 向前移动 20 圈
    HAL_Delay(5000);
    // 到暂存区放置
    Emm_V5ControlX(motor1,motor2,motor3,motor4
                   , 0, 20, 36500);  // 向前移动 30 圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
                   , 5, 20, 11100);  // 右转 90°
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
                   , 0, 20, 16500);  // 向前移动 10 圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
            , 4, 20, 22200);  // 掉头20 圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
            , 0, 20, 16500);  // 向前移动10圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
            , 4, 20, 11100);  // 向左转10圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
            , 0, 20, 73000);  // 向前50圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
            , 4, 20, 11100);  // 左转10圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
            , 0, 20, 33000);  // 前进30圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
            , 4, 20, 22000);  // 掉头20圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
            , 0, 20, 33000);  // 直行30圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
            , 5, 20, 11000);  // 右转10圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
            , 0, 20, 34000);  // 直行30圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
            , 0, 20, 34000);  // 直行20圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
            , 5, 20, 11000);  // 右转10圈
    HAL_Delay(5000);
    Emm_V5ControlX(motor1,motor2,motor3,motor4
            , 0, 20, 62000);  // 直行40圈
    HAL_Delay(5000);


    // 回到启停区
    set_motor_speed(0);  // 停止所有电机
}

void set_motor_speed(uint16_t speed)
{
RU.speed = speed;  // 假设 RU 代表右轮
LU.speed = speed;  // 假设 LU 代表左轮
RL.speed = speed;  // 假设 RL 代表右轮
LL.speed = speed;  // 假设 LL 代表左轮
}