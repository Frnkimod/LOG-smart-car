// Control.c
// Author: Dereko
// Date: 2025-01-10
#include "Control.h"

Motor LU;
Motor RL;
Motor LL;
gpio_Conf a1;

void con_init()
{
    RU.speed=BASESPEED;
    RL.speed=BASESPEED;
    LU.speed=BASESPEED;
    LL.speed=BASESPEED;
    RU.delay_motion=0;
    RL.delay_motion=0;
    LU.delay_motion=0;
    LL.delay_motion=0;
    RU.dir=0;
    RL.dir=0;
    LU.dir=0;
    LL.dir=0;
}
/*
 * up: dir->0
 * down: dir->1
 * left: dir->2
 * right：dir->3
 * cw:dir->4
 * ccw:dir->5
 * */
void con_motion(int32_t speed,int32_t distance,uint32_t dir,uint32_t delay_motion)
{
    speed=3200;
    distance=10000;
    delay_motion=30;
    switch (dir) {
        case 0:
            RU.dir=0;
            LU.dir=1;
            RL.dir=0;
            LL.dir=1;
            break;
        case 1:
            RU.dir=1;
            LU.dir=0;
            RL.dir=1;
            LL.dir=0;
            break;

        case 2:
            RU.dir=0;
            LU.dir=0;
            RL.dir=1;
            LL.dir=1;
            break;
        case 3:
            RU.dir=1;
            LU.dir=1;
            RL.dir=0;
            LL.dir=0;
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


}
