/*
 * Robot.cpp
 *
 * Created: 02/10/2013 13:42:15
 *  Author: ClementC
 */ 


#include "Robot.h"

volatile uint64_t microseconds    =  0;
volatile uint16_t RC_Values[5]    = {0};

int main(void)
{
	cli();
	
	// Initialisations
	ioInit();
	I2C_Init();
	timer1_Init();
	ServoInit();
	
	sei();
	
    while(1)
    {
		
    }
}

void ioInit(void)
{
	DDRB  |= 0b00000110;
}

void timer1_Init(void)
{
	TCCR1A = 0x12; // COM1A1 | COM1B1 | WGM11 | WGM10
	TCCR1B = 0x4C; // ICES1  | WGM12  | CS12
	TIMSK1 = 0x20; // ICIE1
}

ISR(TIMER1_CAPT_vect)
{
	volatile static uint16_t RC_Values_LAST = 0;
	volatile static uint8_t  Channel		= 0;
	volatile        uint16_t temp			= 0;

	temp = ICR1;
	Channel++;

	switch (Channel)
	{
		case 1: break;
		
		case 2: if (temp > RC_Values_LAST) RC_Values[Channel-1] = temp-RC_Values_LAST;
				else 					   RC_Values[Channel-1] = 1023-RC_Values_LAST+temp;
				RC_Values[Channel-1] = (RC_Values[Channel-1] - 63) * (2000 - 1000) / (125 - 63) + 125;
				break;
				
		case 3: if (temp > RC_Values_LAST) RC_Values[Channel-1] = temp-RC_Values_LAST;
				else 					   RC_Values[Channel-1] = 1023-RC_Values_LAST+temp;
				RC_Values[Channel-1] = (RC_Values[Channel-1] - 63) * (2000 - 1000) / (125 - 63) + 125;
				break;
				
		case 4: if (temp > RC_Values_LAST) RC_Values[Channel-1] = temp-RC_Values_LAST;
				else 					   RC_Values[Channel-1] = 1023-RC_Values_LAST+temp;
				RC_Values[Channel-1] = (RC_Values[Channel-1] - 63) * (2000 - 1000) / (125 - 63) + 125;
				break;
				
		case 5: if (temp > RC_Values_LAST) RC_Values[Channel-1] = temp-RC_Values_LAST;
				else 					   RC_Values[Channel-1] = 1023-RC_Values_LAST+temp;
				RC_Values[Channel-1] = (RC_Values[Channel-1] - 63) * (2000 - 1000) / (125 - 63) + 125;
				break;
				
		case 6: if (temp > RC_Values_LAST) RC_Values[Channel-1] = temp-RC_Values_LAST;
				else 					   RC_Values[Channel-1] = 1023-RC_Values_LAST+temp;
				RC_Values[Channel-1] = (RC_Values[Channel-1] - 63) * (2000 - 1000) / (125 - 63) + 125;
				Channel = 0;
				break;
	}
	
	RC_Values_LAST = temp;
}

void timer2_Init(void)
{
	TCCR2A = 0x02; // WGM21
	TCCR2A = 0x01; // CS20
	OCR2A  = 0x10; // OCR2A = TOP = 16
	TIMSK2 = 0x01; // TOIE2 = Interrupt on overflow
}

ISR(TIMER2_OVF_vect)
{
	cli();
	microseconds++;
	sei();
}