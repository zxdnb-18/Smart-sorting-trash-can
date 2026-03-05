#include "control.h"
#include "stm32f1xx_it.h"
#include "tim.h"
#include "control.h"
#include "stdio.h"

int a=0,b=0;
volatile extern int PWM_num4;
volatile extern int mai4;
volatile extern int mubiao4;
uint16_t mansu= 5;
int flag=1;


//void Motor4_course(char course_mod)			// 电机4改变方向
//{
//	if(course_mod == 1){HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);}
//	else if(course_mod == 0){HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);}
//}

void Motor4_course(char course_mod)			// 支流推杆电机4改变方向
{
	if(course_mod == 1){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
	}
	else if(course_mod == 0){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	}
}

void Motor1_course(char course_mod)			// 传送带1改变方向
{
	if(course_mod == 1){HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);}
	else if(course_mod == 0){HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);}
}
void Motor2_course(char course_mod)			// 传送带2改变方向
{
	if(course_mod == 1){HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);}
	else if(course_mod == 0){HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);}
}


void Motor4_enable(void)			// 电机4使能
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
}


void Motor4_disable(void)			// 电机4失能
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
}
void Motor1_enable(void)			// 传送带1使能
{
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
}
void Motor1_disable(void)			// 传送带1失能
{
    HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
}
void Motor2_enable(void)			// 传送带2使能
{
	  HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);
}
void Motor2_disable(void)			// 传送带2失能
{
    HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_2);
}

/*******************************************控制步进电机朝不同方向旋转固定时间****************************************************/
/**********************************通过PWM_num4的值和参数比较控制不同的方向********************************************************/
void maichong4(int mb)
{
	mubiao4=mb;
	mb=0;
	if(mubiao4 > 0)
	{
		Motor4_course(1);     //0/1不同方向
		mai4=1;//定时器中断回调函数PWM_num4++
		HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_2);//开启定时器
	}
	else if(mubiao4 < 0)
	{
		Motor4_course(0);     
		mai4=0;
		HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_2);
	}
}

//void chengxu1(void)
//{	
//	__HAL_TIM_SET_AUTORELOAD(&htim4, 50);	
//	maichong4(50000);//通过调参数值，控制开启定时器的时间
//	HAL_Delay(3000);

//	htim4.Init.Prescaler = 50-1;
//	
//}
