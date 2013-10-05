/*
 * RC.cpp
 *
 * Created: 05/10/2013 12:07:36
 *  Author: ClementC
 */ 

#include "Robot.h"

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
				RC_Values[Channel-1] = Func_map(RC_Values[Channel-1], 63, 125, 1000, 2000);
		break;
		
		case 3: if (temp > RC_Values_LAST) RC_Values[Channel-1] = temp-RC_Values_LAST;
				else 					   RC_Values[Channel-1] = 1023-RC_Values_LAST+temp;
				RC_Values[Channel-1] = Func_map(RC_Values[Channel-1], 63, 125, 1000, 2000);
		break;
		
		case 4: if (temp > RC_Values_LAST) RC_Values[Channel-1] = temp-RC_Values_LAST;
				else 					   RC_Values[Channel-1] = 1023-RC_Values_LAST+temp;
				RC_Values[Channel-1] = Func_map(RC_Values[Channel-1], 63, 125, 1000, 2000);
		break;
		
		case 5: if (temp > RC_Values_LAST) RC_Values[Channel-1] = temp-RC_Values_LAST;
				else 					   RC_Values[Channel-1] = 1023-RC_Values_LAST+temp;
				RC_Values[Channel-1] = Func_map(RC_Values[Channel-1], 63, 125, 1000, 2000);
		break;
		
		case 6: if (temp > RC_Values_LAST) RC_Values[Channel-1] = temp-RC_Values_LAST;
				else 					   RC_Values[Channel-1] = 1023-RC_Values_LAST+temp;
				RC_Values[Channel-1] = Func_map(RC_Values[Channel-1], 63, 125, 1000, 2000);
				Channel = 0;
				receptionRC_OK = true;
		break;
	}
	
	RC_Values_LAST = temp;
}