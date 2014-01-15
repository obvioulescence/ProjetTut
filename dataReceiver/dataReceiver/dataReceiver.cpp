/*
 * dataReceiver.h
 *
 * Created: 02/10/2013 14:40:45
 *  Author: ClementC
 */
 

#include "dataReceiver.h"

/* variables globales */
volatile uint16_t R_GYRO[3]			= {0};
volatile uint16_t R_ACC[3]			= {0};
volatile uint8_t  Data_RX[NB_RX]	= {0};
volatile uint8_t  Data_TX[NB_TX]	= {0xFF, 90, 90, 0xEE};
volatile bool	  xbeeCom_achieved	= false;
volatile uint8_t  headAngle[3]		= {0};
volatile uint16_t GyroZeroRate[3]	= {0};

/* variables locales */
const uint8_t Data_RX_error[NB_RX-2] = {0};

int main(void)
{
	//Initialization
	ioInit();
	I2C_Init();
	Xbee_Init();
	timer1_Init();
	usb_init();
		while (!usb_configured()) /* wait */ ;
	
	while(1)
	{
		
	}
   
}

void ioInit(void)
{
	
}

ISR(USART1_TX_vect)
{
	volatile static uint8_t cursor = 1;

	UDR1 = Data_TX[cursor++];
	
	if (cursor == NB_TX)
	{
		UCSR1B &= ~_BV(TXC1);
		UCSR1B |=  _BV(RXC1);
		cursor  =  1;
		computeAngle();
	}
}

ISR(USART1_RX_vect)
{
	volatile static uint8_t cursor = 0;

	Data_RX[cursor++] = UDR1;

	if (cursor == NB_RX)
	{
		cursor  = 0;
		UCSR1B &= _BV(RXC1);
		xbeeCom_achieved = true;
	}
}

void timer1_Init(void)
{
	TCCR1A = _BV(WGM10) | _BV(WGM11);
	TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS11);
	TIMSK1 = _BV(TOIE1);

	OCR1A  = 19999;
}

ISR(TIMER1_OVF_vect)
{
	uint8_t Data_RX_copy[NB_RX] = {0};
	Read_MPU6050_Data();
	
	// Lance la procédure d'envoi
	xbeeCom_achieved = false;
	UCSR1B |= _BV(TXC1);  // TX interrupt
	UDR1    = Data_TX[0]; // dispatch data
	
	IMU_Compute();
	
	while (!xbeeCom_achieved); // pas touche à l'usb avant que tout ne soit terminé (improvment : tout faire par interruption)
	
	for (uint8_t i = 0 ; i<NB_RX ; i++)
		Data_RX_copy[i] = Data_RX[i];
	
	if ((Data_RX[0] == 0xFF) && (Data_RX[NB_RX-1] == 0xEE))
		usb_serial_write(Data_RX_copy+1 , NB_RX-2);			// réception XBee correcte : envoie des données
	else
		usb_serial_write(Data_RX_error  , NB_RX-2);			// réception XBee erronnée : envoie du tableau vide
}