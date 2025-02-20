//
// Created by liang on 2025/2/13.
//

#ifndef ACTUATOR_DEV_DWT_H
#define ACTUATOR_DEV_DWT_H


#include <stdio.h>
#include <stm32f1xx_hal.h>

/***
*@brief DWT初始化
*@returen 初始化成功，返回1；否则，返回0
*/
uint8_t dwt_init(void);

/***
* @brief 延时微秒
* @param us 指定延时微秒值
*/
void dwt_delay_us(volatile uint16_t us);

/***
* @brief 延时毫秒
* @param us 指定延时毫秒值
*/
void dwt_delay_ms(volatile uint16_t ms);
#endif //ACTUATOR_DEV_DWT_H
