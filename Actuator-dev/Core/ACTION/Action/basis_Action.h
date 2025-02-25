// basis_Action.h
// Author: xl
// Date: 2025-02-14
#include "../BSP/Servos-dev/Servos.h"
#ifndef BASIS_ACTION_H
#define BASIS_ACTION_H

// Your function prototypes and declarations go here
void catching_init(void);//爪子初始化
void Turntable_spin_1(void);//转到转盘1  --- 0°
void Turntable_spin_2(void);//转到转盘2  --- 120°
void Turntable_spin_3(void);//转到转盘3  --- 240°
void catching_catch(void);//爪子抓住  ---90°
void catching_flip(void);//翻转--180°
void catching_flip_init(void);// 翻转复位
void  catching_flip_watch(void);//反转到视觉捕捉
void catching_catch_to_release(void);//抓盘抓取到释放


#endif // BASIS_ACTION_H