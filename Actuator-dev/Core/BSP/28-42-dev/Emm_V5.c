// Emm_V5.c
// Author: Franki
// Date: 2025-02-13
#include "Emm_V5.h"
#include"../BSP/DWT/DWT.h"
#include"../ACTION/Action/basis_Action.h"
void Emm_V5Init()
{

}
/**
 * @brief       模拟PWM信号输出
 * @param       io:输出io steps:脉冲数 cnt:脉冲频率
 * @retval      无
 */
void Emm_PWM_OUT(gpio_Conf io,int32_t steps,int32_t cnt)    //steps 段数 角度    cnt 是周期
{
    if (cnt==0)
        return;
    if (cnt/2<836)
    {
        for (int32_t i = 0; i < steps; i++) {
            //GPIOA->BRR |=(1<<6);
            HAL_GPIO_WritePin(io.def,io.pin,GPIO_PIN_SET);
            dwt_delay_us(cnt/2);
            //GPIOA->BSRR |=(1<<6);
            HAL_GPIO_WritePin(io.def,io.pin,GPIO_PIN_RESET);
            dwt_delay_us(cnt/2);
        }
    } else{
        for (int32_t i = 0; i < steps; i++) {
            HAL_GPIO_WritePin(io.def,io.pin,GPIO_PIN_SET);

            for (int32_t j = 0; j < ((cnt/2)/836); j++) {
                dwt_delay_us(836);

            }
            dwt_delay_us(cnt/2-((cnt/2)/836));

            HAL_GPIO_WritePin(io.def,io.pin,GPIO_PIN_RESET);
            for (int32_t j = 0; j < ((cnt/2)/836); j++) {
                dwt_delay_us(836);
            }
            dwt_delay_us(cnt/2-((cnt/2)/836));
        }
    }
}

void Emm_PWM_remove_JJ(int32_t A){
    int32_t distance_mm=A;
    int32_t steps_needed =(int32_t)(distance_mm*3200/360.0);  // 计算需要的步数
    int32_t pwm_period = (60*1000000)/(80*STPES_PER_REVOLUTION);     // 计算 PWM 周期 (us)
    HAL_GPIO_WritePin(JJ_DIR_GPIO_Port,JJ_DIR_Pin,GPIO_PIN_RESET);//前进
    gpio_Conf motor = {JJ_STP_GPIO_Port, JJ_STP_Pin};       // GPIO 配置
    Emm_PWM_OUT(motor, steps_needed, pwm_period);
}

void Emm_PWM_remove_JJ_SET(int32_t A){
    int32_t distance_mm=A;
    int32_t steps_needed =(int32_t)(distance_mm*3200/360.0);  // 计算需要的步数
    int32_t pwm_period = (60*1000000)/(80*STPES_PER_REVOLUTION);     // 计算 PWM 周期 (us)
    HAL_GPIO_WritePin(JJ_DIR_GPIO_Port,JJ_DIR_Pin,GPIO_PIN_SET);//后退
    gpio_Conf motor = {JJ_STP_GPIO_Port, JJ_STP_Pin};       // GPIO 配置
    Emm_PWM_OUT(motor, steps_needed, pwm_period);
}

void Emm_PWM_remove_JJ_go(){
    int32_t distance_mm=920;
    int32_t steps_needed =(int32_t)(distance_mm*3200/360.0);  // 计算需要的步数
    int32_t pwm_period = (60*1000000)/(80*STPES_PER_REVOLUTION);     // 计算 PWM 周期 (us)
    HAL_GPIO_WritePin(JJ_DIR_GPIO_Port,JJ_DIR_Pin,GPIO_PIN_RESET);//前进
    gpio_Conf motor = {JJ_STP_GPIO_Port, JJ_STP_Pin};       // GPIO 配置
    Emm_PWM_OUT(motor, steps_needed, pwm_period);
}



