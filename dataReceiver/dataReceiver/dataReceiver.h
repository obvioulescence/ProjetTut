/*
 * dataReceiver.h
 *
 * Created: 02/10/2013 14:40:45
 *  Author: ClementC
 */ 

#include "Definitions.h"

#ifndef DATARECEIVER_H_
#define DATARECEIVER_H_

//==========================================================
//==========================================================
extern volatile uint16_t R_GYRO[3];
extern volatile uint16_t R_ACC[3];
extern volatile uint8_t	 Data_RX[NB_RX];
extern volatile uint8_t  Data_TX[NB_TX];
extern volatile bool	 xbeeCom_achieved;
extern volatile uint8_t  headAngle[3];
extern volatile uint16_t GyroZeroRate[3];
//==========================================================

// initialisation des entrées sorties
void ioInit( void );

// fonction du timer 1
void timer1_Init(void);

//IMU
void IMU_Compute(void);
void computeAngle(void);

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
uint8_t Read_mpu6050(uint8_t registre);
void Read_MPU6050_Data(void);
void Write_mpu6050(uint8_t registre, uint8_t data);

/* prototypes des fonctions dédiées au Xbee */
void Xbee_Init(void);
uint16_t Xbee_ReceiveByte(uint16_t timeout);
uint8_t Xbee_Byte_Available(void);
void Xbee_transmit_data(uint8_t data);
void Xbee_transmit_string(char string[]);
void Xbee_transmit_carriage_return(void);

#endif /* ROBOT_H_ */