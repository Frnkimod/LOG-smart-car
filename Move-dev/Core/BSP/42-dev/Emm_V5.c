/**********************************************************
*** 编写作者：Franki
*** Emm_v5 42步进电机脉冲驱动具体函数实现
**********************************************************/

#include <stdlib.h>
#include "Emm_V5.h"
#include "../DWT/dwt.h"
#define WHEEL_CIRCUMFERENCE 235.5
Motor RU={
        .dev={
                .IO_Stp={RU_STP_TYPE,RU_STP_PIN},
                .IO_Dir={RU_DIR_TYPE,RU_DIR_PIN},
        },
        .speed = 0,  // 转速 (r/  min)
        .angle = 0,    // 转角 (°)
        .dir = 0,       // 轮子旋转方向 0顺1逆
        .delay_motion = 0,  // 移动时长 (ms)
        .distance = 0  // 运行距离 (mm)
};
Motor LU= {
        .dev={
                .IO_Stp={LU_STP_TYPE, LU_STP_PIN},
                .IO_Dir={LU_DIR_TYPE, LU_DIR_PIN},
        },
        .speed = 0,  // 转速 (r/min)
        .angle = 0,    // 转角 (°)
        .dir = 0,       // 轮子旋转方向 0顺1逆
        .delay_motion = 0,  // 移动时长 (ms)
        .distance = 0  // 运行距离 (mm);
};
Motor RL= {
        .dev={
                .IO_Stp={RL_STP_TYPE, RL_STP_PIN},
                .IO_Dir={RL_DIR_TYPE, RL_DIR_PIN},
        },
        .speed = 0,  // 转速 (r/min)
        .angle = 0,    // 转角 (°)
        .dir = 0,       // 轮子旋转方向 0顺1逆
        .delay_motion = 0,  // 移动时长 (ms)
        .distance = 0  // 运行距离 (mm);
};
Motor LL={
        .dev={
                .IO_Stp={LL_STP_TYPE,LL_STP_PIN},
                .IO_Dir={LL_DIR_TYPE,LL_DIR_PIN},
        },
        .speed = 0,  // 转速 (r/min)
        .angle = 0,    // 转角 (°)
        .dir = 0,       // 轮子旋转方向 0顺1逆
        .delay_motion = 0,  // 移动时长 (ms)
        .distance = 0  // 运行距离 (mm);
        };
Motor TT={
        .dev={
                .IO_Stp={TT_STP_TYPE,TT_STP_PIN},
                .IO_Dir={TT_DIR_TYPE,TT_DIR_PIN},
        },
        .speed = 0,  // 转速 (r/min)
        .angle = 0,    // 转角 (°)
        .dir = 0,       // 轮子旋转方向 0顺1逆
        .delay_motion = 0,  // 移动时长 (ms)
        .distance = 0  // 运行距离 (mm);
};



/**
 * @brief       初始化四个电机io口信息储存到结构体中
 * @param       无
 * @retval      无
 */
void Emm_V5Init()
{
    dwt_init();


    //...补齐LU,RL,LL初始化(参考以上代码)
}
/**
 * @brief       电机指定角度和速度控制
 * @param       *motor:电机结构体指针 dir:方向(1为正,0为反) speed:速度(r/min) angle:角度(°)
 * @retval      无
 */
void Emm_V5Control(Motor *motor,uint8_t dir,int32_t speed,int32_t angle)
{

    int32_t steps=(int32_t)(angle/STPE_ANGLE);
        int32_t cnt=(60*1000000)/(speed*STPES_PER_REVOLUTION);
    if (dir==1)
    {
        HAL_GPIO_WritePin(motor->dev.IO_Dir.def,
                          motor->dev.IO_Dir.pin,
                          GPIO_PIN_SET);
    }else if(dir==0)
    {
        HAL_GPIO_WritePin(motor->dev.IO_Dir.def,
                          motor->dev.IO_Dir.pin,
                          GPIO_PIN_RESET);
    }
    Emm_PWM_OUT(motor->dev.IO_Stp,steps,cnt);
    //motor->speed=speed;//更新速度
    //motor->angle=angle;//更新角度
}

