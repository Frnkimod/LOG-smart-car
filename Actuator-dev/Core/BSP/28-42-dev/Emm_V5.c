// Emm_V5.c
// Author: Franki
// Date: 2025-02-13
#include "Emm_V5.h"
void Emm_V5Init()
{

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
// Your C functions and implementation go here