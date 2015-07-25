#ifndef __ReceiveInfared_H
#define __ReceiveInfared_H

#include "stm32f10x.h"

//#define START_TIME  time=0;RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);TIM_Cmd(TIM2, ENABLE)
#define START_TIME  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);TIM_Cmd(TIM2, ENABLE)
#define STOP_TIME  TIM_Cmd(TIM2, DISABLE);RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE)

void TIM_NVIC_Configuration(void);
void TIM_Configuration(void);
void GPIO_Configuration(void);
void TIM3_Configuration(void);
void TIM3_NVIC_Configuration(void);
#endif
