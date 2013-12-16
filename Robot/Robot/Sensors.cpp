/*
 * Sensors.cpp
 *
 * Created: 03/12/2013 17:22:56
 *  Author: ClementC
 */

#include "Robot.h"
 
ISR(USART1_TX_vect)
{
	volatile static uint8_t Cursor = 1;
	volatile static uint8_t count = 0;

	count++;

	//_sensorCom_ready = (count == 100) ? true : false;
	
	UDR1 = UART_TX[Cursor]; // arrête tes conneries U_u
	
	if (Cursor == (NB_TX-1))
	{
		UCSR1B &= ~(1<<TXC1);
		Cursor = 1;
		_sensorCom_ready = true;
	}
	else
		Cursor++;
}

void SensorInit(void)
{
	TSL2561_Init();
	MPL3115A2_Init();
}

void AcquireDataSensor(void)
{
	// Commençons par le capteur de luminosité
	Read_TSL2561_data();
	Read_MPL3115A2_data();
	_sensorCom_ready = false;
}