// Control.c
// Author: Dereko
// Date: 2025-01-10
#include "Control.h"



void con_init()
{
}
/*
 * up: dir->0
 * down: dir->1
 * left: dir->2
 * right：dir->3
 * cw:dir->4
 * ccw:dir->5
 * */
void con_motion(int32_t speed,uint32_t dir,uint32_t time)
{
    RU.speed=speed;
    LU.speed=speed;
    RL.speed=speed;
    LL.speed=speed;
    RU.delay_motion=time;
    LU.delay_motion=time;
    RL.delay_motion=time;
    LL.delay_motion=time;

    switch (dir) {
        case 0:
            RU.dir=0;
            LU.dir=1;
            RL.dir=0;
            LL.dir=1;//前进
            break;
        case 1:
            RU.dir=1;
            LU.dir=0;
            RL.dir=1;
            LL.dir=0;
            break;//后退

        case 2:
            RU.dir=0;
            LU.dir=0;
            RL.dir=1;
            LL.dir=1;//右
            break;
        case 3:
            RU.dir=1;
            LU.dir=1;
            RL.dir=0;
            LL.dir=0;//左
            break;
        case 4:
            RU.dir=1;
            LU.dir=1;
            RL.dir=1;
            LL.dir=1;//原地逆时针
            break;
        case 5:
            RU.dir=0;
            LU.dir=0;
            RL.dir=0;
            LL.dir=0;//原地顺时针
            break;
    }


}
