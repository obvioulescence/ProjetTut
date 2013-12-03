/*
 * dataReceiver.h
 *
 * Created: 02/10/2013 14:40:45
 *  Author: Antoine
 */ 

#include "Definitions.h"

#ifndef ROBOT_H_
#define ROBOT_H_

//==========================================================
//==========================================================
extern volatile uint8_t Data_RX[3];
extern volatile uint8_t nb_INT;
extern volatile uint8_t DataCamPosition[2];
//==========================================================

void SendDataCam(void);

// initialisation des entrées sorties
void ioInit( void );

// fonction du timer 1
void timer1_Init(void);

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
void mpu6050_Init(void);
uint8_t Read_mpu6050(int8_t registre);
void Write_mpu6050(uint8_t registre, uint8_t data);

/* prototypes des fonctions dédiées au Xbee */
void Xbee_Init(void);
uint16_t Xbee_ReceiveByte(uint16_t timeout);
uint8_t Xbee_Byte_Available(void);
void Xbee_transmit_data(int8_t data);
void Xbee_transmit_string(char string[]);
void Xbee_transmit_carriage_return(void);
	
	

#endif /* ROBOT_H_ */