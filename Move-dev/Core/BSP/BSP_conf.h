/**********************************************************
*** 编写作者：Franki
*** BSP驱动库配置参数存放区域
**********************************************************/
#ifndef INC_42_DEV_BSP_CONF_H
#define INC_42_DEV_BSP_CONF_H

#include "main.h"

//右上轮接口信息
/******************RU轮********************/
#define RU_EN_TYPE GPIOA
#define RU_EN_PIN GPIO_PIN_5
#define RU_STP_TYPE RU_STP_GPIO_Port
#define RU_STP_PIN RU_STP_Pin
#define RU_DIR_TYPE RU_DIR_GPIO_Port
#define RU_DIR_PIN RU_DIR_Pin
/******************LU轮********************/
#define LU_EN_TYPE GPIOA
#define LU_EN_PIN GPIO_PIN_5
#define LU_STP_TYPE GPIOA
#define LU_STP_PIN GPIO_PIN_1
#define LU_DIR_TYPE GPIOA
#define LU_DIR_PIN GPIO_PIN_7
/******************RL轮********************/
#define RL_EN_TYPE GPIOA
#define RL_EN_PIN GPIO_PIN_5
#define RL_STP_TYPE GPIOA
#define RL_STP_PIN GPIO_PIN_1
#define RL_DIR_TYPE GPIOA
#define RL_DIR_PIN GPIO_PIN_7
/******************LL轮********************/
#define LL_EN_TYPE GPIOA
#define LL_EN_PIN GPIO_PIN_5
#define LL_STP_TYPE GPIOA
#define LL_STP_PIN GPIO_PIN_1
#define LL_DIR_TYPE GPIOA
#define LL_DIR_PIN GPIO_PIN_7
//...其他轮定义方式以此类推（RU、LU、RL、LL）


#define STPES_PER_REVOLUTION 3200 //转一圈脉冲次数
#define STPE_ANGLE (360.0/STPES_PER_REVOLUTION) //脉冲数换算角度
typedef struct{
    GPIO_TypeDef* def;
    uint16_t pin;
}gpio_Conf;

#endif //INC_42_DEV_BSP_CONF_H
