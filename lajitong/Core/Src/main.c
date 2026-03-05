/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "bujin.h"
#include "control.h"
#include "stdio.h"
#include "HCSR04.h"


#define FRAME_LENGTH 5       //接收长度
extern uint8_t rxBuffer[FRAME_LENGTH]; //用于接收的数组
extern uint8_t rxData;    //接收数据，通过接收一个数据不停的数组移位实现接收多个数据

uint8_t hazardous_waste=0;//数量
uint8_t recyclable_waste=0;
uint8_t kitchen_waste=0;
uint8_t other_waste=0;

uint8_t serial_number=0;//总数量


uint8_t hazardous_waste1=0;//标志位
uint8_t kitchen_waste1=0;
uint8_t other_waste1=0;
uint8_t recyclable_waste1=0;

uint8_t waste = 0;

extern int a,b;

uint8_t youhai_yanman=0,kehuishou_yanman=0,chuyu_yanman=0,qita_yanman=0;

uint8_t kehuishouyasuo = 0;

uint32_t c=1;

uint8_t you = 0;

uint8_t ture1 = 0;

uint16_t bei=0;

uint8_t zhibei = 0;

uint8_t zxdnb = 0x00;
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
//******************************************************************串口屏发送逻辑****************************************************************
void serial_touch_screen(void)
{
	
	serial_number++;

	switch(serial_number%2) 
	{
		case 1:
		printf("page0.t15.txt=\"%d\"\xff\xff\xff",serial_number);
		printf("page0.t17.txt=\"%d\"\xff\xff\xff",1);
		printf("page0.t18.txt=\"YES\"\xff\xff\xff");
		switch(waste) 
		{
		case 1:printf("page0.t16.txt=\"厨余垃圾\"\xff\xff\xff");break;
		case 3:printf("page0.t16.txt=\"其他垃圾\"\xff\xff\xff");break;
		case 2:printf("page0.t16.txt=\"可回收垃圾\"\xff\xff\xff");break;
		case 4:printf("page0.t16.txt=\"有害垃圾\"\xff\xff\xff");break;
		}
		break; 
		
		case 0:
		printf("page0.t19.txt=\"%d\"\xff\xff\xff",serial_number);
		printf("page0.t21.txt=\"%d\"\xff\xff\xff",1);
		printf("page0.t22.txt=\"YES\"\xff\xff\xff");
		switch(waste) 
		{
		case 1:printf("page0.t20.txt=\"厨余垃圾\"\xff\xff\xff");break;
		case 3:printf("page0.t20.txt=\"其他垃圾\"\xff\xff\xff");break;
		case 2:printf("page0.t20.txt=\"可回收垃圾\"\xff\xff\xff");break;
		case 4:printf("page0.t20.txt=\"有害垃圾\"\xff\xff\xff");break;
		}
		break;  	
	}
	switch(waste)
	{
		case 1:
			kitchen_waste++;
		printf("page0.t9.txt=\"%d\"\xff\xff\xff",kitchen_waste);waste=0;break;
		case 2:
			recyclable_waste++;		
			printf("page0.t5.txt=\"%d\"\xff\xff\xff",recyclable_waste);waste=0;break;
		case 3:
			other_waste++;
			printf("page0.t7.txt=\"%d\"\xff\xff\xff",other_waste);waste=0;break;
		case 4:
			hazardous_waste++;
			printf("page0.t3.txt=\"%d\"\xff\xff\xff",hazardous_waste);waste=0;break;
	}

}
//***********************************************************外部中断回调函数***************************************************************
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(a == 1)
	{
    switch(GPIO_Pin)
  {
    //第一个传送带处
    case GPIO_PIN_5: 
			
    Motor1_disable();a=0;//第一个传送带停
		Motor2_disable();b=0;
		waste = 0;
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);  //清除中断标志 
		HAL_TIM_Base_Start_IT(&htim1);
    break;
		
    //第二个传送带处
//    case GPIO_PIN_6: 
//			
//    HAL_TIM_Base_Stop_IT(&htim2);  
//    Motor1_enable();a=1;
//		Motor2_disable();b=0;
//		if(waste != 0)
//		{	
//			serial_touch_screen();
//	  }
//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);  //清除中断标志 
//    break;
    default: break;
  }
  }
}
	
