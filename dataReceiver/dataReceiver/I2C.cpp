/*
 * I2C.cpp
 *
 * Created: 02/10/2013 15:20:45
 *  Author: Antoine
 */ 

#include "dataReceiver.h"

void I2C_Init(void)
{

// Enable internal pull up for SDA et SCL pins
	/*MCUCR &=~(1<<PUD);
	DDRD&=~(1<<DDD0);
	DDRD&=~(1<<DDD1);
	PORTD|=(1<<PD0)|(1<<PD1);*/ // sets PD0 and PD1 to enable their poll up

// Setting the I2C frequency as 400KHz
	TWBR=12;
	TWSR&=~(1<<TWPS1);
	TWSR&=~(1<<TWPS0);

	TWCR|=(1<<TWEA)|(1<<TWEN);  // Enable I2C module and acknowledgment sent in case
	TWCR&=~(1<<TWIE); // disable the i2c interrupt
}


void I2C_start(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);  // clear the TWINT flag
    
	while (!(TWCR & (1<<TWINT)));
		//if((TWSR & 0xF8) !=0x08) ERROR();   
}

void I2C_transmit_data(char data)
{
	TWDR=data; //sent data
	TWCR=(1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	//if((TWSR & 0xF8) !=0x28) ERROR();      
}

void I2C_stop(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void I2C_restart(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	//if((TWSR & 0xF8) !=0x10) ERROR();

}

void I2C_status_check(char status)
{
	if((TWSR & 0xF8) !=status) ERROR();
}

char I2C_receive_ACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);     
	while (!(TWCR & (1<<TWINT)));     
	return TWDR;  
}

char I2C_receive_NACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);     
	while (!(TWCR & (1<<TWINT)));     
	return TWDR;  
}

void ERROR(void)
{
	/*Xbee_transmit_data('E');
	Xbee_transmit_data('R');
	Xbee_transmit_data('R');
	Xbee_transmit_data('O');
	Xbee_transmit_data('R');*/
}
