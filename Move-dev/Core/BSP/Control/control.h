// Control.h
// Author: Dereko
// Date: 2025-01-10

#ifndef CONTROL_H
#define CONTROL_H
#include "../42-dev/Emm_V5.h"
#include "../BSP_conf.h"


void con_init();
void con_motion(int32_t speed,uint32_t dir,uint32_t distance);

// Your function prototypes and declarations go here

#endif // CONTROL_H