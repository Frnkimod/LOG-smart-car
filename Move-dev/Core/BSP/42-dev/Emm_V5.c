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
    Motor_Dev LU_buf={{RU_EN_TYPE,RU_EN_PIN},
                      {RU_STP_TYPE,RU_STP_PIN},
                      {RU_DIR_TYPE,RU_DIR_PIN}};
    LU.dev=LU_buf;
    Motor_Dev RU_buf={{RU_EN_TYPE,RU_EN_PIN},
                      {RU_STP_TYPE,RU_STP_PIN},
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
 * @brief       电机指定角度和速度控制
 * @param       int32_t us 例:delay_us(1000)为等待1000微秒
 * @retval      无
 */
void delay_us(int32_t us)
{
/********************SysTick方式(寄存器)**************************/

//    SysTick->LOAD = 72 * us;                                //????????
//    SysTick->VAL = 0x00;                                        //???????
//    SysTick->CTRL = 0x00000005;                                //??????HCLK,?????
//    while(!(SysTick->CTRL & 0x00010000));        //?????0
//    SysTick->CTRL = 0x00000004;
/********************SysTick方式********************************/
//    uint32_t startval,tickn,delays,wait;
//
//    startval = SysTick->VAL;
//    tickn = HAL_GetTick();
//    //sysc = 72000;  //SystemCoreClock / (1000U / uwTickFreq);
//    delays =us * 72; //sysc / 1000 * udelay;
//    if(delays > startval)
//    {
//        while(HAL_GetTick() == tickn)
//        {
//
//        }
//        wait = 72000 + startval - delays;
//        while(wait < SysTick->VAL)
//        {
//
//        }
//    }
//    else {
//        wait = startval - delays;
//        while (wait < SysTick->VAL && HAL_GetTick() == tickn) {
//
//        }
//    }

    uint16_t delay = 0xffff-us-3;		//从此数进行计数，如计数了65535次则刚好1us

    HAL_TIM_Base_Start(&htim3);  	    //开启计数器
    __HAL_TIM_SetCounter(&htim3,delay);	//设置计数器
    while(delay<0xffff-3)
    {
        delay = __HAL_TIM_GetCounter(&htim3); //获取当前计数值
    }
    HAL_TIM_Base_Stop(&htim3);
    //...待补充(具体需要按照时钟树配置构造)
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
