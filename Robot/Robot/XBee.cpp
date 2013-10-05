/*
 * XBee.cpp
 *
 * Created: 05/10/2013 16:30:17
 *  Author: ClementC
 */

#include "Robot.h"

void Xbee_Init(void)
{
	PRR &= ~(1<<PRUSART0); // enables the USART module
	
	//Set baud rate
	UBRR0H = (UBRRVAL0>>8);		//high byte
	UBRR0L = (uint8_t)UBRRVAL0;	//low byte
 
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00); //Set data frame format: asynchronous mode,no parity, 1 stop bit, 8 bit size
	UCSR0B = (1<<RXEN0 ) | (1<<TXEN0 ); //Enable Transmitter and Receiver
}

uint16_t Xbee_ReceiveByte( uint16_t timeout )
{
	uint16_t currentTimeout = 0;
 
	while((!(UCSR0A & (1<<RXC0)) ) & (currentTimeout++ < timeout))   // Wait until a byte has been received or time out
		_delay_us(1);

	if(currentTimeout >= timeout)
		return 0x0100;
	else
		return (0x00FF & UDR0);// Return received data
}

uint8_t Xbee_Byte_Available(void)
{
	return (UCSR0A & (1<<RXC0)) ? 1 : 0;
}

void Xbee_transmit_data(int8_t data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );

	/* Put data into buffer, sends the data */
	UDR0 = data;
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
