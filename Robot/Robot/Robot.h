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

extern volatile uint16_t RC_Values[6];		// tableau contenant les microsecondes des impulsions radio
extern volatile uint16_t camPosition[2];	// position de la cam�ra X Z
extern volatile uint8_t  UART_RX[NB_RX];	// Buffer de r�ception
extern volatile uint8_t  UART_TX[NB_TX];	// Buffer de transmission
extern volatile int16_t  U1;				// loi de commande translation
extern volatile int16_t  U2;				// loi de commande rotation
extern volatile bool	 _sensorCom_ready;	// pr�t � r�cup�rer les donn�es
extern volatile uint8_t  Sensor_LUX[2];

// initialisation des entr�es sorties
void ioInit(void);

/* prototypes des fonctions d�di�s � la r�ception RC */
void RC_Init(void);

/* prototypes des fonctions d�di�es � la gestion des servos ; Angle entre 1000 et 2000*/
void ServoInit(void);
void WriteServo(uint16_t Angle_X, uint16_t Angle_Z);

/* prototyps des fonctions pour les moteurs */
void MoteurInit(void);
void computeMotors(void);

/* prototypes des fonctions d�di�es � la gestion de la cam�ra */
void RequireCamPosition(void);
bool ReceiveCamPosition(uint16_t timeout);
void WriteCamPosition(bool timeout = false);

/* fonctions d�di�s � la gestion des capteurs */
void SensorInit(void);
void AcquireDataSensor(void);
	//TSL2561
	void TSL2561_Init(void);
	void Read_TSL2561_data(void);
	uint8_t Read_TSL2561(uint8_t registre);
	void Write_TSL2561(uint8_t registre, uint8_t data);
	//MPL3115A2
	void MPL3115A2_Init(void);
	void Read_MPL3115A2_data(void);
	uint8_t Read_MPL3115A2(uint8_t registre);
	void Write_MPL3115A2(uint8_t registre, uint8_t data);

/* prototypes des fonctions d�di�es aux timer */ 
void timer3_Init(void);							// interruption 10ms
void timer1_Init(void);							// PWM servos
void timer0_Init(void);							// input capture (PPM)
void timer4_Init(void);							// PWM moteurs

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
void Xbee_transmit_data(uint8_t data);
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
uint8_t Func_map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);

#endif /* ROBOT_H_ */