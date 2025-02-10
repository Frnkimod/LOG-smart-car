// check_line.c
// Author: Init
// Date: 2025-02-09
#include "check_line.h"
float um=0.618f;//设定标准比例系数
int32_t ADJ=30;//车身调整所需时间
// Your C functions and implementation go here
void angle_check(int mode)//角度校验
{
    if(mode==0)//找不到边界线
    {
        con_motion(60, 100, 2, ADJ);//向右移动
    }
    if(mode==1)//(找的到边界线)
    {
        if(BOUNDARY_RATE(1)<BOUNDARY_RATE(2))
        {
            con_motion(60,300,4,ADJ);//车身偏右，原地逆时针旋转调整
        }
        else if(BOUNDARY_RATE(1)>BOUNDARY_RATE(2))
            con_motion(60,300,5,ADJ);//车身偏左，原地顺时针旋转调整
    }
}
void pos_check(int mode)//车身距位置校验
{
    if(mode==0)//找不到边界线
    {
        con_motion(60, 100, 2, ADJ);//向右移动
    }
    if(mode==1)//(找的到边界线)
    {
        if(BOUNDARY_RATE(1)==BOUNDARY_RATE(2))
        {
            if(BOUNDARY_RATE(1)<um-0.1)//车身距离边界系数偏小
            {
                con_motion(60,100,2,ADJ);//车身向右移动
            }
            else if(BOUNDARY_RATE(1)>um+0.1)//车身距离边界系数偏大
            {
                con_motion(60,100,3,ADJ);//车身向左移动
            }
            else if(um-0.1<=BOUNDARY_RATE(1)<=um+0.1)
            {
                con_motion(60,5151,0,ADJ) ; //车身符合边界距离，向前移动
            }
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
float BOUNDARY_RATE(int flag)//车身边距比例
{
    if(flag==1)
    {

        return BOUNDARY_VALUE[0]/BOUNDARY_VALUE[2];
    }
    else if(flag==0)
    {
        return BOUNDARY_VALUE[1]/BOUNDARY_VALUE[3];
    }

}

void car_in_Init()//小车进场
{
    TT_motion(60,0,0);
    angle_check(1);
    pos_check(1);
}

