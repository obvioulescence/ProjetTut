/*
 * dataReceiver.h
 *
 * Created: 02/10/2013 14:40:45
 *  Author: Antoine Galvaire
 */ 

#include "Definitions.h"

#ifndef ROBOT_H_
#define ROBOT_H_

//==========================================================
//==========================================================

// initialisation des entrées sorties
void ioInit( void );

/* prototypes des fonctions dédiées à l'i²C */
void I2C_Init(void);
void I2C_start(void);
void I2C_transmit_data(char data);
void I2C_stop(void);
void I2C_restart(void);
void I2C_status_check(char status);
char I2C_receive_ACK(void);
char I2C_receive_NACK(void);
void ERROR(void);

/* prototypes des fonctions dédiées à l'IMU3000 */
void IMU3000_Init(void);
void Read_IMU_3000_data(void);
uint8_t Read_IMU_3000(int8_t registre);
void Write_IMU_3000(uint8_t registre, uint8_t data);
	// prototypes des fonctions dédiées au gyroscope
	void gyroCalibration(void);
	void UpdateGyroValues(void);

#endif /* ROBOT_H_ */