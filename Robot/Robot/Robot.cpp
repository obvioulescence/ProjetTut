/*
 * Robot.cpp
 *
 * Created: 02/10/2013 13:42:15
 *  Author: ClementC
 */ 


#include "Robot.h"

int main(void)
{
	// Initialisations
	cli();
	ioInit();
	I2C_Init();
	ReceptionRCInit();
	
    while(1)
    {
        
    }
}

ISR(PCINT0_vect)
{
	
}

void ioInit(void)
{
	DDRB  |= 0b00000010;
}

void ReceptionRCInit(void)
{
	while (PINB & 0x02);
}

void timer0_Init(void)
{
	TCCR0A = 0x02;
	TCCR0B = 0x01;
	OCR0A  = 0x14;
}
