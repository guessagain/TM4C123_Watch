// Nokia5110TestMain.c
// Runs on LM4F120/TM4C123
// Test the functions in Nokia5110.c by printing various
// things to the LCD.
// Daniel Valvano
// September 16, 2013

// Font table, initialization, and other functions based
// off of Nokia_5110_Example from Spark Fun:
// 7-17-2011
// Spark Fun Electronics 2011
// Nathan Seidle
// http://dlnmh9ip6v2uc.cloudfront.net/datasheets/LCD/Monochrome/Nokia_5110_Example.pde

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013

 Copyright 2013 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// Blue Nokia 5110
// ---------------
// Signal        (Nokia 5110) LaunchPad pin
// Reset         (RST, pin 1) connected to PA7
// SSI0Fss       (CE,  pin 2) connected to PA3
// Data/Command  (DC,  pin 3) connected to PA6
// SSI0Tx        (Din, pin 4) connected to PA5
// SSI0Clk       (Clk, pin 5) connected to PA2
// 3.3V          (Vcc, pin 6) power
// back light    (BL,  pin 7) not connected
// Ground        (Gnd, pin 8) ground

// Red SparkFun Nokia 5110 (LCD-10168)
// -----------------------------------
// Signal        (Nokia 5110) LaunchPad pin
// 3.3V          (VCC, pin 1) power
// Ground        (GND, pin 2) ground
// SSI0Fss       (SCE, pin 3) connected to PA3
// Reset         (RST, pin 4) connected to PA7
// Data/Command  (D/C, pin 5) connected to PA6
// SSI0Tx        (DN,  pin 6) connected to PA5
// SSI0Clk       (SCLK, pin 7) connected to PA2
// back light    (LED, pin 8) not connected

#include "Nokia5110.h"
#include "PLL.h"
#include "TM4C123GH6PM.h"
#include "glcd_5110.h"
#include "Button.h"

unsigned int clock_tick = 0,second=0,minutes=0,hours=0,S_angle=270, M_angle=270,H_angle = 270,display_changed=0,bounce=0;
enum Clock_status{
	ANALOG,
	DIGITAL,
};
enum Clock_status Button=0;

//Configure SYSTICK timer for 100ms interrupt. 
void Clock_100ms(void)
{
	SysTick->LOAD = 0x4C4B3F;
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk; 
	SysTick->VAL   = 0UL;
}

void Analog_display()
{
	Clock_second(S_angle);
	Clock_minutes(M_angle);
	Clock_hours(H_angle);
}

void Digital_display()
{
	Digital_second( second);
	Digital_minutes( minutes);
	Digital_hours( hours);
}


void GPIOB_Handler(void)
{
	
	Button ^= 0x01;
	if (Button  == ANALOG)
	{
		Nokia5110_Clear();										// Clear the LCD.
		Clock_dial();													// Draw clock dil on LCD. 
		Analog_display();
	}	
	else if (Button == DIGITAL)
	{
		Nokia5110_Clear();										// Clear the LCD.
		Digital_display();
	}
	display_changed =1;
	GPIOB->IM &= (~0x40);
	GPIOB->ICR |= 0x40;
}

//SYSTICK handler subroutine for second, minutes and hours update. 
void SysTick_Handler(void)
{
	clock_tick++;
	if (clock_tick ==10)
	{
		clock_tick =0;
		second++;
		S_angle += 6; 
		if(second == 60)
		{
			minutes++;
			M_angle += 6;
			S_angle = 270; 
			second =0;
			if(minutes == 60)
			{
				minutes =0;
				M_angle = 270;
				hours++;
				H_angle +=30;
				if(hours==12)
				{
					hours =0;
					H_angle +=270;
				}	
			}	
		}
		
	if (Button  == ANALOG)
	{
		Analog_display();
	}	
	else if (Button == DIGITAL)
	{
		Digital_display();
	}
	
	}
	if(display_changed==1)
	{
		bounce++;
		if(bounce==5)
		{
		NVIC_ClearPendingIRQ(1);
		GPIOB->ICR = 0x40;
		GPIOB->IM |= 0x40;
		display_changed=0;
		bounce=0;
		}
	}
}


int main(void){
  PLL_Init();                           // set system clock to 50 MHz
  Nokia5110_Init();											// Initialize LCD 
	Clock_100ms();												// Configure SYSTICK for 100ms interrupt. 
  Nokia5110_Clear();										// Clear the LCD.
	Clock_dial();													// Draw clock dil on LCD. 
	Clock_minutes(M_angle);								// Draw minute hand on the dial.
	Clock_hours(H_angle);									// Draw hour hand on the dial. 
	Button_init();
	
  while(1);
}
