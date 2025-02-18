// move.c
// Author: Dereko
// Date: 2025-02-13
#include "move.h"

// Your C functions and implementation go here
#include <stdint.h>

// 定义轮子的周长 (单位: mm)
double WHEEL_CIRCUMFERENCE = 235.5;

// 计算运动所需的圈数
double calculate_circle(double distance) {
    return (distance * 0.707) / WHEEL_CIRCUMFERENCE;
}

// 控制电机运动的函数
void Emm_V5ControlX(Motor *motor1, Motor *motor2, Motor *motor3, Motor *motor4, uint8_t dir, int32_t speed, double distance) {
    if (speed == 0) { // 如果速度为0，停止电机
        set_motor_speed(0);
        Emm_PWM_OUT(motor3->dev.IO_Stp, 0, 0);
        return;
    }
    int32_t angle = (int32_t)((distance / WHEEL_CIRCUMFERENCE) * 360); // 将距离转换为角度
    int32_t steps = (int32_t)(angle / STPE_ANGLE); // 将角度转换为步数
    int32_t cnt = (speed > 0) ? (60 * 1000000) / (speed * STPES_PER_REVOLUTION) : 0; // 计算PWM周期



    // 设置电机方向
    switch (dir) {
        case 0: // 直行
            motor1->dir = 1;
            motor2->dir = 0;
            motor3->dir = 0;
            motor4->dir = 1;
            break;
        case 4: // 后退
            motor1->dir = 1;
            motor2->dir = 1;
            motor3->dir = 1;
            motor4->dir = 1;
            break;
        case 5: // 前进
            motor1->dir = 0;
            motor2->dir = 0;
            motor3->dir = 0;
            motor4->dir = 0;
            break;
        default: // 默认停止
            motor1->dir = motor2->dir = motor3->dir = motor4->dir = 0;
            set_motor_speed(0); // 停止所有电机
            Emm_PWM_OUT(motor1->dev.IO_Stp, 0, 0);
            return;
    }

    // 计算并更新每个电机的转动圈数
    double circle = calculate_circle(distance);
    motor1->circle = motor2->circle = motor3->circle = motor4->circle = circle;

    // 设置电机方向引脚
    HAL_GPIO_WritePin(motor1->dev.IO_Dir.def, motor1->dev.IO_Dir.pin, motor1->dir);
    HAL_GPIO_WritePin(motor2->dev.IO_Dir.def, motor2->dev.IO_Dir.pin, motor2->dir);
    HAL_GPIO_WritePin(motor3->dev.IO_Dir.def, motor3->dev.IO_Dir.pin, motor3->dir);
    HAL_GPIO_WritePin(motor4->dev.IO_Dir.def, motor4->dev.IO_Dir.pin, motor4->dir);

    // 产生步进信号
    Emm_PWM_OUT(motor1->dev.IO_Stp, steps, cnt);
}

