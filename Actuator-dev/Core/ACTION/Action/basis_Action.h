// basis_Action.h
// Author: xl
// Date: 2025-02-14
#include "../BSP/Servos-dev/Servos.h"
#ifndef BASIS_ACTION_H
#define BASIS_ACTION_H

// Your function prototypes and declarations go here
void catching_init(void);//צ�ӳ�ʼ��
void Turntable_spin_1(void);//ת��ת��1  --- 0��
void Turntable_spin_2(void);//ת��ת��2  --- 120��
void Turntable_spin_3(void);//ת��ת��3  --- 240��
void catching_catch(void);//צ��ץס  ---90��
void catching_flip(void);//��ת--180��
void catching_flip_init(void);// ��ת��λ
void  catching_flip_watch(void);//��ת���Ӿ���׽
void catching_catch_to_release(void);//ץ��ץȡ���ͷ�


#endif // BASIS_ACTION_H