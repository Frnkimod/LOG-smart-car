// move.c
// Author: Dereko
// Date: 2025-02-13
#include "move.h"

// Your C functions and implementation go here
#include <stdint.h>
//WHEEL_CIRCUMFERENCE 235.5   轮子的周长 (mm)
double calculate_circle(double distance) {
    return distance * 1.414 / 2;
}
void move_motion(int32_t dir, double distance){
    switch (dir)
    {
        case 0:

            break;
        case 4:

            break;
        case 5:

            break;
        default:
            // 默认情况下，设置所有电机速度为0，停止运动
            RU.dir = LU.dir = RL.dir = LL.dir = 0;
            set_motor_speed(0);  // 停止所有电机
            break;
    }

//    RU.circle=calculate_circle(distance);
//    LU.circle=calculate_circle(distance);
//    RL.circle=calculate_circle(distance);
//    LL.circle=calculate_circle(distance);
}
void main_move() {
    move_motion(0, 20);  // 向前 20 圈
    HAL_Delay(100);
    //到扫码区
    move_motion(0, 20);  // 向前 20 圈
    HAL_Delay(100);
    /***
     *
     *
     * ***/
//    while (pos_check_flag)
//    {
//
//    }
//     while(taking_check_flag)
//     {
//      }
    //到物料区夹取物料
    move_motion(0, 10);  // 向前 10 圈
    HAL_Delay(10);
    move_motion(4, 10);  // 左转 90°
    HAL_Delay(10);
    move_motion(0, 50);  // 向前 50 圈
    HAL_Delay(10);
    move_motion(4, 10);  // 左转 90°
    HAL_Delay(10);
    move_motion(0, 30);  // 向前 30 圈
//     while (pos_check_flag)
//    {
//    }
//     while(putting_check_flag)
//     {
//      }
//     while(taking_check_flag)
//     {
//      }
    // 到加工区放置
    move_motion(4, 20);  // 掉头
    HAL_Delay(10);
    move_motion(0, 30);  // 向前 30 圈
    HAL_Delay(10);
    move_motion(5, 10);  // 右转 90°
    HAL_Delay(10);
    move_motion(0, 20);  // 向前 20 圈
//     while (pos_check_flag)
//    {
//    }
//     while(putting_check_flag)
//     {
//      }
    // 到暂存区放置
    move_motion(0, 30);  // 向前 30 圈
    HAL_Delay(10);
    move_motion(5, 10);  // 右转 90°
    HAL_Delay(10);
    move_motion(0, 10);  // 向前 10 圈
//    while (pos_check_flag)
//    {
//
//    }
//     while(taking_check_flag)
//     {
//      }
    // 到物料区夹取物料
    move_motion(4, 20);  // 掉头
    HAL_Delay(10);
    move_motion(0, 10);  // 向前 10 圈
    HAL_Delay(10);
    move_motion(4, 10);  // 左转 90°
    HAL_Delay(10);
    move_motion(0, 50);  // 向前 50 圈
    HAL_Delay(10);
    move_motion(4, 10);  // 左转 90°
    HAL_Delay(10);
    move_motion(0, 30);  // 向前 30 圈
//    while (pos_check_flag)
//    {
//
//    }
//     while(putting_check_flag)
//     {
//      }
//     while(taking_check_flag)
//     {
//      }
    // 到加工区放置物料
    move_motion(4, 20);  // 掉头
    move_motion(0, 30);  // 向前 30 圈
    HAL_Delay(10);
    move_motion(5, 10);  // 右转 90°
    HAL_Delay(10);
    move_motion(0, 20);  // 向前 20 圈
//    while (pos_check_flag)
//    {
//
//    }
//     while(putting_check_flag)
//     {
//      }
    // 到暂存区放置物料
    move_motion(0, 30);  // 向前 30 圈
    HAL_Delay(10);
    move_motion(5, 10);  // 右转 90°
    HAL_Delay(10);
    move_motion(0, 50);  // 向前 50 圈
    set_motor_speed(0);
    //回到启停区
}
void set_motor_speed(uint16_t speed)
{
RU.speed = speed;  // 假设 RU 代表右轮
LU.speed = speed;  // 假设 LU 代表左轮
RL.speed = speed;  // 假设 RL 代表右轮
LL.speed = speed;  // 假设 LL 代表左轮
}