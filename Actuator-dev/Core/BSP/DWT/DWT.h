//
// Created by liang on 2025/2/13.
//

#ifndef ACTUATOR_DEV_DWT_H
#define ACTUATOR_DEV_DWT_H


#include <stdio.h>
#include <stm32f1xx_hal.h>

/***
*@brief DWT��ʼ��
*@returen ��ʼ���ɹ�������1�����򣬷���0
*/
uint8_t dwt_init(void);

/***
* @brief ��ʱ΢��
* @param us ָ����ʱ΢��ֵ
*/
void dwt_delay_us(volatile uint16_t us);

/***
* @brief ��ʱ����
* @param us ָ����ʱ����ֵ
*/
void dwt_delay_ms(volatile uint16_t ms);
#endif //ACTUATOR_DEV_DWT_H
