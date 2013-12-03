/*
 * Robot.cpp
 *
 * Created: 11/11/2013 14:27:36
 *  Author: ClementC
 */

#include "Robot.h"

volatile uint16_t RC_Values[6]   = {0};
volatile uint16_t camPosition[2] = {1500, 1500};
volatile uint8_t  UART_RX[4]	 = {0};
volatile uint8_t  UART_TX[12]	 = {0x46, 0x75, 0x63, 0x6B, 0x69, 0x6E, 0x67, 0x20, 0x74, 0x72, 0x79, 0x0D};
volatile int16_t  U1			 = 0;
volatile int16_t  U2			 = 0;

int main(void)
{
	PRR1 |= 0x80; // désactivation indispensable du module USB non utilisé !!

	// Initialisations
	ioInit();
	Xbee_Init();
	RC_Init();
	I2C_Init();
	ServoInit();
	MoteurInit();
	
	sei();
	
	while(1)
	{
		/*if (ReceiveCamPosition(10000))   // Routine de réception des données séries
			WriteCamPosition();		// recalibrage de l'azimut de balayage
		else
			WriteCamPosition(TIMEOUT);
		
		AcquireDataSensor();
		SendDataSensor();*/
		computeMotors();
	}
}

void ioInit(void)
{
	DDRB |= 0b11110000;
	DDRC  = 0b01000000;
	DDRD |= 0b10011000;
	DDRE |= 0b01000000;
}

void timer0_Init(void) // interruption toutes les 5 * 4ms
{
	TCCR0A = _BV(WGM01 );
	TCCR0B = _BV(CS02  );
	OCR0A  = 250;
	TIMSK0 = _BV(OCIE0A);
	TIFR0  = 0xFF;
}

ISR(TIMER0_COMPA_vect)
{
	
}

void AcquireDataSensor(void)
{
	
}

void SendDataSensor(void)
{
	
}

uint8_t Func_map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}