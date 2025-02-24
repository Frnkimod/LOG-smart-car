// check_line.c
// Author: Init
// Date: 2025-02-09
#include "check_line.h"

float um=0.618f;//设定标准比例系数
float BOUNDARY_VALUE[4];
// Your C functions and implementation go here
void angle_check(int angle_mode) // 角度校验
{
    int values[] = {10, 15, 20};

    if (angle_mode == 0) { // 找不到边界线，向右移动
        for (int i = 0; i < 3; i++) {
            con_motion(values[i], 2, 1000);
        }
    }
    else if (angle_mode == 1) { // 找得到边界线
        float rate1 = BOUNDARY_RATE(1);
        float rate2 = BOUNDARY_RATE(2);
        int direction = (rate1 < rate2) ? 4 : 5; // 4: 逆时针旋转, 5: 顺时针旋转

        if (rate1 != rate2) {
            for (int i = 0; i < 3; i++) {
                con_motion(values[i], direction, 1000);
            }
        }
    }
}

void pos_check(int pos_mode) // 车身距位置校验
{
    int values[] = {10, 15, 20};

    if (pos_mode == 0) { // 找不到边界线，向右移动
        for (int i = 0; i < 3; i++) {
            con_motion(values[i], 3, 1000);
        }
    }
    else if (pos_mode == 1) { // 找得到边界线
        float rate1 = BOUNDARY_RATE(1);
        float rate2 = BOUNDARY_RATE(2);

        if (rate1 == rate2) {
            int direction = (rate1 < um - 0.1) ? 2 : (rate1 > um + 0.1) ? 3 : -1;

            if (direction != -1) {
                for (int i = 0; i < 3; i++) {
                    con_motion(values[i], direction, 10);
                }
            }
            else { // 车身在正确位置，向前直行
                ac_motion(1);
            }
        }
    }
}
void ac_motion(int need) // 分级调速，加减速与停止
{
    int values[][3] =
     {
            {20, 15, 10}, // need == 0（缓减速）
            {10, 15, 20}, // need == 1（缓加速）
            {20, 10,  0}  // need == 2（缓停止）
     };

    if (need >= 0 && need <= 2)
    {
        for (int i = 0; i < 3; i++)
        {
            con_motion(values[need][i],0,1000);
        }
    }
}

void check_line_Init()//内部参数初始化
{
    for (int i = 0; i < sizeof(BOUNDARY_VALUE); i++) {
        BOUNDARY_VALUE[i]=0;
    }

}
void TT_motion(Motor *tt,int32_t speed,int16_t dir,int32_t angle)//控制机械臂运动
{
    int32_t steps = (int32_t)(angle*3200/360.0); // 将角度转换为步数
    int32_t cnt = (speed > 0) ? (60 * 1000000) / (speed * STPES_PER_REVOLUTION) : 0; // 计算PWM周期
    TT.speed=speed;
    TT.dir=dir;
    HAL_GPIO_WritePin(tt->dev.IO_Dir.def, tt->dev.IO_Dir.pin, tt->dir);
    Emm_PWM_OUT(tt->dev.IO_Stp, steps, cnt);
}
float BOUNDARY_RATE(int flag) // 车身边距比例
{
    return BOUNDARY_VALUE[flag ? 0 : 1] / BOUNDARY_VALUE[flag ? 2 : 3];
   // flag == 1 时取 [0] / [2]，否则取 [1] / [3]
}
void car_in_Init()//小车进场
{


    con_motion(60,3,50);
    angle_check(1);
    pos_check(1);
}

