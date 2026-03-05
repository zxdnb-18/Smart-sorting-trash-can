#ifndef __CONTROL_H
#define __CONTROL_H


#include "gpio.h"
/**************步进电机******************/
void Motor4_course(char course_mod);
void Motor4_enable(void);
void Motor4_disable(void);

void maichong4(int mb);
//void chengxu1(void);
/***************传送带直流电机****************/
void Motor1_course(char course_mod);
void Motor1_enable(void);
void Motor1_disable(void);
void Motor2_course(char course_mod);
void Motor2_enable(void);
void Motor2_disable(void);

void xunhuan(void);
void duoji(uint16_t q);
#endif
