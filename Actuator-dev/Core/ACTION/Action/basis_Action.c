// basis_Action.c
// Author: xl
// Date: 2025-02-14
#include "basis_Action.h"
#include "../BSP/Servos-dev/Servos.h"
void catching_init(void){
   Servo_SetAngle_180(60);  //爪子初始化回到0°
}

void catching_catch(){

    Servo_SetAngle_180(100);//抓
}

void Turntable_spin_1(){
   Servo_SetAngle_270_2(0);  //转盘转到盘子1的角度--0°&兼复位
}
void Turntable_spin_2(){
    Servo_SetAngle_270_2(120);  //转盘转到盘子2的角度--120°
}
void Turntable_spin_3(){
    Servo_SetAngle_270_2(237);  //转盘转到盘子3的角度--240°
}
void catching_flip(){
    Servo_SetAngle_270_1(180);
}//翻转--180°

void catching_flip_init(){
    Servo_SetAngle_270_1(12);
}// 回到0°
void catching_catch_to_release() {
    Servo_SetAngle_180(90);
    Servo_SetAngle_270_1(180);
    Servo_SetAngle_180(0);
    Servo_SetAngle_270_1(0);
}


// Your C functions and implementation go here