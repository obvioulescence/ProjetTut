/*
 * MPU6050.cpp
 *
 * Created: 07/10/2013 10:54:36
 *  Author: ClementC
 */ 

#include "dataReceiver.h"

void mpu6050_Init(void)
{
	Write_mpu6050(MPU6050_RA_GYRO_CONFIG, MPU6050_GYRO_FS_500);
	Write_mpu6050(MPU6050_RA_PWR_MGMT_1 , MPU6050_CLOCK_PLL_ZGYRO);
}

uint8_t Read_mpu6050(uint8_t registre)
{
	uint8_t result = 0;
	
	I2C_start();
	I2C_status_check(STATUS_START);
	I2C_transmit_data((MPU6050_DEFAULT_ADDRESS<<1)); // 0x68 address with write command
	I2C_status_check(STATUS_ADRESS_WRITE);

	I2C_transmit_data(registre);
	I2C_status_check(STATUS_DATA_TRANSMIT);

	I2C_restart();
	I2C_status_check(STATUS_RESTART);
	I2C_transmit_data((MPU6050_DEFAULT_ADDRESS<<1)|1);

	I2C_status_check(STATUS_ADRESS_READ);
	result = I2C_receive_NACK();
	I2C_status_check(STATUS_DATA_RECEIVE_2);
	I2C_stop();

	return result;
}

void Read_MPU6050_Data(void)
{
	I2C_start();
	I2C_status_check(STATUS_START);
	I2C_transmit_data((MPU6050_DEFAULT_ADDRESS<<1)); // address with write command
	I2C_status_check(STATUS_ADRESS_WRITE);

	I2C_transmit_data(MPU6050_RA_GYRO_XOUT_H);
	I2C_status_check(STATUS_DATA_TRANSMIT);

	I2C_restart();
	I2C_status_check(STATUS_RESTART);
	I2C_transmit_data((MPU6050_DEFAULT_ADDRESS<<1)|1);
	I2C_status_check(STATUS_ADRESS_READ);

	// partie gyro
	R_GYRO[X] = I2C_receive_ACK() * 256;
	I2C_status_check(STATUS_DATA_RECEIVE_1);
	R_GYRO[X] = I2C_receive_ACK();
	I2C_status_check(STATUS_DATA_RECEIVE_1);
	R_GYRO[Y] = I2C_receive_ACK() * 256;
	I2C_status_check(STATUS_DATA_RECEIVE_1);
	R_GYRO[Y] = I2C_receive_ACK();
	I2C_status_check(STATUS_DATA_RECEIVE_1);
	R_GYRO[Z] = I2C_receive_ACK() * 256;
	I2C_status_check(STATUS_DATA_RECEIVE_1);
	R_GYRO[Z] = I2C_receive_ACK();
	I2C_status_check(STATUS_DATA_RECEIVE_1);
	
	// saut des registres température
	I2C_receive_ACK();
	I2C_receive_ACK();
	
	// partie acc
	R_ACC[X] = I2C_receive_ACK() * 256;
	I2C_status_check(STATUS_DATA_RECEIVE_1);
	R_ACC[X] = I2C_receive_ACK();
	I2C_status_check(STATUS_DATA_RECEIVE_1);
	R_ACC[Y] = I2C_receive_ACK() * 256;
	I2C_status_check(STATUS_DATA_RECEIVE_1);
	R_ACC[Y] = I2C_receive_ACK();
	I2C_status_check(STATUS_DATA_RECEIVE_1);
	R_ACC[Z] = I2C_receive_ACK() * 256;
	I2C_status_check(STATUS_DATA_RECEIVE_1);
	R_ACC[Z] = I2C_receive_NACK();
	I2C_status_check(STATUS_DATA_RECEIVE_2);

	I2C_stop();
}

void Write_mpu6050(uint8_t registre, uint8_t data)
{
	I2C_start();
	I2C_status_check(STATUS_START);
	
	I2C_transmit_data((MPU6050_DEFAULT_ADDRESS<<1));
	I2C_status_check(STATUS_ADRESS_WRITE);

	I2C_transmit_data(registre);
	I2C_status_check(STATUS_DATA_TRANSMIT);

	I2C_transmit_data(data);
	I2C_status_check(STATUS_DATA_TRANSMIT);

	I2C_stop();
}