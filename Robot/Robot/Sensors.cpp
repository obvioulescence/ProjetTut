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
	 
	 UDR1 = UART_TX[Cursor];
	 
	 if (Cursor == (11))
	 {
		 UCSR1B &= ~(1<<TXC1);
		 Cursor = 1;
	 }
	 else
		Cursor++;
 }