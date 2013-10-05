/*
 * Servo.cpp
 *
 * Created: 04/10/2013 12:41:43
 *  Author: ClementC
 */

#include "Robot.h"

void ServoInit(void)
{
	WriteServo(94, 94);
}

void WriteServo(uint8_t Angle_X, uint8_t Angle_Z)
{
	SERVO_X = ((Angle_X >= 63) && (Angle_X <= 125)) ? Angle_X : SERVO_X;
	SERVO_Z = ((Angle_Z >= 63) && (Angle_Z <= 125)) ? Angle_Z : SERVO_Z;
}
