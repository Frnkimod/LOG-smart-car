// basis_Action.c
// Author: xl
// Date: 2025-02-14
#include "basis_Action.h"
#include "../BSP/Servos-dev/Servos.h"
void catching_init(void) {
    for (int i = 0; i < 30; i++) {
        Servo_SetAngle_180(70);  //爪子初始化回到0°
    }
}
void catching_catch() {
    for (int i = 0; i < 30; i++) {
        Servo_SetAngle_180(100);//抓
    }
}
void Turntable_spin_1(){
    for (int i = 0; i < 30; i++) {
        Servo_SetAngle_270_2(0);  //转盘转到盘子1的角度--0°&兼复位
    }

}
void Turntable_spin_2(){
    for (int i = 0; i < 30; i++) {
        Servo_SetAngle_270_2(120);  //转盘转到盘子2的角度--120°
    }
}
void Turntable_spin_3(){
    for (int i = 0; i < 30; i++) {
        Servo_SetAngle_270_2(237);  //转盘转到盘子3的角度--240°
    }
}
void catching_flip(){
    for (int i = 0; i < 30; i++) {
        Servo_SetAngle_270_1(180);
    }
}//翻转--180°

void catching_flip_init(){
    for (int i = 0; i < 30; i++) {
        Servo_SetAngle_270_1(17);
    }
}// 回到0°
void catching_catch_to_release() {
    Servo_SetAngle_180(90);
    Servo_SetAngle_270_1(180);
    Servo_SetAngle_180(0);
    Servo_SetAngle_270_1(0);
}


void catching_flip_watch() {
    for (int i = 0; i < 30; i++) {
        Servo_SetAngle_270_1(144);
    }
}
// Your C functions and implementation go here