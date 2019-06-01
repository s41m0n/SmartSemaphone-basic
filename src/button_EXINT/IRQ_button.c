#include "button.h"
#include "lpc17xx.h"
#include "../led/led.h"
#include "../timer/timer.h"
#include "../config/config.h"

extern enum states currentState;
extern int isGreenPedOn;

void buttonPressed() {
	switch(currentState){
		/*Reset timer and stay in this state*/
		case GoPedestrian: {
			reset_timer(NORMAL_TIMER);
			enable_timer(NORMAL_TIMER);
			break;
		};
		/*Go back into the normal green for pedestrian (GoPedestrian state)*/
		case ChangingPed: {
			disable_timer(BLINKING_TIMER);
			reset_timer(BLINKING_TIMER);
			currentState = GoPedestrian;
			if(!isGreenPedOn){
				isGreenPedOn = !isGreenPedOn;
				LED_On(GreenPed);
			}
			reset_timer(NORMAL_TIMER);
			init_timer(NORMAL_TIMER, PEDESTRIAN_TO_FLASHING);
			enable_timer(NORMAL_TIMER);
			break;
		};
		/*Start the timer if it is not started yet*/
		case GoCar: {
			enable_timer(NORMAL_TIMER);
			break;
		};
		/*Perform a NOP as it is already changing state (going into GoPedestrian state)*/
		case ChangingCar:{
			__ASM("NOP");
			break;
		};
		default: break;
	}
	return;
}

void EINT1_IRQHandler (void)	  	/* KEY1, bit 11											 */
{
		buttonPressed(); 	
		LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2, bit 12											 */
{
		buttonPressed();
  	LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}
