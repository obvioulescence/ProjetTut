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
extern volatile bool     receptionRC_OK;	// Information sur l'�tat de la r�ception RC
extern volatile uint16_t camPosition[2];	// position de la cam�ra X Z


// initialisation des entr�es sorties
void ioInit(void);

/* prototypes des fonctions d�di�es � la gestion des servos ; Angle entre 63 et 125*/
void ServoInit(void);
void WriteServo(uint8_t Angle_X, uint8_t Angle_Z);

/* prototypes des fonctions d�di�es � la gestion de la cam�ra */
void RequireCamPosition(void);
bool ReceiveCamPosition(void);
void WriteCamPosition(void);

/* fonctions d�di�s � la gestion des capteurs */
void AcquireDataSensor(void);
void SendDataSensor(void);

/* prototypes des fonctions d�di�es au timer0 */
void timer0_Init(void);

/* prototypes des fonctions d�di�es au timer1 */
void timer1_Init(void);

/* prototypes des fonctions d�di�es au timer2 */
void timer2_Init(void);

/* prototypes des fonctions d�di�es � l'i�C */
void I2C_Init(void);
void I2C_start(void);
void I2C_transmit_data(char data);
void I2C_stop(void);
void I2C_restart(void);
void I2C_status_check(char status);
char I2C_receive_ACK(void);
char I2C_receive_NACK(void);
void ERROR(void);

/* prototypes des fonctions d�di�es au Xbee */
void Xbee_Init(void);
uint16_t Xbee_ReceiveByte(uint16_t timeout);
uint8_t Xbee_Byte_Available(void);
void Xbee_transmit_data(int8_t data);
void Xbee_transmit_string(char string[]);
void Xbee_transmit_carriage_return(void);

/* prototypes des fonctions d�di�es � l'IMU3000 */
void IMU3000_Init(void);
void Read_IMU_3000_data(void);
uint8_t Read_IMU_3000(int8_t registre);
void Write_IMU_3000(uint8_t registre, uint8_t data);
 // prototypes des fonctions d�di�es au gyroscope
 void gyroCalibration(void);
 void UpdateGyroValues(void);
 
// fonctions math�matiques
uint16_t Func_map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);

#endif /* ROBOT_H_ */