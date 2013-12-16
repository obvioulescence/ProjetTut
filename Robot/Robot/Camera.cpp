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

ISR(USART1_RX_vect)
{
	volatile static uint8_t Cursor = 0;

	UART_RX[Cursor] = UDR1;

	if (Cursor == (NB_RX-1))
	{
		Cursor = 0;
		UCSR1B |= (1<<TXC1);
		UDR1 = UART_TX[0];		// Début de la phase TX
	}
	else
		Cursor++;
}

bool ReceiveCamPosition(uint16_t timeout)
{
	uint16_t temp    =  0;
	uint8_t  data[4] = {0};

	for (uint8_t i = 0 ; i<4 ; i++)
	{
		temp = Xbee_ReceiveByte(timeout);
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

void WriteCamPosition(bool timeout)
{
	if (!timeout)
		WriteServo(camPosition[0], camPosition[1]);
	else
		WriteServo(1500,1500);
}