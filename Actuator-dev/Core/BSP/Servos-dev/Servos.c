// Servos.c
// Author: Franki
// Date: 2025-02-13
#include "Servos.h"
#include "../BSP/DWT/DWT.h"





Servos turntable;

//����SG90Ϊ������Χ��(0~180��)�������
//htim:Ҫ���õĶ�ʱ�����
//* Channel��PWM���ͨ��
//* countPeriod��pWMһ�����ڼ���ֵ������Ϊ20000
// * CycleTime��һ�����ڶ���ms������Ϊ20
void Servos_Init(void)
{
    turntable.dev.def=Servor_turntable_GPIO_Port;
    turntable.dev.pin=Servor_turntable_Pin;
}




void Servo_SetAngle_270_1(uint16_t angle)
{
    uint16_t pulse_width =500 + (angle * 2000) / 270;  // ���� PWM ��ȣ�us��

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
    if (pulse_width>0&&pulse_width<836){
        dwt_delay_us(pulse_width);

    } else if (pulse_width>836&&pulse_width<836*2){
        dwt_delay_us(836);

        dwt_delay_us(pulse_width-836);

    }else if(pulse_width>836*2){
        dwt_delay_us(836);
        dwt_delay_us(836);
        dwt_delay_us(pulse_width-836*2);

    }
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
    dwt_delay_ms(20 - (pulse_width/1000));  // ���ֵ͵�ƽ��ʹ���� = 20ms

}
void Servo_SetAngle_270_2(uint16_t angle)
{
    uint16_t pulse_width =500 + (angle * 2000) / 270;  // ���� PWM ��ȣ�us��

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
    if (pulse_width>0&&pulse_width<836){
        dwt_delay_us(pulse_width);

    } else if (pulse_width>836&&pulse_width<836*2){
        dwt_delay_us(836);

        dwt_delay_us(pulse_width-836);

    }else if(pulse_width>836*2){
        dwt_delay_us(836);
        dwt_delay_us(836);
        dwt_delay_us(pulse_width-836*2);

    }
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
    dwt_delay_ms(20 - (pulse_width/1000));  // ���ֵ͵�ƽ��ʹ���� = 20ms

}







void Servo_SetAngle_180(uint16_t angle)
{
    uint16_t pulse_width =500 + (angle * 2000) / 180;  // ���� PWM ��ȣ�us��

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
    if (pulse_width>0&&pulse_width<836){
        dwt_delay_us(pulse_width);

    } else if (pulse_width>836&&pulse_width<836*2){
        dwt_delay_us(836);

        dwt_delay_us(pulse_width-836);

    }else if(pulse_width>836*2){
        dwt_delay_us(836);
        dwt_delay_us(836);
        dwt_delay_us(pulse_width-836*2);

    }
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
    dwt_delay_ms(20 - (pulse_width/1000));  // ���ֵ͵�ƽ��ʹ���� = 20ms

}



// Your C functions and implementation go here