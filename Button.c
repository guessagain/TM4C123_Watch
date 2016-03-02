#include "TM4C123GH6PM.h"

void Button_init()
{
	SYSCTL->RCGC2 |= 0x02;
	GPIOB->LOCK = 0x4C4F434B;
	GPIOB->AMSEL = 0x00;
	GPIOB->PCTL =0x00;
	GPIOB->DIR |=0x00;
	GPIOB->DEN |=0x40;
	GPIOB->PDR |=0x40;
	GPIOB->IEV |=0x40;
	GPIOB->IM |= 0x40;
	NVIC_EnableIRQ(1);
}
