/**********************************************************
*** 编写作者：Franki
*** Emm_v5 42步进电机脉冲驱动具体函数实现
**********************************************************/

#include "Emm_V5.h"
#include "../DWT/dwt.h"
Motor RU;
Motor LU;
Motor RL;
Motor LL;


/**
 * @brief       初始化四个电机io口信息储存到结构体中
 * @param       无
 * @retval      无
 */
void Emm_V5Init()
{
    dwt_init();
    Motor_Dev LU_buf={{RU_STP_TYPE,RU_STP_PIN},
                      {RU_DIR_TYPE,RU_DIR_PIN}};
    LU.dev=LU_buf;
    Motor_Dev RU_buf={{RU_STP_TYPE,RU_STP_PIN},
                      {RU_DIR_TYPE,RU_DIR_PIN}};
    RU.dev=RU_buf;

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
    int32_t cnt=(60*1000000)/(70*STPES_PER_REVOLUTION);
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
    for (int32_t i = 0; i < steps; i++) {
        HAL_GPIO_WritePin(motor1->dev.IO_Stp.def,motor1->dev.IO_Stp.pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(motor2->dev.IO_Stp.def,motor2->dev.IO_Stp.pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(motor3->dev.IO_Stp.def,motor3->dev.IO_Stp.pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(motor4->dev.IO_Stp.def,motor4->dev.IO_Stp.pin,GPIO_PIN_SET);
        //dwt_delay_us(cnt/2);
        //GPIOA->BSRR |=(1<<6);
        HAL_GPIO_WritePin(motor1->dev.IO_Stp.def,motor1->dev.IO_Stp.pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor2->dev.IO_Stp.def,motor2->dev.IO_Stp.pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor3->dev.IO_Stp.def,motor3->dev.IO_Stp.pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor4->dev.IO_Stp.def,motor4->dev.IO_Stp.pin,GPIO_PIN_RESET);
        //dwt_delay_us(cnt/2);
    }

}
/**
 * @brief       模拟PWM信号输出
 * @param       io:输出io steps:脉冲数 cnt:脉冲频率
 * @retval      无
 */
void Emm_PWM_OUT(gpio_Conf io,int32_t steps,int32_t cnt)
{
    for (int32_t i = 0; i < steps; i++) {
        //GPIOA->BRR |=(1<<6);
        HAL_GPIO_WritePin(io.def,io.pin,GPIO_PIN_SET);
        dwt_delay_us(cnt/2);
        //GPIOA->BSRR |=(1<<6);
        HAL_GPIO_WritePin(io.def,io.pin,GPIO_PIN_RESET);
        dwt_delay_us(cnt/2);
    }
}