void Emm_PWM_remove_JJ_spin(){//开始旋转 12.5
int32_t steps_needed =(int32_t)(540*3200/360.0);  // 计算需要的步数
int32_t pwm_period = (60*1000000)/(80*STPES_PER_REVOLUTION);     // 计算 PWM 周期 (us)
HAL_GPIO_WritePin(JJ_DIR_GPIO_Port,JJ_DIR_Pin,GPIO_PIN_RESET);//前进
gpio_Conf motor = {JJ_STP_GPIO_Port, JJ_STP_Pin};       // GPIO 配置
Emm_PWM_OUT(motor, steps_needed, pwm_period);
}

void Emm_PWM_remove_JJ_spin_go(){//开始旋转 12.5
    int32_t steps_needed =(int32_t)(100*3200/360.0);  // 计算需要的步数
    int32_t pwm_period = (60*1000000)/(80*STPES_PER_REVOLUTION);     // 计算 PWM 周期 (us)
    HAL_GPIO_WritePin(JJ_DIR_GPIO_Port,JJ_DIR_Pin,GPIO_PIN_RESET);//前进
    gpio_Conf motor = {JJ_STP_GPIO_Port, JJ_STP_Pin};       // GPIO 配置
    Emm_PWM_OUT(motor, steps_needed, pwm_period);
}



void Emm_PWM_remove_JJ_distance(int32_t A){//x为1到10
int32_t steps_needed =(int32_t)(A*95*3200/360.0);  // 计算需要的步数
int32_t pwm_period = (60*1000000)/(80*STPES_PER_REVOLUTION);     // 计算 PWM 周期 (us)
HAL_GPIO_WritePin(JJ_DIR_GPIO_Port,JJ_DIR_Pin,GPIO_PIN_RESET);//前进
gpio_Conf motor = {JJ_STP_GPIO_Port, JJ_STP_Pin};       // GPIO 配置
Emm_PWM_OUT(motor, steps_needed, pwm_period);}






void Emm_PWM_remove_JJ_back() {
    int32_t steps_needed = (int32_t) (920 * 3200 / 360.0);  // 计算需要的步数
    int32_t pwm_period = (60 * 1000000) / (80*STPES_PER_REVOLUTION);     // 计算 PWM 周期 (us)
    HAL_GPIO_WritePin(JJ_DIR_GPIO_Port, JJ_DIR_Pin, GPIO_PIN_SET);//前进
    gpio_Conf motor = {JJ_STP_GPIO_Port, JJ_STP_Pin};       // GPIO 配置
    Emm_PWM_OUT(motor, steps_needed, pwm_period);
}
void Emm_PWM_remove_JJ_spin_go_back(){
    int32_t steps_needed =(int32_t)(835*3200/360.0);  // 计算需要的步数
    int32_t pwm_period = (60*1000000)/(80*STPES_PER_REVOLUTION);     // 计算 PWM 周期 (us)
    HAL_GPIO_WritePin(JJ_DIR_GPIO_Port,JJ_DIR_Pin,GPIO_PIN_SET);//前进
    gpio_Conf motor = {JJ_STP_GPIO_Port, JJ_STP_Pin};       // GPIO 配置
    Emm_PWM_OUT(motor, steps_needed, pwm_period);
}


 void  Emm_PWM_remove_KK_up(int32_t distance_mm)
 {
     int32_t steps_needed =(int32_t)(distance_mm*3200/360.0);  // 计算需要的步数
     int32_t pwm_period = (60*1000000)/(65*STPES_PER_REVOLUTION);      // 计算 PWM 周期 (us)
     HAL_GPIO_WritePin(KK_DIR_GPIO_Port,KK_DIR_Pin,GPIO_PIN_SET);// 从轴看向电机 逆时针时针 向上
     gpio_Conf motor = {KK_STP_GPIO_Port, KK_STP_Pin};       // GPIO 配置
     Emm_PWM_OUT(motor, steps_needed, pwm_period);
 }

