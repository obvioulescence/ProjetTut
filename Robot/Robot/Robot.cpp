/*
 * Robot.cpp
 *
 * Created: 02/10/2013 13:42:15
 *  Author: ClementC
 */ 

#include "Robot.h"

volatile uint64_t microseconds    =  0;
volatile uint16_t RC_Values[5]    = {0};
volatile bool     receptionRC_OK  = false;
volatile uint16_t camPosition[2]  = {94, 94};

int main(void)
{
	cli();
	
	// Initialisations
	ioInit();
	I2C_Init();
	Xbee_Init();
	timer1_Init();
	ServoInit();
	
	sei();
	
    while(1)
    {
		if (receptionRC_OK)
		{
			RequireCamPosition();		// Demande de données sur la commande de la caméra
			ReceiveCamPosition();		// Routine de réception des données séries
			
			AcquireDataSensor();
			SendDataSensor();
			
			receptionRC_OK = false;
		}
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

void AcquireDataSensor(void)
{
	
}

void SendDataSensor(void)
{
	
}

uint16_t Func_map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
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