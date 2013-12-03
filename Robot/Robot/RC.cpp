/*
 * RC.cpp
 *
 * Created: 05/10/2013 12:07:36
 *  Author: ClementC
 */ 

#include "Robot.h"

void RC_Init(void)
{
	// initialisation du timer3 pour IC
	timer3_Init();
}

void timer3_Init(void)
{
	TCCR3A = 0;
	TCCR3B = 1<<ICES3 | 1<<CS31;
	TIMSK3 = 1<<ICIE3;
	TIFR3  = 0xFF;
}

ISR(TIMER3_CAPT_vect)
{
	volatile static uint8_t  chan = 0;
	volatile		uint16_t temp = 0;
	
	temp = ICR3 / 2;
	TCNT3 = 0;
	
	sei();
	
	if (temp > 3000)
	chan = 0;
	
	if (temp >= 800 && temp <= 2200)
	RC_Values[chan] = temp;
	
	chan++;
}

