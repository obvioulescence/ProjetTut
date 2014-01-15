/*
 * XBee.cpp
 *
 * Created: 05/10/2013 16:30:17
 *  Author: ClementC
 */

#include "dataReceiver.h"

void Xbee_Init(void)
{
	//PRR1 &= ~(1<<PRUSART1); // enables the USART module
	
	//Set baud rate
	UBRR1H = (UBRRVAL1>>8);		//high byte
	UBRR1L = (uint8_t)UBRRVAL1;	//low byte
 
	UCSR1C = (1<<UCSZ11) | (1<<UCSZ10); //Set data frame format: asynchronous mode,no parity, 1 stop bit, 8 bit size
	UCSR1B = (1<<RXEN1) | (1<<TXEN1); //Enable Transmitter and Receiver without interrupt
}

uint16_t Xbee_ReceiveByte(uint16_t timeout)
{
	uint16_t currentTimeout = 0;
 
	while((!(UCSR1A & (1<<RXC1)) ) & (currentTimeout++ < timeout))   // Wait until a byte has been received or time out
		_delay_us(1);

	if(currentTimeout >= timeout)
		return 0x0100;
	else
		return (0x00FF & UDR1);// Return received data
}

uint8_t Xbee_Byte_Available(void)
{
	return (UCSR1A & (1<<RXC1)) ? 1 : 0;
}

void Xbee_transmit_data(uint8_t data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR1A & (1<<UDRE1)) );

	/* Put data into buffer, sends the data */
	UDR1 = data;
}

void Xbee_transmit_string(char string1[])
{
	// codage de tous les caractères de la chaine avec la table ascii puis envoi
	uint8_t i;
	size_t nb = strlen(string1);

	for(i=0 ; i<nb ; i++)
	{
		if ((string1[i] == '/') && (string1[i+1] == 'n')) // détection d'un carriage return
		{
			Xbee_transmit_data(0x0D); // on transmet le code ascii correspond
			i++; // et on zape le '\n'
		}
		else
			Xbee_transmit_data(string1[i]);
	}
}

void Xbee_transmit_carriage_return(void)
{
	Xbee_transmit_data(0x0D);
}