// 线性加速和减速函数
void linearMovement(Motor *motor1, Motor *motor2, Motor *motor3, Motor *motor4, uint8_t dir, double distance, int max_speed, int acceleration_steps) {
    int current_speed = 0; // 当前速度
    int step_size = max_speed / acceleration_steps; // 每步速度变化量

    // 加速阶段
    for (int i = 1; i < max_speed; i++) {
        current_speed += step_size; // 逐步增加速度
        Emm_V5ControlX(motor1, motor2, motor3, motor4, dir, current_speed, distance / acceleration_steps); // 调用电机控制函数
        //HAL_Delay(10);
    }

    // 保持最大速度一段时间
    Emm_V5ControlX(motor1, motor2, motor3, motor4, dir, current_speed, distance / acceleration_steps);
    // 减速阶段
    for (int i = max_speed; i > 1; i--) {
        current_speed -= step_size; // 逐步减少速度
        Emm_V5ControlX(motor1, motor2, motor3, motor4, dir, current_speed, distance / acceleration_steps); // 调用电机控制函数
    }
    // 停止电机
    Emm_V5ControlX(motor1, motor2, motor3, motor4, dir, 0, 0);
}
// 主程序
int move_main() {
    // 设置最大速度和加速/减速步骤数
    int max_speed = 120; // 最大速度
    int acceleration_steps = 3; // 加速和减速的步数
    linearMovement(&RU, &LU, &RL, &LL, 0, 275, max_speed, acceleration_steps);
    HAL_Delay(10);
    // 到扫码区扫码
    linearMovement(&RU, &LU, &RL, &LL, 0, 415, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 到物料区夹取物料
    linearMovement(&RU, &LU, &RL, &LL, 0, 190, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 向前到拐角
    linearMovement(&RU, &LU, &RL, &LL, 4, 156, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 左转
    linearMovement(&RU, &LU, &RL, &LL, 0, 890, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 向前到拐角
    linearMovement(&RU, &LU, &RL, &LL, 4, 151, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 左转
    linearMovement(&RU, &LU, &RL, &LL, 0, 405, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 到加工区
    linearMovement(&RU, &LU, &RL, &LL, 4, 290, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 调头
    linearMovement(&RU, &LU, &RL, &LL, 0, 430, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 向前到拐角
    linearMovement(&RU, &LU, &RL, &LL, 5, 140, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 右转
    linearMovement(&RU, &LU, &RL, &LL, 0, 410, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 向前到暂存区
    linearMovement(&RU, &LU, &RL, &LL, 0, 475, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 向前到拐角
    linearMovement(&RU, &LU, &RL, &LL, 5, 140, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 右转
    linearMovement(&RU, &LU, &RL, &LL, 0, 158, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 向前到物料区
    linearMovement(&RU, &LU, &RL, &LL, 4, 283, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 调头
    linearMovement(&RU, &LU, &RL, &LL, 0, 170, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 向前到拐角
    linearMovement(&RU, &LU, &RL, &LL, 4, 150, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 左转
    linearMovement(&RU, &LU, &RL, &LL, 0, 885, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 向前到拐角
    linearMovement(&RU, &LU, &RL, &LL, 4, 155, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 左转
    linearMovement(&RU, &LU, &RL, &LL, 0, 415, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 向前到加工区
    linearMovement(&RU, &LU, &RL, &LL, 4, 285, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 调头
    linearMovement(&RU, &LU, &RL, &LL, 0, 430, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 向前到拐角
    linearMovement(&RU, &LU, &RL, &LL, 5, 151, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 右转
    linearMovement(&RU, &LU, &RL, &LL, 0, 415, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 向前到暂存区
    linearMovement(&RU, &LU, &RL, &LL, 0, 490, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 向前到拐角
    linearMovement(&RU, &LU, &RL, &LL, 5, 148, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 右转
    linearMovement(&RU, &LU, &RL, &LL, 0, 850, max_speed, acceleration_steps);
    HAL_Delay(10);

    // 停止所有电机
    set_motor_speed(0);

    return 0;
}

// 设置电机速度的函数
void set_motor_speed(uint16_t speed) {
    RU.speed = speed;  // 假设 RU 代表右轮
    LU.speed = speed;  // 假设 LU 代表左轮
    RL.speed = speed;  // 假设 RL 代表右轮
    LL.speed = speed;  // 假设 LL 代表左轮
}


//void main_move(Motor *motor1,Motor *motor2,Motor *motor3,Motor *motor4) {
//    // 小车起步向前
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 3375);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 3375);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 3375);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 3375);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 3375);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 3375);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 3375);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 3375);
//    HAL_Delay(1000);
//    // 到扫码区扫码
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 3906);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 3906);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 3906);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 3906);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 3906);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 3906);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 3906);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 3906);
//    HAL_Delay(1000);
//    // 到物料区夹取物料
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 1875);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 1875);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 1875);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 1875);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 1875);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 1875);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 1875);
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 1875);
//    HAL_Delay(1000);
//    //向前到拐角
//    Emm_V5ControlX(motor1, motor2, motor3, motor4, 4, 10, 1875);
//    Emm_V5ControlX(motor1, motor2, motor3, motor4, 4, 20, 1875);
//    Emm_V5ControlX(motor1, motor2, motor3, motor4, 4, 40, 1875);
//    Emm_V5ControlX(motor1, motor2, motor3, motor4, 4, 60, 1875);
//    Emm_V5ControlX(motor1, motor2, motor3, motor4, 4, 60, 1875);
//    Emm_V5ControlX(motor1, motor2, motor3, motor4, 4, 40, 1875);
//    Emm_V5ControlX(motor1, motor2, motor3, motor4, 4, 20, 1875);
//    Emm_V5ControlX(motor1, motor2, motor3, motor4, 4, 10, 1875);
//    HAL_Delay(1000);
//    //左转
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 9125);   // 速度 5, 距离 9125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 9125);  // 速度 10, 距离 9125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 9125);  // 速度 15, 距离 9125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 9125);  // 速度 20, 距离 9125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 9125);  // 速度 20, 距离 9125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 9125);  // 速度 15, 距离 9125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 9125);  // 速度 10, 距离 9125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 9125);   // 速度 5, 距离 9125
//    HAL_Delay(1000);
//    //向前到拐角
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 10, 1875);   // 速度 5, 距离 1875
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 20, 1875);  // 速度 10, 距离 1875
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 40, 1875);  // 速度 15, 距离 1875
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 60, 1875);  // 速度 20, 距离 1875
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 60, 1875);  // 速度 20, 距离 1875
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 40, 1875);  // 速度 15, 距离 1875
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 20, 1875);  // 速度 10, 距离 1875
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 10, 1875);   // 速度 5, 距离 1875
//    HAL_Delay(1000);
//    //左转
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 4062);   // 速度 10, 距离 4062
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 4062);   // 速度 20, 距离 4062
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 4062);   // 速度 40, 距离 4062
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 4062);   // 速度 60, 距离 4062
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 4062);   // 速度 60, 距离 4062
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 4062);   // 速度 40, 距离 4062
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 4062);   // 速度 20, 距离 4062
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 4062);   // 速度 10, 距离 4062
//    HAL_Delay(1000);
//    // 到加工区
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 10, 2775);  // 掉头（向后 20 圈）
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 20, 2775);  // 掉头（向后 20 圈）
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 40, 2775);  // 掉头（向后 20 圈）
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 60, 2775);  // 掉头（向后 20 圈）
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 60, 2775);  // 掉头（向后 20 圈）
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 40, 2775);  // 掉头（向后 20 圈）
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 20, 2775);  // 掉头（向后 20 圈）
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 10, 2775);  // 掉头（向后 20 圈）
//    HAL_Delay(1000);
//    //调头
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 4062);  // 向前移动 30 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 4062);  // 向前移动 30 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 4062);  // 向前移动 30 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 4062);  // 向前移动 30 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 4062);  // 向前移动 30 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 4062);  // 向前移动 30 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 4062);  // 向前移动 30 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 4062);  // 向前移动 30 圈
//    HAL_Delay(1000);
////向前到拐角
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 10, 1387);  // 右转 90°
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 20, 1387);  // 右转 90°
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 40, 1387);  // 右转 90°
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 60, 1387);  // 右转 90°
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 60, 1387);  // 右转 90°
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 40, 1387);  // 右转 90°
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 20, 1387);  // 右转 90°
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 10, 1387);  // 右转 90°
//    HAL_Delay(1000);
////右转
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 4250);  // 向前移动 20 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 4250);  // 向前移动 20 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 4250);  // 向前移动 20 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 4250);  // 向前移动 20 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 4250);  // 向前移动 20 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 4250);  // 向前移动 20 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 4250);  // 向前移动 20 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 4250);  // 向前移动 20 圈
//    HAL_Delay(1000);
//    // 向前到暂存区
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 4562);  // 向前移动 30 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 4562);  // 向前移动 30 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 4562);  // 向前移动 30 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 4562);  // 向前移动 30 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 4562);  // 向前移动 30 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 4562);  // 向前移动 30 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 4562);  // 向前移动 30 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 4562);  // 向前移动 30 圈
//    HAL_Delay(1000);
////向前到拐角
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 10, 1387);  // 右转 90°
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 20, 1387);  // 右转 90°
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 40, 1387);  // 右转 90°
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 60, 1387);  // 右转 90°
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 60, 1387);  // 右转 90°
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 40, 1387);  // 右转 90°
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 20, 1387);  // 右转 90°
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 10, 1387);  // 右转 90°
//    HAL_Delay(1000);
////右转
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 2062);  // 向前移动 10 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 2062);  // 向前移动 10 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 2062);  // 向前移动 10 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 2062);  // 向前移动 10 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 2062);  // 向前移动 10 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 2062);  // 向前移动 10 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 2062);  // 向前移动 10 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 2062);  // 向前移动 10 圈
//    HAL_Delay(1000);
////向前到物料区
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 10, 2775);  // 向后 20 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 20, 2775);  // 向后 20 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 40, 2775);  // 向后 20 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 60, 2775);  // 向后 20 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 60, 2775);  // 向后 20 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 40, 2775);  // 向后 20 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 20, 2775);  // 向后 20 圈
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 10, 2775);  // 向后 20 圈
//    HAL_Delay(1000);
////调头
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 2062);  // 速度 10, 距离 2062
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 2062);  // 速度 20, 距离 2062
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 2062);  // 速度 40, 距离 2062
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 2062);  // 速度 60, 距离 2062
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 2062);  // 速度 60, 距离 2062
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 2062);  // 速度 40, 距离 2062
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 2062);  // 速度 20, 距离 2062
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 2062);  // 速度 10, 距离 2062
//    HAL_Delay(1000);
////向前到拐角
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 10, 1387);  // 速度 10, 距离 1387
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 20, 1387);  // 速度 20, 距离 1387
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 40, 1387);  // 速度 40, 距离 1387
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 60, 1387);  // 速度 60, 距离 1387
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 60, 1387);  // 速度 60, 距离 1387
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 40, 1387);  // 速度 40, 距离 1387
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 20, 1387);  // 速度 20, 距离 1387
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 10, 1387);  // 速度 10, 距离 1387
//    HAL_Delay(1000);
////左转
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 9125);  // 速度 10, 距离 9125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 9125);  // 速度 20, 距离 9125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 9125);  // 速度 40, 距离 9125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 9125);  // 速度 60, 距离 9125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 9125);  // 速度 60, 距离 9125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 9125);  // 速度 40, 距离 9125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 9125);  // 速度 20, 距离 9125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 9125);  // 速度 10, 距离 9125
//    HAL_Delay(1000);
////向前到拐角
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 10, 1387);  // 速度 10, 距离 1387
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 20, 1387);  // 速度 20, 距离 1387
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 40, 1387);  // 速度 40, 距离 1387
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 60, 1387);  // 速度 60, 距离 1387
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 60, 1387);  // 速度 60, 距离 1387
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 40, 1387);  // 速度 40, 距离 1387
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 20, 1387);  // 速度 20, 距离 1387
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 10, 1387);  // 速度 10, 距离 1387
//    HAL_Delay(1000);
////左转
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 4125);  // 速度 10, 距离 4125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 4125);  // 速度 20, 距离 4125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 4125);  // 速度 40, 距离 4125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 4125);  // 速度 60, 距离 4125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 4125);  // 速度 60, 距离 4125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 4125);  // 速度 40, 距离 4125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 4125);  // 速度 20, 距离 4125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 4125);  // 速度 10, 距离 4125
//    HAL_Delay(1000);
//
////向前到加工区
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 10, 2750);  // 速度 10, 距离 2750
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 20, 2750);  // 速度 20, 距离 2750
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 40, 2750);  // 速度 40, 距离 2750
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 60, 2750);  // 速度 60, 距离 2750
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 60, 2750);  // 速度 60, 距离 2750
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 40, 2750);  // 速度 40, 距离 2750
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 20, 2750);  // 速度 20, 距离 2750
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 4, 10, 2750);  // 速度 10, 距离 2750
//    HAL_Delay(1000);
//
////调头
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 4125);   // 速度 10, 距离 4125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 4125);   // 速度 20, 距离 4125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 4125);   // 速度 40, 距离 4125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 4125);   // 速度 60, 距离 4125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 4125);   // 速度 60, 距离 4125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 4125);   // 速度 40, 距离 4125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 4125);   // 速度 20, 距离 4125
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 4125);   // 速度 10, 距离 4125
//    HAL_Delay(1000);
////向前到拐角
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 10, 1375);   // 速度 10, 距离 1375
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 20, 1375);   // 速度 20, 距离 1375
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 40, 1375);   // 速度 40, 距离 1375
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 60, 1375);   // 速度 60, 距离 1375
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 60, 1375);   // 速度 60, 距离 1375
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 40, 1375);   // 速度 40, 距离 1375
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 20, 1375);   // 速度 20, 距离 1375
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 10, 1375);   // 速度 10, 距离 1375
//    HAL_Delay(1000);
////右转
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 4250);   // 速度 10, 距离 4250
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 4250);   // 速度 20, 距离 4250
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 4250);   // 速度 40, 距离 4250
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 4250);   // 速度 60, 距离 4250
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 4250);   // 速度 60, 距离 4250
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 4250);   // 速度 40, 距离 4250
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 4250);   // 速度 20, 距离 4250
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 4250);   // 速度 10, 距离 4250
//    HAL_Delay(1000);
////向前到暂存区
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 4250);   // 速度 10, 距离 4250
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 4250);   // 速度 20, 距离 4250
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 4250);   // 速度 40, 距离 4250
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 4250);   // 速度 60, 距离 4250
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 4250);   // 速度 60, 距离 4250
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 4250);   // 速度 40, 距离 4250
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 4250);   // 速度 20, 距离 4250
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 4250);   // 速度 10, 距离 4250
//    HAL_Delay(1000);
////向前到拐角
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 10, 1375);   // 速度 10, 距离 1375
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 20, 1375);   // 速度 20, 距离 1375
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 40, 1375);   // 速度 40, 距离 1375
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 60, 1375);   // 速度 60, 距离 1375
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 60, 1375);   // 速度 60, 距离 1375
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 40, 1375);   // 速度 40, 距离 1375
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 20, 1375);   // 速度 20, 距离 1375
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 5, 10, 1375);   // 速度 10, 距离 1375
//    HAL_Delay(1000);
//    //右转
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 7750);   // 速度 10, 距离 7750
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 7750);   // 速度 20, 距离 7750
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 7750);   // 速度 40, 距离 7750
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 7750);   // 速度 60, 距离 7750
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 60, 7750);   // 速度 60, 距离 7750
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 40, 7750);   // 速度 40, 距离 7750
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 20, 7750);   // 速度 20, 距离 7750
//    Emm_V5ControlX(motor1,motor2,motor3,motor4, 0, 10, 7750);   // 速度 10, 距离 7750
//    HAL_Delay(1000);
//    // 回到启停区
//    set_motor_speed(0);
//    // 停止所有电机
//}

