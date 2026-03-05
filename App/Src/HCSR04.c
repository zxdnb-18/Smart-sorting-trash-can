//#include "HCSR04.h"

//#define TRIG_PIN GPIO_PIN_15
//#define TRIG_PORT GPIOB
//#define ECHO_PIN GPIO_PIN_0
//#define ECHO_PORT GPIOA

//uint32_t pMillis;
//uint32_t start = 0;
//uint32_t end = 0;
//float distance = 0;
//char string[15];

//void HCSR04_Init(void)
//{
//	HAL_TIM_Base_Start(&htim5);
//	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);
//}

//float HCSR04_Read(void)
//{
//	start=0;
//	end=0;
//	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_SET);//拉高TRIG_PIN，开始发射脉冲
//	__HAL_TIM_SET_COUNTER(&htim5, 0);//重置定时器
//	while (__HAL_TIM_GET_COUNTER(&htim5) < 10)//等待10us
//		; 
//	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);// 关闭超声波传感器的 TRIG_PIN 引脚，停止发射脉冲信号

//	pMillis = HAL_GetTick();// 记录当前时间（以毫秒为单位）
//	while (!(HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN)) && pMillis + 10 > HAL_GetTick())// 等待直到 ECHO_PIN 引脚开始接收到回波信号，或者超过 10 毫秒的时间
//		;
//	start = __HAL_TIM_GET_COUNTER(&htim5);//记录 ECHO_PIN 开始接收到回波信号时的计数器值

//	pMillis = HAL_GetTick();// 继续记录当前时间（以毫秒为单位）
//	while ((HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN)) && pMillis + 50 > HAL_GetTick())// 等待直到 ECHO_PIN 引脚停止接收到回波信号，或者超过 50 毫秒的时间
//		;
//	end = __HAL_TIM_GET_COUNTER(&htim5);// 记录 ECHO_PIN 停止接收到回波信号时的计数器值

//	distance = (end - start) * 0.034 / 2;// 计算距离值（单位：厘米），声波的传播速度约为 0.034 厘米/微秒
//	return distance;
//}



//// 测量的数据并不总是准确，这里提供一个可供参考的解决方法
//// 将一定时间内采集到的数据，先存起来，再做一个排序，去除最大值和最小值，也可以多去除几个极端值，然后取平均

//// 会影响到测量结果的因素有很多：气温、气压、湿度等会影响声音在大气中传播的速度(distance = v * t)

//// 此外由于驱动函数是直接操作GPIO口进行翻转，再延时等待以完成通信协议，而这一系列操作都会影响到接受数据的解析
////更为精准的一种方式应该是输入捕获采集脉冲变化，若还要更精准，可以使用不同的通道分别采集上升和下降沿，这样可以减小一些误差
//// 还有就是模块和被测物体的相对位置，若偏了或者其他原因造成声波的反射都会影响到正确的测量结果
////0.034 = 340 * 10^2 / 10^6
