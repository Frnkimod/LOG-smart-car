/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../BSP/42-dev/Emm_V5.h"
#include "../BSP/DWT/dwt.h"
#include "../BSP/Control/control.h"
#include "../move/move/move.h"
#include "../../Core/LG/check/check_line.h"
#include "../../Core/TT_MOTION/TT/tt.h"
#include "../../Core/Inc/usart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId LURL_TaskHandle;
osThreadId RULL_TaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartLURL_Task(void const * argument);
void StartRULL_Task(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  Emm_V5Init();
  con_init();
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityIdle, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of LURL_Task */
  osThreadDef(LURL_Task, StartLURL_Task, osPriorityIdle, 0, 128);
  LURL_TaskHandle = osThreadCreate(osThread(LURL_Task), NULL);

  /* definition and creation of RULL_Task */
  osThreadDef(RULL_Task, StartRULL_Task, osPriorityIdle, 0, 128);
  RULL_TaskHandle = osThreadCreate(osThread(RULL_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
//      int max_speed =150; // �???大�?�度
//      int acceleration_steps =4; // 加�?�和减�?�的步数
//      linearMovement(&RU, &LU, &RL, &LL, 0, 1000, max_speed, acceleration_steps);
//      HAL_Delay(3000);
//      Emm_V5ControlX(&RU, &LU, &RL, &LL, 0, 3000, 30000);
      Emm_V5ControlX(&RU, &LU, &RL, &LL, 0, 600, 100);

      //TT_main();
      uint8_t rx_buffer[100];
      int x, y, r;

      // 接收数据
      if (HAL_UART_Receive(&huart1, rx_buffer, sizeof(rx_buffer), 1000) == HAL_OK)
      {
          // 解析数据
          if (sscanf((char*)rx_buffer, "%d,%d,%d", &x, &y, &r) == 3)
          {

              if (x<T_X&&abs(x-T_X)>2) {
                  Emm_V5ControlX(&RU, &LU, &RL, &LL, 1, 600, 1000);
              }else if(x>T_X&&abs(x-T_X)>2) {

                  Emm_V5ControlX(&RU, &LU, &RL, &LL, 0, 600, 1000);
              }

              // PID控制
              // 这里�?要根据你的PID控制算法来调整小车的运动
              // 例如，根据x, y计算出需要调整的方向和�?�度
          }
      }
      osDelay(1);

  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartLURL_Task */
/**
* @brief Function implementing the LURL_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLURL_Task */
void StartLURL_Task(void const * argument)
{
  /* USER CODE BEGIN StartLURL_Task */
  /* Infinite loop */
  for(;;)
  {
      //Emm_dir_PWM(&RL,&LL,&RU,&LU);
      osDelay(1);
  }
  /* USER CODE END StartLURL_Task */
}

/* USER CODE BEGIN Header_StartRULL_Task */
/**
* @brief Function implementing the RULL_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartRULL_Task */
void StartRULL_Task(void const * argument)
{
  /* USER CODE BEGIN StartRULL_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartRULL_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

