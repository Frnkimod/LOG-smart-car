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
void con_motion(int32_t speed,int32_t distance,uint32_t dir,int32_t delay_motion)
{
    speed=60;
    distance=10000;
    delay_motion=30;
    switch (dir) {
        case 0:
            RU.dir=0;
            LU.dir=1;
            RL.dir=0;
            LL.dir=1;
            break;//前
        case 1:
            RU.dir=1;
            LU.dir=0;
            RL.dir=1;
            LL.dir=0;
            break;//后

        case 2:
            RU.dir=0;
            LU.dir=0;
            RL.dir=1;
            LL.dir=1;
            break;//右
        case 3:
            RU.dir=1;
            LU.dir=1;
            RL.dir=0;
            LL.dir=0;
            break;//左
        case 4:
            RU.dir=1;
            LU.dir=1;
            RL.dir=1;
            LL.dir=1;
            break;//原地逆时针
        case 5:
            RU.dir=0;
            LU.dir=0;
            RL.dir=0;
            LL.dir=0;
            break;//原地顺时针
    }


}
