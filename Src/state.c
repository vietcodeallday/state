/*
 * state.c
 *
 *  Created on: Oct 24, 2023
 *      Author: quocv
 */
#include "main.h"
#include "state.h"
#include "stm32f1xx_it.h"
static state_t State;

void init_State()
{
	State = OFF_LED;
}
void state_Machine_Update(void){
	switch (State){
	case OFF_LED:
		LL_GPIO_ResetOutputPin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);
		//if (LL_GPIO_IsInputPinSet(BUTTON_GPIO_Port,BUTTON_Pin)){
			sysTickCounter=0;
			State = OFF_PRESSED;
		//}
		break;
	case OFF_PRESSED:
		if (sysTickCounter>=30000){
			State = ON_LED;
		}
		break;
	case ON_LED:
		LL_GPIO_SetOutputPin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);
		//if (LL_GPIO_IsInputPinSet(BUTTON_GPIO_Port,BUTTON_Pin)){
			sysTickCounter=0;
			State = ON_PRESSED;
		//}
		State = ON_PRESSED;
		break;
	case ON_PRESSED:
		if (sysTickCounter>=60000){
			State = OFF_LED;
		}
		break;
	}
}

