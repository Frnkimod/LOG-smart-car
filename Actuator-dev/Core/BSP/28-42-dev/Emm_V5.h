// Emm_V5.h
// Author: Franki
// Date: 2025-02-13

#ifndef EMM_V5_H
#define EMM_V5_H
#include "../BSP_conf.h"

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
    double distance;//运行距离
    double circle;
}Motor;

extern Motor JJ;
// Your function prototypes and declarations go here
void Emm_V5Init(void);

void Emm_PWM_OUT(gpio_Conf io,int32_t steps,int32_t cnt);
void Emm_PWM_remove_JJ(int32_t A);
void Emm_PWM_remove_JJ_SET(int32_t A);
void Emm_PWM_remove_JJ_back(void);//最大的缩短
void Emm_PWM_remove_JJ_go(void);//最大伸长
void Emm_PWM_remove_JJ_spin(void);//开始旋转的长度
void Emm_PWM_remove_JJ_spin_go_back(void);
void Emm_PWM_remove_JJ_distance(int32_t A);//x为1到10  9cm 需要920
void  Emm_PWM_remove_JJ_spin_go(void); //旋转后再探出到最大
void Emm_PWM_remove_KK_down(int32_t distance_mm);//下
void Emm_PWM_remove_KK_up(int32_t distance_mm);//上
void Emm_PWM_remove_KK(int32_t distance_mm);//下
void Emm_PWM_remove_KK_SET(int32_t distance_mm);//上

void calibration_catch();//信号接收,抓取 放盘子上
void calibration_release();//
void  start(void);//开始
void  start_scan(void);//扫描
void  start_catch(void);
#endif // EMM_V5_H


