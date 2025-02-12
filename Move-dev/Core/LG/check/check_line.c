// check_line.c
// Author: Init
// Date: 2025-02-09
#include "check_line.h"
float um=0.618f;//设定标准比例系数
// Your C functions and implementation go here
void angle_check(int mode) // 角度校验
{
    int values[] = {20, 40, 60};

    if (mode == 0) { // 找不到边界线，向右移动
        for (int i = 0; i < 3; i++) {
            con_motion(values[i], 2, 10);
        }
    }
    else if (mode == 1) { // 找得到边界线
        float rate1 = BOUNDARY_RATE(1);
        float rate2 = BOUNDARY_RATE(2);
        int direction = (rate1 < rate2) ? 4 : 5; // 4: 逆时针旋转, 5: 顺时针旋转

        if (rate1 != rate2) {
            for (int i = 0; i < 3; i++) {
                con_motion(values[i], direction, 10);
            }
        }
    }
}

void pos_check(int mode) // 车身距位置校验
{
    int values[] = {20, 40, 60};

    if (mode == 0) { // 找不到边界线，向右移动
        for (int i = 0; i < 3; i++) {
            con_motion(values[i], 3, 10);
        }
    }
    else if (mode == 1) { // 找得到边界线
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
    int values[][3] = {
            {60, 40, 20}, // need == 0（缓减速）
            {20, 40, 60}, // need == 1（缓加速）
            {40, 20,  0}  // need == 2（缓停止）
    };

    if (need >= 0 && need <= 2) {
        for (int i = 0; i < 3; i++) {
            con_motion(values[need][i], 0, 10);
        }
    }
}

void check_line_Init()//内部参数初始化
{
    for (int i = 0; i < sizeof(BOUNDARY_VALUE); i++) {
        BOUNDARY_VALUE[i]=0;
    }
    for (int i = 0; i < sizeof (QR_NUM); i++) {
        QR_NUM[i]=0;
    }
}
void TT_motion(int32_t speed,int16_t dir,int32_t angle)//控制机械臂运动
{
  TT.speed=speed;
  TT.dir=dir;
  TT.angle=angle;
}
float BOUNDARY_RATE(int flag) // 车身边距比例
{
    return BOUNDARY_VALUE[flag ? 0 : 1] / BOUNDARY_VALUE[flag ? 2 : 3];
    //flag == 1 时取 [0] / [2]，否则取 [1] / [3]
}
void car_in_Init()//小车进场
{
    TT_motion(60,0,0);
    angle_check(1);
    pos_check(1);
}

