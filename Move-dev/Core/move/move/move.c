// move.c
// Author: Dereko
// Date: 2025-02-13
#include "move.h"
#include <stdint.h>
// Your C functions and implementation go here
#include <stdint.h>

#define WHEEL_CIRCUMFERENCE 235.5  // 轮子的周长 (mm)
void move_motion(int32_t dir, int32_t circle){
    switch (dir)
    {
        case 0:
            RU.dir=0;
            LU.dir=1;
            RL.dir=0;
            LL.dir=1;
            break;
        case 4:
            RU.dir=1;
            LU.dir=1;
            RL.dir=1;
            LL.dir=1;
            break;
        case 5:
            RU.dir=0;
            LU.dir=0;
            RL.dir=0;
            LL.dir=0;
            break;
    }
    RU.circle=circle;
    LU.circle=circle;
    RL.circle=circle;
    LL.circle=circle;
}
void main_move() {
    move_motion(0, 20);  // 向前 20 圈
    HAL_Delay(100);
    //到扫码区
    move_motion(0, 20);  // 向前 20 圈
    HAL_Delay(100);
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
    HAL_Delay(100);
    // 到加工区放置
    move_motion(4, 20);  // 掉头
    HAL_Delay(10);
    move_motion(0, 30);  // 向前 30 圈
    HAL_Delay(10);
    move_motion(5, 10);  // 右转 90°
    HAL_Delay(10);
    move_motion(0, 20);  // 向前 20 圈
    HAL_Delay(100);
    // 到暂存区放置
    move_motion(0, 30);  // 向前 30 圈
    HAL_Delay(10);
    move_motion(5, 10);  // 右转 90°
    HAL_Delay(10);
    move_motion(0, 10);  // 向前 10 圈
    HAL_Delay(100);
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
    HAL_Delay(100);
    // 到加工区放置物料
    move_motion(4, 20);  // 掉头
    move_motion(0, 30);  // 向前 30 圈
    HAL_Delay(10);
    move_motion(5, 10);  // 右转 90°
    HAL_Delay(10);
    move_motion(0, 20);  // 向前 20 圈
    HAL_Delay(100);
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