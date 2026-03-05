/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "control.h"
#include "tim.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

volatile int PWM_num4 = 0;
volatile int mai4 = 2;
volatile int mubiao4=0;
extern uint8_t zxdnb;
extern uint8_t a,b;
/* USER CODE END TD */

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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define FRAME_HEADER 0x7F   //帧头
#define FRAME_TAIL 0xFF     //帧尾
#define FRAME_LENGTH 5      //接收长度

uint8_t rxBuffer[FRAME_LENGTH]; // 接收缓冲区
uint8_t rxIndex = 0; // 接收缓冲区索引
uint8_t rxState = 0; // 接收状态
uint8_t rxData;
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt.
  */
void TIM1_UP_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_IRQn 0 */

  /* USER CODE END TIM1_UP_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_IRQn 1 */

  /* USER CODE END TIM1_UP_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */

  /* USER CODE END USART3_IRQn 1 */
}

/**
  * @brief This function handles TIM8 update interrupt.
  */
void TIM8_UP_IRQHandler(void)
{
  /* USER CODE BEGIN TIM8_UP_IRQn 0 */

  /* USER CODE END TIM8_UP_IRQn 0 */
  HAL_TIM_IRQHandler(&htim8);
  /* USER CODE BEGIN TIM8_UP_IRQn 1 */

  /* USER CODE END TIM8_UP_IRQn 1 */
}

/* USER CODE BEGIN 1 */
//数脉冲
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    	if (htim->Instance == htim4.Instance)
    {
        if (mai4 == 1)
        {
            PWM_num4++;
            if (PWM_num4 == mubiao4)
            {  
							  PWM_num4 = 0;
                HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
                mai4 = 2;
            }
        }
        if (mai4 == 0)
        {
            PWM_num4--;
            if (PWM_num4 == mubiao4)
            {
                HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
                mai4 = 2;
								PWM_num4 = 0;
            }
        }
    }
}


/**********************************接收数组****************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
   if (huart->Instance == USART1) {
        // 接收到数据，进行处理
           if (rxState == 0) { // 初始状态，等待帧头
            if (rxData == FRAME_HEADER) {
                rxState = 1;
            }
        } 
		   if (rxState == 1) { // 接收数据状态
            rxBuffer[rxIndex++] = rxData; // 将接收到的数据存入缓冲区
            if (rxIndex >= FRAME_LENGTH) { // 缓冲区已满，进入下一个状态
                rxIndex = 0;
                rxState = 2;
            }
        } 
		   if (rxState == 2) { // 检查帧尾
            if (rxData == FRAME_TAIL) {
                // 帧头帧尾均匹配，完整帧接收成功
                // 在这里可以对接收到的完整帧进行处理
                // 例如，打印帧中的数据或者执行其他操作
            }
            // 重置状态机，等待下一个帧的接收
            rxIndex = 0;
            rxState = 0;
        }
           HAL_UART_Receive_IT(&huart1, &rxData, 1);
    }
	  if (huart->Instance == USART3) {
		 
		 if(zxdnb == 0x01)
		 {
		 Motor1_enable();a=1;
			 
		 }
		 
		 if(zxdnb == 0x02)
		 {
		 Motor1_disable();a=0;
			 
		 }
         if(zxdnb == 0x03)
		 {
		 __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,20);  //可回收
			 
		 }
		 
		 if(zxdnb == 0x04)
		 {
		 __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,10); //有害
			 
		 }
		 HAL_UART_Receive_IT(&huart3, &zxdnb, 1);

		}

   
    
}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	static uint8_t RxState = 0;
//	static uint8_t pRxPacket = 0;
//	if (huart->Instance == USART1) //        // 接收到数据，进行处理	
//	{

//		if (RxState == 0)   
//		{
//			if (rxData == 0x7F)  
//			{
//				pRxPacket = 0;
//				RxState = 1;
//			}
//		}
//		if (RxState == 1)
//		{
//			rxBuffer[pRxPacket] = rxData;   
//			pRxPacket ++;
//			if (pRxPacket >= 5)
//			{
//				RxState =2;

//			}
//		}
//		if (RxState == 2)  
//		{
//			if (rxData == 0xFF)    
//			{
//				RxState = 0;

//			}
//		}
//		HAL_UART_Receive_IT(&huart1, &rxData, 1);
//	}
//  
//}
/* USER CODE END 1 */
