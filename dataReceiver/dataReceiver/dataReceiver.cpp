/*
 * dataReceiver.h
 *
 * Created: 02/10/2013 14:40:45
 *  Author: Antoine
 */
 

#include "dataReceiver.h"

volatile uint8_t Data_RX[3]         = {0};
volatile static uint8_t nb_INT      =  0;
const uint8_t Data_RX_format[3]     = {0xFF, 0xAA, 0xEE};
volatile uint8_t DataCamPosition[2] = {94, 94};

int main(void)
{
	uint8_t i;
	
	//Initialization
	I2C_Init();
	Xbee_Init();
	timer1_Init();
	
	while(1)
	{
		if (nb_INT == 3)
		{
			for (i = 0 ; i<3 ; i++)
				if (Data_RX[i] != Data_RX_format[i])
					break;
			
			if (i == 3)	SendDataCam();
		}
	}
   
}

void ioInit( void )
{
	
}

void SendDataCam(void)
{
	Xbee_transmit_data();
	Xbee_transmit_data();
	Xbee_transmit_data();
	Xbee_transmit_data();
}

ISR(USART_RX_vect)
{
	nb_INT++;
	
	switch (i)
	{
		case 1: Data_RX[i] = UDR0;
		break;
		
		case 2: Data_RX[i] = UDR0;
		break;
		
		case 3: Data_RX[i] = UDR0;
		break;
	}
}

ISR(TIMER1_OVF_vect)
{
	
}

void timer1_Init( void )
{
	TCCR1A = 0x02;
	TCCR1B = 0x1A;
	TIMSK1 = 0x01;
	
	ICR1   = 19999;	
}
