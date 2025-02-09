// check_line.c
// Author: Init
// Date: 2025-02-09
#include "check_line.h"
#include "../../Core/BSP/Control/control.h"
float um=0.689f;
// Your C functions and implementation go here
void check_line_Init()
{
    for (int i = 0; i < sizeof(BOUNDARY_VALUE); i++) {
        BOUNDARY_VALUE[i]=0;
    }
    for (int i = 0; i < sizeof (QR_NUM); i++) {
        QR_NUM[i]=0;
    }
}
float ACTION_MODE(int mode)
{

    if(mode==0)//找不到边界线
    {
        con_motion(3200, 3000, 2, 30000);
    }
    if(mode==1)//(找的到边界线)
    {
        if(BOUNDARY_RATE(1)==BOUNDARY_RATE(2))
        {
            if(BOUNDARY_RATE(1)>um)
            {
                con_motion(3200,3000,2,100);
            }
            else if(BOUNDARY_RATE(1)<um)
            {
                con_motion(3200,3000,3,100);
            }
        }
        else
        {
            if(BOUNDARY_RATE(1)<BOUNDARY_RATE(2))
            {
                con_motion(3200,3000,4,100);
            }
            else if(BOUNDARY_RATE(1)>BOUNDARY_RATE(2))
                con_motion(3200,3000,5,100);
        }
    }
}
void car_in_Init()
{
    ACTION_MODE;
}

float BOUNDARY_RATE(int flag)
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
