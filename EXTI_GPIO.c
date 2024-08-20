/*
 * EXTI.c
 *
 *  Created on: Jul 25, 2024
 *      Author: ahmed
 */

#include "stm32wle5xx.h"
#include "EXTI_GPIO.h"
#include "Timer.h"
#include "main.h"

void GPIO_PINx_EXTI_Init(void){

	//Disable ISR
	__disable_irq();
	//Enable clock Sources For Port A , B
	RCC->AHB2ENR |= 1;
	RCC->AHB2ENR |= 2;


	//Select Port C from 0x2  and [3] for PIN 13
	SYSCFG->EXTICR[0] = 0x00;

	//unmask EXTI0
	EXTI->IMR1 |= 0x01;

	//Select Falling Edge trigger
	EXTI->FTSR1 |= 0x01;

	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 1);
	NVIC_EnableIRQ(EXTI0_IRQn);
	__enable_irq();

}


void EXTI0_callback(void){
	//When micro 		1.  wake-up  set PIN 15 to High
	HAL_GPIO_WritePin(GPIOB, ZB_STATE_GPIO_Pin, GPIO_PIN_RESET);
	//When micro 		2.  wake-up  set PIN 15 to High
	TIM_Start();
}
void EXTI0_IRQHandler(void){
	EXTI0_callback();
	EXTI->PR1 = 0x01;
}
