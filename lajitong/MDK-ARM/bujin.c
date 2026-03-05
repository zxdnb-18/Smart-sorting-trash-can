#include "bujin.h"
#include "stm32f1xx_it.h"
void Motor1_course(char course_mod)			// 电机改变方向
{
	if(course_mod == 1){HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);}
	else if(course_mod == 0){HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);}
}
void Motor1_enable(void)			// 电机使能
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
}
void Motor1_disable(void)			// 电机失能
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
}