void  Emm_PWM_remove_KK_SET(int32_t distance_mm)
{
    int32_t steps_needed =(int32_t)(distance_mm*3200/360.0);  // 计算需要的步数
    int32_t pwm_period = (60*1000000)/(80*STPES_PER_REVOLUTION);      // 计算 PWM 周期 (us)
    HAL_GPIO_WritePin(KK_DIR_GPIO_Port,KK_DIR_Pin,GPIO_PIN_SET);// 从轴看向电机 逆时针时针 向上
    gpio_Conf motor = {KK_STP_GPIO_Port, KK_STP_Pin};       // GPIO 配置
    Emm_PWM_OUT(motor, steps_needed, pwm_period);
}


void Emm_PWM_remove_KK_down(int32_t distance_mm){
    int32_t steps_needed =(int32_t)(distance_mm*3200/360.0);  // 计算需要的步数   835 到了四分之一
    int32_t pwm_period = (60*1000000)/(60*STPES_PER_REVOLUTION);      // 计算 PWM 周期 (us)
     HAL_GPIO_WritePin(KK_DIR_GPIO_Port,KK_DIR_Pin,GPIO_PIN_RESET);// 从轴看向电机 顺时针 向下
    gpio_Conf motor = {KK_STP_GPIO_Port, KK_STP_Pin};       // GPIO 配置
    Emm_PWM_OUT(motor, steps_needed, pwm_period);
}





void Emm_PWM_remove_KK(int32_t distance_mm){
    int32_t steps_needed =(int32_t)(distance_mm*3200/360.0);  // 计算需要的步数  下降 835 到了四分之一
    int32_t pwm_period = (60*1000000)/(80*STPES_PER_REVOLUTION);      // 计算 PWM 周期 (us)
    HAL_GPIO_WritePin(KK_DIR_GPIO_Port,KK_DIR_Pin,GPIO_PIN_RESET);// 从轴看向电机 顺时针 向下
    gpio_Conf motor = {KK_STP_GPIO_Port, KK_STP_Pin};       // GPIO 配置
    Emm_PWM_OUT(motor, steps_needed, pwm_period);
}

void  calibration_catch(){
    uint8_t pin_state;
    pin_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
    if(pin_state==GPIO_PIN_SET)//&&颜色识别,缺少
    {
       Emm_PWM_remove_JJ_go();//伸长
        HAL_Delay(2000);
        Emm_PWM_remove_KK_up(700);//上升至抓取高度
        HAL_Delay(2000);
        catching_init();//松抓
        HAL_Delay(1000);
        catching_catch();//抓
        HAL_Delay(1000);
        Turntable_spin_1();//转盘1到位
        HAL_Delay(2000);
        catching_flip();//翻转
        HAL_Delay(2000);
        catching_init();//松抓
        HAL_Delay(1000);
        catching_flip_init();//爪子角度复位
        HAL_Delay(2000);

    }
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
}



void  calibration_release(){

}


void  start_scan(){
    while (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2));
    Emm_PWM_remove_KK_down(300);
    catching_flip_watch();
    HAL_GPIO_WritePin(FLAG_OUT_GPIO_Port,FLAG_OUT_Pin,GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(FLAG_OUT_GPIO_Port,FLAG_OUT_Pin,GPIO_PIN_RESET);
}



void  start(){


    Emm_PWM_remove_JJ_spin();
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(FLAG_OUT_GPIO_Port,FLAG_OUT_Pin,GPIO_PIN_RESET);
}



void start_catch(){
    while (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2));
    HAL_Delay(100);
    Emm_PWM_remove_JJ_spin_go();
    Emm_PWM_remove_KK_up(300);
    catching_flip();
    catching_init();
    catching_catch();
    Emm_PWM_remove_KK_up(100);
    catching_flip_init();
    Turntable_spin_1();

    HAL_GPIO_WritePin(FLAG_OUT_GPIO_Port,FLAG_OUT_Pin,GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(FLAG_OUT_GPIO_Port,FLAG_OUT_Pin,GPIO_PIN_RESET);
}

// Your C functions and implementation go here