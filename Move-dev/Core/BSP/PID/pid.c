#include "pid.h"
#include "../../move/move/move.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义目标位置和时间变量


void SendIntOverUART(int value) {
    char buffer[32];  // 用于存储转换后的字符串
    sprintf(buffer, "%d\n", value);  // 将整数转换为字符串，并添加换行符
    HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
}

// PID控制器初始化
void PID_Init(PID_Controller *pid, float Kp, float Ki, float Kd) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->integral = 0;
    pid->prev_error = 0;
    // 等待接收到数据
    while (1) {

        uint8_t buffer[3];  // 用于存储接收到的数据
        int angle;
        if (HAL_UART_Receive(&huart1, buffer, sizeof(buffer), HAL_MAX_DELAY) == HAL_OK) {
            if (sscanf((char*)buffer, "@%d@", &angle) == 1) {
                // 解析成功，angle 包含角度值
                SendIntOverUART(angle);
                return;
            }

        }
    }
}

// PID控制器更新函数
float PID_Update(PID_Controller *pid, float error, float dt) {
    float derivative = (error - pid->prev_error) / dt;
    pid->integral += error * dt;
    float output = pid->Kp * error + pid->Ki * pid->integral + pid->Kd * derivative;
    pid->prev_error = error;
    return output;
}
float GetSensorValue()
{


    while (1) {

        static uint8_t buffer[5];  // 用于存储接收到的数据
        int angle;
        if (HAL_UART_Receive(&huart1, buffer, sizeof(buffer), HAL_MAX_DELAY) == HAL_OK) {
            if (strcmp(buffer, "STOPA") == 0) {
                HAL_UART_Transmit(&huart1, (uint8_t *) buffer, strlen(buffer), HAL_MAX_DELAY);
                return 1000;
            }
            if (sscanf((char*)buffer, "A=%d", &angle) == 1) {
                // 解析成功，angle 包含角度值
                SendIntOverUART(angle);
                return angle;
            }
        }
    }
}
int GetPosYValue()
{


    while (1) {

        static uint8_t buffer[5];  // 用于存储接收到的数据
        int y;
        if (HAL_UART_Receive(&huart1, buffer, sizeof(buffer), HAL_MAX_DELAY) == HAL_OK) {
            if (strcmp(buffer, "STOPY") == 0) {
                HAL_UART_Transmit(&huart1, (uint8_t *) buffer, strlen(buffer), HAL_MAX_DELAY);
                return 1000;
            }
            if (sscanf((char*)buffer,"Y=%d", &y) == 1) {
                // 解析成功，angle 包含角度值
                SendIntOverUART(y);
                //SendIntOverUART(pos[1]);

                return y;
            }
        }
    }
}
int GetPosXValue()
{


    while (1) {

        static uint8_t buffer[5];  // 用于存储接收到的数据
        int x;
        if (HAL_UART_Receive(&huart1, buffer, sizeof(buffer), HAL_MAX_DELAY) == HAL_OK) {
            if (strcmp(buffer, "STOPX") == 0) {
                HAL_UART_Transmit(&huart1, (uint8_t *) buffer, strlen(buffer), HAL_MAX_DELAY);
                return 1000;
            }
            if (sscanf((char*)buffer,"X=%d", &x) == 1) {
                // 解析成功，angle 包含角度值
                SendIntOverUART(x);
                //SendIntOverUART(pos[1]);

                return x;
            }
        }
    }
}
void PID_Angle_Check()
{
    float target_position = 0.0;  // 示例目标位置（角度）
    float current_position = 0.0;  // 当前位置
    float error = 0.01;             // 误差
    float dt = 0.01;               // 时间间隔（根据实际情况调整）
    //PID_Init(&pid, 5.0, 0.25, 0.01);  // 设置PID参数（根据实际情况调整）
    while (1)
    {


        // 获取当前位置（从传感器读取）
        current_position = GetSensorValue();
        if (current_position==1000)
            return;
        Emm_dir(current_position);

        // 计算误差
        //error = target_position - current_position;

        // 更新PID控制器
        //float output = PID_Update(&pid, error, dt);

        // 设置伺服电机角度（根据PID输出调整）

        // 等待一段时间
        //HAL_Delay((uint32_t)(dt*1000));
        //HAL_Delay(1000);
        // 从串口读取目标位置
        //target_position = GetSensorValue();
    }
}

void PID_Pos_Check()
{
    int x=0;  // 示例目标位置（角度）
    int y=0;
    while (1)
    {
        y = GetPosYValue();
        if (y==1000)
            break;
        Emm_y(y);
    }

    while (1)
    {
        x = GetPosXValue();
        if (x==1000)
            break;
        Emm_x(x);
    }
}
