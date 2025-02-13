// Control.c
// Author: Dereko
// Date: 2025-01-10
#include "Control.h"



void con_init()
{
}
void con_motion(int32_t speed,uint32_t dir,uint32_t distance)
{
    RU.speed = LU.speed = RL.speed = LL.speed = speed;
    RU.distance = LU.distance = RL.distance = LL.distance = distance;

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
