// Emm_V5.h
// Author: Franki
// Date: 2025-02-13

#ifndef EMM_V5_H
#define EMM_V5_H
#include "../BSP_conf.h"
// Your function prototypes and declarations go here
void Emm_V5Init(void);
void Emm_PWM_OUT(gpio_Conf io,int32_t steps,int32_t cnt);
#endif // EMM_V5_H