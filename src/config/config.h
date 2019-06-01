#ifndef __CONFIG__
#define __CONFIG

/*	count = seconds * frequency */

/* REAL VALUES*/
//#define PEDESTRIAN_TO_FLASHING 0xABA9500 /*15"*/
//#define PEDESTRIAN_TO_RED 0x3938700 		 /*5"*/
//#define CAR_TO_YELLOW 0x3938700 				 /*5"*/
//#define CAR_TO_RED 0x3938700						 /*5"*/
//#define FLASHING_TIME 0x5B8D80					 /*0.5"*/


/* DEBUG VALUES = REAL VALUES /50			 */
#define PEDESTRIAN_TO_FLASHING 0x800
#define PEDESTRIAN_TO_RED 0x500 		 
#define CAR_TO_YELLOW 0x500 				 
#define CAR_TO_RED 0x500						 
#define BLINKING_TIME 0x200					 

#define NORMAL_TIMER 0									 
#define	BLINKING_TIMER 1

enum leds{RedPed=7, GreenPed=6, RedCar=5, YellowCar=4, GreenCar=3}; 
enum states{GoPedestrian = 0, ChangingPed = 1, GoCar = 2, ChangingCar = 3};

#endif
