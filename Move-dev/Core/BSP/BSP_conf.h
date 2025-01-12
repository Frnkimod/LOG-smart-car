/**********************************************************
*** 编写作者：Franki
*** BSP驱动库配置参数存放区域
**********************************************************/
#ifndef INC_42_DEV_BSP_CONF_H
#define INC_42_DEV_BSP_CONF_H

#include "main.h"

//???????????
#define RU_EN_TYPE GPIOF
#define RU_EN_PIN GPIO_PIN_0
#define RU_STP_TYPE GPIOF
#define RU_STP_PIN GPIO_PIN_1
#define RU_DIR_TYPE GPIOF
#define RU_DIR_PIN GPIO_PIN_2
#define LU_STP_TYPE GPIOF
#define LU_STP_PIN GPIO_PIN_3
#define LU_DIR_TYPE GPIOF
#define LU_DIR_PIN GPIO_PIN_4
#define RL_STP_TYPE GPIOF
#define RL_STP_PIN GPIO_PIN_5
#define RL_DIR_TYPE GPIOF
#define RL_DIR_PIN GPIO_PIN_6
#define LL_STP_TYPE GPIOF
#define LL_STP_PIN GPIO_PIN_7
#define LL_DIR_TYPE GPIOF
#define LL_DIR_PIN GPIO_PIN_8


//...其他轮定义方式以此类推（RU、LU、RL、LL）
#define BASESPEED 3200
#define SPEEDFACTOR 3.9999
#define STPES_PER_REVOLUTION 3200
#define STPE_ANGLE (360.0/STPES_PER_REVOLUTION)
#define SPEED (BASESPEED*SPEEDFACTOR)

typedef struct{
    GPIO_TypeDef* def;
    uint16_t pin;
}gpio_Conf;


#endif //INC_42_DEV_BSP_CONF_H
