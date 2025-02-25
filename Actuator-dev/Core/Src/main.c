/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../BSP/DWT/DWT.h"
#include "../BSP/Servos-dev/Servos.h"
#include"../BSP/28-42-dev/Emm_V5.h"
#include "../ACTION/Action/basis_Action.h"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    dwt_init();
    Turntable_spin_1();
//    catching_init();//放抓
//    catching_flip();//翻转在外面
//    HAL_Delay(3000);
//
//
//    start();
//    start_scan();
//   start_catch();
  while (1) {
      uint8_t message[] = "LIAO";
      int A[3];
      int i=0;

      uint16_t received_size = 0;

      catching_flip_watch();
      // 发送消息
      while (1)
      {
          HAL_UART_Transmit(&huart1, message, sizeof(message), HAL_MAX_DELAY);
          uint8_t rx_buffer[10];

          received_size = HAL_UART_Receive(&huart1, rx_buffer, sizeof(rx_buffer), 10); // 设置超时时间为10ms

          if (received_size > 0) {
              // 处理接收到的数据
//              if (rx_buffer[0] == '1'||rx_buffer[0] == '2'||rx_buffer[0] == '3'){//1 是红色 2是绿色 3是蓝色
//                 scanf((char*)rx_buffer, "%d", &A[i]);
//                  i++;
                  if (rx_buffer[0] == '1' || rx_buffer[0] == '2' || rx_buffer[0] == '3') {
                      A[i] = atoi((char*)rx_buffer);  // 把rx_buffer转换成整数存入A[i]
                      i++;
                  }
                  break;
              }
          }
      }


















      catching_init();
      Emm_PWM_remove_KK_down(510);
      HAL_Delay(2000);
      catching_catch();
      Emm_PWM_remove_KK_up(800);
      catching_flip();
      Turntable_spin_1();
      catching_flip_init();
      HAL_Delay(1000);
      catching_init();
      HAL_Delay(2000);
      catching_flip();


      catching_init();
      Emm_PWM_remove_KK_down(710);
      HAL_Delay(2000);
      catching_catch();
      Emm_PWM_remove_KK_up(1150);
      catching_flip();
      Turntable_spin_2();
      catching_flip_init();
      HAL_Delay(1000);
      catching_init();
      HAL_Delay(2000);
      catching_flip();



      catching_init();
      Emm_PWM_remove_KK_down(910);
      HAL_Delay(2000);
      catching_catch();
      Emm_PWM_remove_KK_up(1400);
      catching_flip();
      Turntable_spin_3();
      catching_flip_init();
      HAL_Delay(1000);
      catching_init();
      HAL_Delay(2000);
      catching_flip();

      Turntable_spin_1();



//      HAL_Delay(100);
//      Emm_PWM_remove_JJ_spin_go();//现场微调
//      Emm_PWM_remove_KK_up(300);
//      catching_flip();
//      catching_init();
//      catching_catch();
//      Emm_PWM_remove_KK_up(100);
//      catching_flip_init();
//      Turntable_spin_1();
//      catching_init();

//      catching_flip_init();
//      HAL_Delay(1000);
//      catching_catch();
//      HAL_Delay(1000);
//      catching_flip();//翻转在外面
//      HAL_Delay(1000);
//      catching_flip_init();
//      HAL_Delay(1000);
//      catching_init();
//      HAL_Delay(1000);
//      catching_flip();//翻转在外面
//      HAL_Delay(1000);
//
//
//
//
//      Turntable_spin_2();
//      catching_flip_init();//翻回来
//      HAL_Delay(1000);
//      catching_catch();//抓
//      HAL_Delay(1000);
//      catching_flip();//翻出去
//      HAL_Delay(1000);
//      catching_flip_init();//返回来
//      HAL_Delay(1000);
//      catching_init();//放
//      HAL_Delay(1000);
//      catching_flip();//翻转在外面
//      HAL_Delay(1000);
//
//
//
//
//
//      Turntable_spin_3();
//      catching_flip_init();
//      HAL_Delay(1000);
//       catching_catch();
//      HAL_Delay(1000);
//      catching_flip();
//      HAL_Delay(1000);
//      catching_flip_init();
//      HAL_Delay(1000);
//      catching_init();
//      HAL_Delay(1000);
//      catching_flip();//翻转在外面
//      HAL_Delay(1000);



// 接收数据



//      uint8_t rx_buffer[100];
//      if (HAL_UART_Receive(&huart1, rx_buffer, sizeof(rx_buffer), 1000) == HAL_OK)
//      {
//          // 解析数据
//          if (sscanf((char*)rx_buffer, "%d,%d,%d", &x, &y, &r) == 3)// y是上下kk    r是jj伸缩
//          {
//
//              // PID控制
//              if (y<T_Y&&abs(y-T_Y)>2)
//              {
//                  Emm_PWM_remove_KK(25);
//
//              } else if(y>T_Y&&abs(y-T_Y)>2){
//                  Emm_PWM_remove_KK_SET(25);
//              }
//
//              if (r<T_R&&abs(r-T_R)>2 ){
//                  Emm_PWM_remove_JJ_SET(25);
//
//
//
//              } else if(r>T_R&&abs(r-T_R)>2){
//                  Emm_PWM_remove_JJ(25);
//              }
//              if (abs(y-T_Y)<2&& abs(r-T_R)<2)
//              {
//                   catching_flip();
//              HAL_Delay(1000);
//              catching_init();
//              HAL_Delay(1000);
//              catching_catch();
//              HAL_Delay(1000);    通讯接收
//                  return 0;
//              }
//




//              if (abs(y-T_Y)<0.5&& abs(r-T_R))
//              {
//                  return 0;
//              }

//               这里需要根据你的PID控制算法来调整小车的运动
//               例如，根据x, y计算出需要调整的方向和速度
  }







//      catching_flip_watch();
//      HAL_Delay(1000);
//      Emm_PWM_remove_KK_down(150);
//      return 0;      第一个转台视觉捕捉角度与高度



//      Emm_PWM_remove_KK_up(1100);
//      HAL_Delay(3000);



//        catching_flip();
//        HAL_Delay(10000);  //先180 再到0°
 //    catching_flip_init();
//      HAL_Delay(6000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {


  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
