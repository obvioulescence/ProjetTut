/*
 * Camera.cpp
 *
 * Created: 05/10/2013 18:52:14
 *  Author: ClementC
 */

#include "Robot.h"

void RequireCamPosition(void)
{
	Xbee_transmit_data(0xFF);
	Xbee_transmit_data(0xAA);
	Xbee_transmit_data(0xEE);
}

bool ReceiveCamPosition(void)
{
	uint16_t temp    =  0;
	uint8_t  data[4] = {0};

	for (uint8_t i = 0 ; i<4 ; i++)
	{
		temp = Xbee_ReceiveByte(200);
			if (temp == 0x0100) return false;
			else data[i] = temp;
	}
	
	if ((data[0] == 0xFF) && (data[3] == 0xEE))
	{
		if ((data[1] >= 63) && (data[1] <= 125))
			camPosition[0] = data[1];
		else return false;
		
		if ((data[2] >= 63) && (data[2] <= 125))
			camPosition[1] = data[2];
		else return false;
	}
	else return false;
	
	return true;
}

void WriteCamPosition(void)
{
	
}