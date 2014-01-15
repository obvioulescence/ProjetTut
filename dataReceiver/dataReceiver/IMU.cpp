/*
 * IMU.cpp
 *
 * Created: 26/12/2013 20:41:53
 *  Author: ClementC
 */ 

#include "dataReceiver.h"

void IMU_Compute(void)
{
	volatile double GyroAngle[3]	 = {0};
	volatile double lastGyroAngle[3] = {0};
	volatile double AccAngle[3]		 = {0};
	
	//============= PARTIE GYROSCOPIQUE ==============
	// backup
	lastGyroAngle[Z] = GyroAngle[Z];
	// calcul
	GyroAngle[Y] += headAngle[Y] + (R_GYRO[Y] - GyroZeroRate[Y])*dT;
	GyroAngle[Z] += headAngle[Z] + (R_GYRO[Z] - GyroZeroRate[Z])*dT;
	
	//============= PARTIE ACCELEROMETRIQUE ==========
	if (R_ACC[X] <= 0)
	AccAngle[Y] += asin(AccAngle[Y]/ACC_MAX);
	else
	AccAngle[Y] += M_PI_2 - asin(AccAngle[Y]/ACC_MAX) + M_PI_2;

	//================================================
	//============= FUSION DE DONNEES ================
	//================================================
	headAngle[Y] = (AccAngle[Y]      + GyroAngle[Y] * wGyro) / (1 + wGyro);
	headAngle[Z] = (lastGyroAngle[Z] + GyroAngle[Z] * wMoye) / (1 + wMoye);
}

void computeAngle(void)
{
	Data_TX[1] = headAngle[Y] * 180 / M_PI;
	Data_TX[2] = headAngle[Z] * 180 / M_PI;
}