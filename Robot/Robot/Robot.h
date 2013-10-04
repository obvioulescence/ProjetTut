/*
 * Robot.h
 *
 * Created: 02/10/2013 14:40:45
 *  Author: ClementC
 */ 

#include "Definitions.h"

#ifndef ROBOT_H_
#define ROBOT_H_

//==========================================================
//================= VARIABLES GLOBALES =====================
//==========================================================

extern volatile uint64_t microseconds;		// compteur de microsecondes
extern volatile uint16_t RC_Values[5];		// tableau contenant les microsecondes des impulsions radio


// initialisation des entrées sorties
void ioInit(void);

/* prototypes des fonctions dédiées à la gestion des servos */
void ServoInit(void);

/* prototypes des fonctions dédiées au timer1 */
void timer1_Init(void);

/* prototypes des fonctions dédiées au timer2 */
void timer2_Init(void);

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