// *******************************下传送带运行4秒自动停止且串口屏显示垃圾信息*************************************************************

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
 	static uint16_t TIM1_Cnt1 = 0 , TIM1_Cnt2 = 0;
	
	
	if(htim->Instance == TIM1)
	{
		if(a==0&&b==0)
		{
		TIM1_Cnt2 ++;
	  }
		
    if(a==0&&b==1)
		{
		  TIM1_Cnt1 ++;
		  TIM1_Cnt2 = 0;
	  }
		if(a==1&&b==0)
		{
		  TIM1_Cnt1=0;
			TIM1_Cnt2 = 0;
		}
		
		if(TIM1_Cnt1 >= 4)
		{
			Motor2_disable();  b=0;
      Motor1_enable();  a=1;
				
			if(waste != 0)
			{	  
				  ture1 = 1;
					serial_touch_screen();
				  
			}
			if(waste == 0 && you == 1 && ture1 == 0)
			{
				serial_number++;
				switch((serial_number)%2) 
					{
						case 1:
						printf("page0.t15.txt=\"%d\"\xff\xff\xff",serial_number);
						printf("page0.t17.txt=\"%d\"\xff\xff\xff",1);
						printf("page0.t18.txt=\"NO\"\xff\xff\xff");
						printf("page0.t16.txt=\"无\"\xff\xff\xff");
						break; 
						
						case 0:
						printf("page0.t19.txt=\"%d\"\xff\xff\xff",serial_number);
						printf("page0.t21.txt=\"%d\"\xff\xff\xff",1);
						printf("page0.t22.txt=\"NO\"\xff\xff\xff");
						printf("page0.t20.txt=\"无\"\xff\xff\xff");
						break;  	
					}
				you=0;
			}
			ture1 = 0;
			TIM1_Cnt1 = 0;
      HAL_TIM_Base_Stop_IT(&htim1); 
      if(bei==1)
				{
					Motor2_disable();  b=0;
          Motor1_disable();  a=0;
			    zhibei = 1;
					bei = 0;
				}			
		}
		
		if(TIM1_Cnt2 >= 5)
		{

				Motor2_enable();  b=1;
				Motor1_disable();  a=0;
				TIM1_Cnt2 = 0;  
			if(waste == 0)
			{
				you = 1;
			}
				
		}
	}
//***************************************************************验满计数***********************************************************************
	if(htim->Instance == TIM8)
	{
		//*********************************************可回收*********************************************
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) == 0 && kehuishou_yanman < 11)
		{
			kehuishou_yanman++;
		}
		if(kehuishou_yanman > 5)
		{
			  printf("page0.t6.txt=\"已满\"\xff\xff\xff");
			  kehuishouyasuo = 1;
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) == 1)
		{
			if(kehuishou_yanman > 0)
			{
			  kehuishou_yanman--;
			}
		}
		if(kehuishou_yanman < 5)
		{
			  printf("page0.t6.txt=\"未满\"\xff\xff\xff");
			kehuishouyasuo = 0;
		}
		//*********************************************厨余*********************************************
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2) == 0 && chuyu_yanman < 11)
		{
			chuyu_yanman++;
		}
		if(chuyu_yanman > 5)
		{
			  printf("page0.t10.txt=\"已满\"\xff\xff\xff");
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2) == 1)
		{
			if(chuyu_yanman > 0)
			{
			  chuyu_yanman--;
			}
		}
		if(chuyu_yanman < 5)
		{
			  printf("page0.t10.txt=\"未满\"\xff\xff\xff");
		}
		//*********************************************其他*********************************************
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1) == 0 && qita_yanman < 11)
		{
			qita_yanman++;
		}
		if(qita_yanman > 5)
		{
			  printf("page0.t8.txt=\"已满\"\xff\xff\xff");
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1) == 1)
		{
			if(qita_yanman > 0)
			{
			  qita_yanman--;
			}
		}
		if(qita_yanman < 5)
		{
			  printf("page0.t8.txt=\"未满\"\xff\xff\xff");
		}
		//*********************************************有害*********************************************
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13) == 0 && youhai_yanman < 11)
		{
			youhai_yanman++;
		}
		if(youhai_yanman > 5)
		{
			  printf("page0.t4.txt=\"已满\"\xff\xff\xff");
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13) == 1)
		{
			if(youhai_yanman > 0)
			{
			  youhai_yanman--;
			}
		}
		if(youhai_yanman < 5)
		{
			  printf("page0.t4.txt=\"未满\"\xff\xff\xff");
		}
	}
}

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
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART3_UART_Init();
  MX_TIM1_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */
	
//定时器，串口初始化
  HAL_UART_Receive_IT(&huart3, &zxdnb, 1);
  HAL_UART_Receive_IT(&huart1, &rxData, 1);  //接收 ,串口中断开始接收
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);//打开对应定时器通道PB3舵机7V
  HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);//打开对应定时器通道PA6 dirPA-11 12v 
  HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);//打开对应定时器通道PA7 dirPA12 12v
  HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_1);//步进电机PB6,方向引脚PC11 12v 3.3v
  HAL_TIM_Base_Start_IT(&htim8);//打开定时器中断

//电机初始状态
  Motor4_disable();//失能步进电机
	
	Motor1_course(1);//传送带方向
  Motor2_course(1);
	
//  Motor2_enable();b=0;//初始传送带状态
//	Motor1_enable();a=1;
Motor1_disable();a=0;
Motor2_disable();b=0;
//舵机初始化状态
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,10);

