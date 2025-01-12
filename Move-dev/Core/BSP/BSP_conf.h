/**********************************************************
*** 编写作者：Franki
*** BSP驱动库配置参数存放区域
**********************************************************/
#ifndef INC_42_DEV_BSP_CONF_H
#define INC_42_DEV_BSP_CONF_H

#include "main.h"

/******************RU轮********************/
#define RU_STP_TYPE RU_STP_GPIO_Port
#define RU_STP_PIN RU_STP_Pin
#define RU_DIR_TYPE RU_DIR_GPIO_Port
#define RU_DIR_PIN RU_DIR_Pin
/******************LU轮********************/
#define LU_STP_TYPE LU_STP_GPIO_Port
#define LU_STP_PIN LU_STP_Pin
#define LU_DIR_TYPE LU_DIR_GPIO_Port
#define LU_DIR_PIN LU_DIR_Pin
/******************RL轮********************/
#define RL_STP_TYPE RL_STP_GPIO_Port
#define RL_STP_PIN RL_STP_Pin
#define RL_DIR_TYPE RL_DIR_GPIO_Port
#define RL_DIR_PIN RL_DIR_Pin
/******************LL轮********************/
#define LL_STP_TYPE LL_STP_GPIO_Port
#define LL_STP_PIN LL_STP_Pin
#define LL_DIR_TYPE LL_DIR_GPIO_Port
#define LL_DIR_PIN LL_DIR_Pin

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
