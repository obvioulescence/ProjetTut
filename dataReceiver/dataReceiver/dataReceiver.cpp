/*
 * dataReceiver.cpp
 *
 * Created: 01/10/2013 18:11:31
 *  Author: ClementC
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>

#include <avr/io.h>

int main(void)
{DDRB |= 0b00010000;
	PORTB |= 0x10;
    while(1)
    {
		_delay_ms(500);
    }
}