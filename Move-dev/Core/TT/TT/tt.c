// tt.c
// Author: Dereko
// Date: 2025-02-13
#include "tt.h"
// Your C functions and implementation go here
void smooth_motion(int32_t max_speed, int32_t acceleration, int32_t total_distance,
                   int32_t angle, int32_t dir, float load, int32_t target_position)
// 控制机械臂的启动和停止,速度，加速度，距离，角度，方向，负载，目标位置
{
    int32_t speed = 0, pos = 0;  // 当前速度 speed，当前位置 pos
    int32_t accel_dist = 0, adjusted_max_speed = 0;

    // **计算最大可达速度，确保加速+减速距离不超过总行程**
    while (accel_dist + (adjusted_max_speed + acceleration) <= total_distance / 2) {
        adjusted_max_speed += acceleration;
        accel_dist += adjusted_max_speed;
    }

    // **确保最大速度不会超过设定值**
    if (adjusted_max_speed > max_speed) adjusted_max_speed = max_speed;

    // **负载调整：根据负载影响加速度**，负载越大，减小加速度（简单示例）
    if (load > 0.8f) {  // 假设负载大于0.8时，减小加速度，这个0.8可在小车调试中调整
        acceleration = acceleration / 2;
    }

    // **加速阶段：逐步增加速度**
    while (pos < accel_dist) {
        speed += acceleration;
        if (speed > adjusted_max_speed) speed = adjusted_max_speed;  // 限制最大速度
        set_motor_speed(speed, angle, dir);  // 传递角度和方向控制电机
        pos += speed;
        HAL_Delay(10);
        // 假设目标位置在加速阶段已经达到
        if (pos >= target_position) break;
        //添加 target_position 参数来标识机械臂的目标位置。当 pos 达到 target_position 时，我们就可以提前停止运动。
    }

    // **匀速阶段：保持最大速度**
    while (pos < total_distance - accel_dist) {
        set_motor_speed(adjusted_max_speed, angle, dir);  // 传递角度和方向控制电机
        pos += adjusted_max_speed;
        HAL_Delay(10);
        // 假设目标位置在匀速阶段已经达到
        if (pos >= target_position) break;
    }

    // **减速阶段：逐步降低速度**
    while (pos < total_distance) {
        speed -= acceleration;
        if (speed < 0) speed = 0;  // 确保速度不变负
        set_motor_speed(speed, angle, dir);  // 传递角度和方向控制电机
        pos += speed;
        HAL_Delay(10);
        // 假设目标位置在减速阶段已经达到
        if (pos >= target_position) break;
    }

    // **停止运动**
    set_motor_speed(0, angle, dir);  // 停止电机
}

// 设置电机速度，并考虑旋转方向和角度
void set_motor_speed(int32_t speed, int32_t angle, int32_t dir) {
    TT.speed = speed;

    // 方向控制：逆时针 (dir == 0) 或顺时针 (dir == 1)
    if (dir == 0) {
        TT.angle = angle;  // 顺时针转动
    } else if (dir == 1) {
        TT.angle = -angle;  // 逆时针转动，角度反向
    }
}
