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
		if ((data[1] >= 0) && (data[1] <= 180))
			camPosition[0] = Func_map(data[1], 0, 180, 2000, 4000);
		else return false;
		
		if ((data[2] >= 0) && (data[2] <= 180))
			camPosition[1] = Func_map(data[2], 0, 180, 2000, 4000);
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
		WriteServo(3000,3000);
}