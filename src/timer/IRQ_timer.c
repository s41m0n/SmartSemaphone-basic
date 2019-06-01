/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"
#include "../config/config.h"
#include "../led/led.h"

extern enum states currentState;
int isGreenPedOn = 1;

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void)
{	 
	switch(currentState){
		case GoPedestrian: {
			currentState = ChangingPed;
			init_timer(NORMAL_TIMER, PEDESTRIAN_TO_RED);
			init_timer(BLINKING_TIMER, BLINKING_TIME);
			enable_timer(BLINKING_TIMER);
			enable_timer(NORMAL_TIMER);
			break;
		};
		case ChangingPed: {
			disable_timer(BLINKING_TIMER);
			reset_timer(BLINKING_TIMER);
			isGreenPedOn = 1;
			currentState = GoCar;
			init_timer(NORMAL_TIMER, CAR_TO_YELLOW);
			LED_Off(GreenPed);
			LED_Off(RedCar);
			LED_On(RedPed);
			LED_On(GreenCar);
			break;
		};
		case GoCar: {
			LED_Off(GreenCar);
			LED_On(YellowCar);
			currentState = ChangingCar;
			init_timer(NORMAL_TIMER, CAR_TO_RED);
			enable_timer(NORMAL_TIMER);
			break;
		};
		case ChangingCar:{
			LED_Off(YellowCar);
			LED_Off(RedPed);
			LED_On(RedCar);
			LED_On(GreenPed);
			currentState = GoPedestrian;
			init_timer(NORMAL_TIMER, PEDESTRIAN_TO_FLASHING);
			enable_timer(NORMAL_TIMER);
			break;
		};
		default: break;
	}	
	LPC_TIM0->IR = 1;			/* clear interrupt flag */
	return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	if(isGreenPedOn)
		LED_Off(GreenPed);
	else
		LED_On(GreenPed);
	isGreenPedOn = !isGreenPedOn;
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
