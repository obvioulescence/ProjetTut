/*
 * TSL2561.cpp
 *
 * Created: 11/12/2013 01:11:59
 *  Author: ClementC
 */

#include "Robot.h"
  
void TSL2561_Init(void)
{
	Write_TSL2561(TSL2561_REGISTER_CONTROL, 0x03); // power up
	Write_TSL2561(TSL2561_REGISTER_TIMING , 0x02); // gain X1, integration period : 402ms
}

void Read_TSL2561_data(void)
{
	I2C_start();
	I2C_status_check(STATUS_START);
	I2C_transmit_data((0x29<<1)); // address with write command
	I2C_status_check(STATUS_ADRESS_WRITE);

	I2C_transmit_data(TSL2561_REGISTER_CHAN0_LOW | TSL2561_COMMAND_BIT | TSL2561_WORD_BIT);
	I2C_status_check(STATUS_DATA_TRANSMIT);

	I2C_restart();
	I2C_status_check(STATUS_RESTART);
	I2C_transmit_data((0x29<<1)|1);
	I2C_status_check(STATUS_ADRESS_READ);

	UART_TX[2]	= I2C_receive_ACK();
	I2C_status_check(STATUS_DATA_RECEIVE_1);
	UART_TX[1]	= I2C_receive_NACK();
	I2C_status_check(STATUS_DATA_RECEIVE_2);

	I2C_stop();
}

uint8_t Read_TSL2561(uint8_t registre)
{
	uint8_t result = 0;
	I2C_start();
	I2C_status_check(STATUS_START);
	I2C_transmit_data((0x29<<1)); // 0x68 address with write command
	I2C_status_check(STATUS_ADRESS_WRITE);

	I2C_transmit_data(registre);
	I2C_status_check(STATUS_DATA_TRANSMIT);

	I2C_restart();
	I2C_status_check(STATUS_RESTART);
	I2C_transmit_data((0x29<<1)|1);

	I2C_status_check(STATUS_ADRESS_READ);
	result = I2C_receive_NACK();
	I2C_status_check(STATUS_DATA_RECEIVE_2);
	I2C_stop();

	return result;
}

void Write_TSL2561(uint8_t registre, uint8_t data)
{
	I2C_start();
	I2C_status_check(STATUS_START);
	
	I2C_transmit_data((0x29<<1));
	I2C_status_check(STATUS_ADRESS_WRITE);

	I2C_transmit_data(registre | 0x80);
	I2C_status_check(STATUS_DATA_TRANSMIT);

	I2C_transmit_data(data);
	I2C_status_check(STATUS_DATA_TRANSMIT);

	I2C_stop();
}