///123
void Emm_dir_PWM(Motor *motor1,Motor *motor2,Motor *motor3,Motor *motor4)
{
    int32_t steps=(int32_t)(360/STPE_ANGLE);
    int32_t cnt=(60*1000000)/(100*STPES_PER_REVOLUTION);
    HAL_GPIO_WritePin(motor1->dev.IO_Dir.def,
                      motor1->dev.IO_Dir.pin,
                      motor1->dir);
    HAL_GPIO_WritePin(motor2->dev.IO_Dir.def,
                      motor2->dev.IO_Dir.pin,
                      motor2->dir);
    HAL_GPIO_WritePin(motor3->dev.IO_Dir.def,
                      motor3->dev.IO_Dir.pin,
                      motor3->dir);
    HAL_GPIO_WritePin(motor4->dev.IO_Dir.def,
                      motor4->dev.IO_Dir.pin,
                      motor4->dir);
    for (;;) {


        HAL_GPIO_WritePin(motor1->dev.IO_Stp.def,motor1->dev.IO_Stp.pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(motor2->dev.IO_Stp.def,motor2->dev.IO_Stp.pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(motor3->dev.IO_Stp.def,motor3->dev.IO_Stp.pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(motor4->dev.IO_Stp.def,motor4->dev.IO_Stp.pin,GPIO_PIN_SET);
        dwt_delay_us(cnt/2);
        //GPIOA->BSRR |=(1<<6);
        HAL_GPIO_WritePin(motor1->dev.IO_Stp.def,motor1->dev.IO_Stp.pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor2->dev.IO_Stp.def,motor2->dev.IO_Stp.pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor3->dev.IO_Stp.def,motor3->dev.IO_Stp.pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor4->dev.IO_Stp.def,motor4->dev.IO_Stp.pin,GPIO_PIN_RESET);
        dwt_delay_us(cnt/2);
    }

}
/**
 * @brief       模拟PWM信号输出
 * @param       io:输出io steps:脉冲数 cnt:脉冲频率
 * @retval      无
 */
void Emm_PWM_OUT(gpio_Conf io,int32_t steps,int32_t cnt)
{
    if (cnt==0)
        return;
    if (cnt/2<836)
    {
        for (int32_t i = 0; i < steps; i++) {
            //GPIOA->BRR |=(1<<6);
            HAL_GPIO_WritePin(io.def,io.pin,GPIO_PIN_SET);
            dwt_delay_us(cnt/2);
            //GPIOA->BSRR |=(1<<6);
            HAL_GPIO_WritePin(io.def,io.pin,GPIO_PIN_RESET);
            dwt_delay_us(cnt/2);
        }
    } else{
        for (int32_t i = 0; i < steps; i++) {
            HAL_GPIO_WritePin(io.def,io.pin,GPIO_PIN_SET);

            for (int32_t j = 0; j < ((cnt/2)/836); j++) {
                dwt_delay_us(836);

            }
            dwt_delay_us(cnt/2-((cnt/2)/836));

            HAL_GPIO_WritePin(io.def,io.pin,GPIO_PIN_RESET);
            for (int32_t j = 0; j < ((cnt/2)/836); j++) {
                dwt_delay_us(836);
            }
            dwt_delay_us(cnt/2-((cnt/2)/836));
        }
    }
}
void Emm_PWM_OUT_new(int32_t steps,int32_t cnt)
{
    for (int32_t i = 0; i < steps; i++) {
        //GPIOA->BRR |=(1<<6);
        HAL_GPIO_WritePin(RU_STP_GPIO_Port,RU_STP_Pin,GPIO_PIN_SET);
        dwt_delay_us(cnt);
        //GPIOA->BSRR |=(1<<6);
        HAL_GPIO_WritePin(RU_STP_GPIO_Port,RU_STP_Pin,GPIO_PIN_RESET);
        dwt_delay_us(cnt);
    }
}
void Emm_dir(int value)
{
    int32_t steps = (int32_t)(abs(value)*3200/360.0); // 将角度转换为步数
    int32_t cnt = ((60 * 1000000) / (3200 * 100)) ; // 计算PWM周期 转速20r/min
    HAL_GPIO_WritePin(RU_DIR_GPIO_Port, RU_DIR_Pin, value > 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LU_DIR_GPIO_Port, LU_DIR_Pin, value > 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LL_DIR_GPIO_Port, LL_DIR_Pin, value > 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RL_DIR_GPIO_Port, RL_DIR_Pin, value > 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);

    // 产生步进信号
    Emm_PWM_OUT_new(steps, cnt);
    return;
}
void Emm_x(int value)
{
    int32_t angle = (int32_t)((abs(value) / WHEEL_CIRCUMFERENCE) * 360); // 将距离转换为角度
    int32_t steps = (int32_t)(angle*3200/360.0); // 将角度转换为步数
    int32_t cnt = ((60 * 1000000) / (3200 * 20)) ; // 计算PWM周期 转速20r/min
    HAL_GPIO_WritePin(RU_DIR_GPIO_Port, RU_DIR_Pin, value < 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LU_DIR_GPIO_Port, LU_DIR_Pin, value > 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RL_DIR_GPIO_Port, RL_DIR_Pin, value > 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LL_DIR_GPIO_Port, LL_DIR_Pin, value < 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);

    // 产生步进信号
    Emm_PWM_OUT_new(steps, cnt);
    return;
}
void Emm_y(int value)
{
    int32_t angle = (int32_t)((abs(value) / WHEEL_CIRCUMFERENCE) * 360); // 将距离转换为角度
    int32_t steps = (int32_t)(angle*3200/360.0); // 将角度转换为步数
    int32_t cnt = ((60 * 1000000) / (3200 * 20)) ; // 计算PWM周期 转速20r/min
    HAL_GPIO_WritePin(RU_DIR_GPIO_Port, RU_DIR_Pin, value > 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LU_DIR_GPIO_Port, LU_DIR_Pin, value > 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LL_DIR_GPIO_Port, LL_DIR_Pin, value < 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RL_DIR_GPIO_Port, RL_DIR_Pin, value < 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);

    // 产生步进信号
    Emm_PWM_OUT_new(steps, cnt);
    return;
}
