/*
 * Definitions.h
 *
 * Created: 16/04/2013 10:07:40
 *  Author: ClementC
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

//definition.h
#define UBRRVAL1	8	// XBee baud rate 38400

#define X			0
#define Y			1
#define Z			2

#define NB_CHAN_RC	5

#define SERVO_X		OCR1A
#define SERVO_Z		OCR1C

#define MOT1		OCR4B
#define MOT2		OCR4D
#define MOT1_REV	PORTD&=~0x10;PORTC|=0x40
#define MOT1_FWD	PORTD|=0x10;PORTC&=~0x40
#define MOT2_REV	PORTE&=~0x40;PORTB|=0x10
#define MOT2_FWD	PORTE|=0x40;PORTB&=~0x10

#define TIMEOUT		true

#define NB_TX		12
#define NB_RX		4

// I2C status definition
#define STATUS_START			0x08
#define STATUS_RESTART			0x10
#define STATUS_ADRESS_WRITE		0x18
#define STATUS_DATA_TRANSMIT	0x28
#define STATUS_ADRESS_READ		0x40
#define STATUS_DATA_RECEIVE_1	0x50 // with acknowledgment
#define STATUS_DATA_RECEIVE_2	0x58 // without acknowledgment


#endif /* DEFINITIONS_H_ */