//串口屏清屏
  printf("page0.t15.txt=\"无\"\xff\xff\xff"); 
  printf("page0.t16.txt=\"无\"\xff\xff\xff");
	printf("page0.t17.txt=\"无\"\xff\xff\xff"); 
  printf("page0.t18.txt=\"无\"\xff\xff\xff");
  printf("page0.t19.txt=\"无\"\xff\xff\xff"); //清除屏幕
  printf("page0.t20.txt=\"无\"\xff\xff\xff");
	printf("page0.t21.txt=\"无\"\xff\xff\xff"); 
  printf("page0.t22.txt=\"无\"\xff\xff\xff");
  printf("page0.t9.txt=\"%d\"\xff\xff\xff",0);
	printf("page0.t5.txt=\"%d\"\xff\xff\xff",0);
	printf("page0.t7.txt=\"%d\"\xff\xff\xff",0);
	printf("page0.t3.txt=\"%d\"\xff\xff\xff",0);
	printf("page0.t4.txt=\"未满\"\xff\xff\xff");
	printf("page0.t6.txt=\"未满\"\xff\xff\xff");
	printf("page0.t8.txt=\"未满\"\xff\xff\xff");
	printf("page0.t10.txt=\"未满\"\xff\xff\xff");
	printf("page0.t23.txt=\"未启动\"\xff\xff\xff");
	
	maichong4(-140000);
	HAL_Delay(3000);

//压缩测试代码: 
//			maichong4(140000); 
//			HAL_Delay(8000);
//			maichong4(-140000);
//			HAL_Delay(8000);
//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
//HAL_Delay(9000);
//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
//HAL_Delay(9000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
//***********************************************************可回收垃圾压缩并恢复初始状态************************************************************************
//		if(kehuishouyasuo == 1)
//		{
//			Motor2_disable(); 
//			Motor1_disable();
//			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,15);
//			HAL_Delay(3000);
//			maichong4(140000); 
//			HAL_Delay(8000);
//			maichong4(-160000);
//			HAL_Delay(8000);
//			Motor2_disable(); b=0;
//			Motor1_enable(); a=1;
//			kehuishouyasuo = 0;
//		}
		 
     if(zhibei == 1)
		 {
			Motor2_disable(); 
			Motor1_disable();
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,15);
			HAL_Delay(3000);
			maichong4(140000); 
			HAL_Delay(8000);
			maichong4(-160000);
			HAL_Delay(8000);
			Motor2_disable(); b=0;
			Motor1_enable(); a=1;
			zhibei = 0;
		 }
			
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
// 
/********************************************************************************判断垃圾种类执行对应反馈******************************************************************************************/
	    switch(rxBuffer[FRAME_LENGTH-2])
    {
        case 1:

        waste=1;
//        kitchen_waste++;
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,25);  //厨余
				HAL_Delay(1000);
				Motor2_course(1); 
				Motor2_enable();  b=1; 
				Motor1_disable();  a=0;
				HAL_Delay(1000);
				HAL_TIM_Base_Start_IT(&htim1);			
        rxBuffer[FRAME_LENGTH-2] = 0;


        break;
				
        case 3:

					waste=3;
        other_waste1=1;
//			  other_waste++;
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,15);  //其他
				HAL_Delay(1000);
				Motor2_course(1); 
				Motor2_enable(); b=1;  
        Motor1_disable();  a=0;
				HAL_Delay(1000);
				HAL_TIM_Base_Start_IT(&htim1);			
        rxBuffer[FRAME_LENGTH-2] = 0;

        break;
				
        case 2:

					waste=2;
			  recyclable_waste1=1;
//				recyclable_waste++;
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,20);  //可回收
				HAL_Delay(1000);
				Motor2_course(1); 
				Motor2_enable(); b=1;  
        Motor1_disable();  a=0;
				HAL_Delay(1000);
				bei = 1;
				HAL_TIM_Base_Start_IT(&htim1);
        rxBuffer[FRAME_LENGTH-2] = 0;


			
        break;
				
        case 4:

					waste=4;
        hazardous_waste1=1;
//				hazardous_waste++;
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,10); //有害
				HAL_Delay(1000);
				Motor2_course(1); 
				Motor2_enable(); b=1; 
        Motor1_disable();  a=0;
				HAL_Delay(1000);
				HAL_TIM_Base_Start_IT(&htim1);			
        rxBuffer[FRAME_LENGTH-2] = 0;

        break;
//***********************************************打开yolov5后重新初始系统***********************************************************************************
				case 9:
				Motor2_disable(); b=0;  
        Motor1_enable();  a=1;
				printf("page0.t23.txt=\"已启动\"\xff\xff\xff");	
        rxBuffer[FRAME_LENGTH-2] = 0;
        break;
        default: break;        
    }
  }
  /* USER CODE END 3 */
}

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
