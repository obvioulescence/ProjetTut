/*
* MPL3115A2.cpp
*
* Created: 11/12/2013 01:12:44
*  Author: ClementC
*/

#include "Robot.h"
 
void MPL3115A2_Init(void)
{
	Write_MPL3115A2(CTRL_REG1, 0x01); // standby to active mode
}

void Read_MPL3115A2_data(void)
{
	I2C_start();
	I2C_status_check(STATUS_START);
	I2C_transmit_data(MPL3115A2_ADDRESS << 1); // address with write command
	I2C_status_check(STATUS_ADRESS_WRITE);

	I2C_transmit_data(OUT_T_LSB);
	I2C_status_check(STATUS_DATA_TRANSMIT);

	I2C_restart();
	I2C_status_check(STATUS_RESTART);
	I2C_transmit_data((MPL3115A2_ADDRESS << 1)|1);
	I2C_status_check(STATUS_ADRESS_READ);

	// Pression
	UART_TX[3]	= I2C_receive_ACK();
	I2C_status_check(STATUS_DATA_RECEIVE_1);
	UART_TX[4]	= I2C_receive_ACK();
	I2C_status_check(STATUS_DATA_RECEIVE_1);
	UART_TX[5]	= I2C_receive_ACK();
	I2C_status_check(STATUS_DATA_RECEIVE_1);
	
	// Temperature
	UART_TX[6]	= I2C_receive_ACK();
	I2C_status_check(STATUS_DATA_RECEIVE_1);
	UART_TX[7]	= I2C_receive_NACK();
	I2C_status_check(STATUS_DATA_RECEIVE_2);

	I2C_stop();
}

uint8_t Read_MPL3115A2(uint8_t registre)
{
	uint8_t result = 0;
	
	I2C_start();
	I2C_status_check(STATUS_START);
	I2C_transmit_data(MPL3115A2_ADDRESS << 1); // 0x68 address with write command
	I2C_status_check(STATUS_ADRESS_WRITE);

	I2C_transmit_data(registre);
	I2C_status_check(STATUS_DATA_TRANSMIT);

	I2C_restart();
	I2C_status_check(STATUS_RESTART);
	I2C_transmit_data((MPL3115A2_ADDRESS << 1)|1);

	I2C_status_check(STATUS_ADRESS_READ);
	result = I2C_receive_NACK();
	I2C_status_check(STATUS_DATA_RECEIVE_2);
	I2C_stop();

	return result;
}

void Write_MPL3115A2(uint8_t registre, uint8_t data)
{
	I2C_start();
	I2C_status_check(STATUS_START);
	 
	I2C_transmit_data(MPL3115A2_ADDRESS << 1);
	I2C_status_check(STATUS_ADRESS_WRITE);

	I2C_transmit_data(registre);
	I2C_status_check(STATUS_DATA_TRANSMIT);

	I2C_transmit_data(data);
	I2C_status_check(STATUS_DATA_TRANSMIT);

	I2C_stop();
}