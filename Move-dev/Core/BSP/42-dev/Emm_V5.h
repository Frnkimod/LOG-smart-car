/**********************************************************
*** 编写作者：Franki
*** Emm_v5 42步进电机脉冲驱动
**********************************************************/
#ifndef INC_42_DEV_EMM_V5_H
#define INC_42_DEV_EMM_V5_H
#include "../BSP_conf.h"
#include "tim.h"


typedef struct {
    gpio_Conf IO_Stp;//Stp引脚信息(包含字母编号和数字编号)
    gpio_Conf IO_Dir;//Dir引脚信息(包含字母编号和数字编号)
}Motor_Dev;


//电机参数结构体(目的:实时储存电机参数,方便动态调试需要改参数)
typedef struct {
    Motor_Dev dev;//设备IO口信息
    int32_t speed;//转速(r/min)
    int32_t angle;//转角(°)
    uint32_t dir;//轮子旋转方向 0顺1逆
    uint32_t delay_motion;//移动时长
    int32_t distance;//运行距离

}Motor;

extern Motor RU;
extern Motor LU;
extern Motor RL;
extern Motor LL;

void Emm_V5Init(void);
void Emm_V5Control(Motor *motor,uint8_t dir,int32_t speed,int32_t angle);
void delay_us(int32_t us);

void Emm_PWM_OUT(gpio_Conf io,int32_t steps,int32_t cnt);
#endif //INC_42_DEV_EMM_V5_H
