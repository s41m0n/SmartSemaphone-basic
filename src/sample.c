/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: to control led through EINT buttons
 * Note(s):
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------  */
                  
#include <stdio.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                  */
#include "led/led.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include "config/config.h"

enum states currentState = GoPedestrian;

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
  	
		SystemInit();  						  						/* System Initialization (i.e., PLL)  */
  	LED_init();                           	/* LED Initialization                 */
  	BUTTON_init();						  						/* BUTTON Initialization              */
	
		LED_On(GreenPed);
		LED_On(RedCar);
	
		init_timer(NORMAL_TIMER, PEDESTRIAN_TO_FLASHING);	/* TIMER0 Initialization              */
		enable_timer(NORMAL_TIMER);
	
		LPC_SC->PCON |= 0x1;				  					/* power-down	mode					*/
		LPC_SC->PCON &= 0xFFFFFFFFD;						
		
  	while (1) {                           	/* Loop forever                       */	
			__ASM("wfi");
  	}

}
