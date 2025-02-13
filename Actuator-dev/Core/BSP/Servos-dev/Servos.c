// Servos.c
// Author: Franki
// Date: 2025-02-13
#include "Servos.h"
void Servos_Init(void)
{
    turntable.dev.def=Servor_turntable_GPIO_Port;
    turntable.dev.pin=Servor_turntable_Pin;
}
// Your C functions and implementation go here