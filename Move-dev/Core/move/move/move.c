// move.c
// Author: Dereko
// Date: 2025-02-13
#include "move.h"
void move_motion(int32_t max_speed, int32_t acceleration, int32_t action, int32_t distance)
// 控制轮子的转速、加速度、运动距离，避免急刹车
{
    static int32_t speed = 0;  // 当前轮子转速，初始为 0
    int32_t distance_travelled = 0;  // 已行驶的距离

    // **根据 action 来决定加速或减速**
    if (action == 0) {
        // **加速阶段：缓慢增加速度**
        while (distance_travelled < distance && speed < max_speed) {
            speed += acceleration;  // 每次增加加速度
            if (speed > max_speed) speed = max_speed;  // 限制最大速度
            set_motor_speed(speed);  // 设置轮子的转速
            distance_travelled += speed;  // 更新已行驶的距离
            HAL_Delay(10);  // 模拟时间流逝
        }
    }
    else if (action == 1) {
        // **减速阶段：缓慢降低速度**
        while (distance_travelled < distance && speed > 0) {
            speed -= acceleration;  // 每次减少加速度
            if (speed < 0) speed = 0;  // 限制最低速度
            set_motor_speed(speed);  // 设置轮子的转速
            distance_travelled += speed;  // 更新已行驶的距离
            HAL_Delay(10);  // 模拟时间流逝
        }
    }

    // **停止运动**
    set_motor_speed(0);  // 最终停止电机
}

// 设置电机速度的函数
void set_motor_speed(int32_t speed) {
    // 此函数用于设置轮子的转速，这里假设你有具体的电机控制代码
    // 例如，设定电机的速度
    // 此示例假设你控制的电机是通过设置某些结构体或寄存器
    RU.speed = speed;  // 假设 RU 代表右轮
    LU.speed = speed;  // 假设 LU 代表左轮
    RL.speed = speed;  // 假设 RL 代表右轮
    LL.speed = speed;  // 假设 LL 代表左轮
}

// Your C functions and implementation go here