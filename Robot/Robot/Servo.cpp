/*
 * Servo.cpp
 *
 * Created: 04/10/2013 12:41:43
 *  Author: ClementC
 */

#include "Robot.h"

void timer1_Init(void)
{
	TCCR1A = 0x8A; // COM1A1 | COM1C1 | WGM11
	TCCR1B = 0x1A; // WGM12  | WGM13  | CS11
	ICR1   = 39999;
}

void ServoInit(void)
{
	timer1_Init();
	WriteServo(2000, 4000);
}

void WriteServo(uint16_t Angle_X, uint16_t Angle_Z)
{
	SERVO_X = ((Angle_X >= 2000) && (Angle_X <= 4000)) ? Angle_X : SERVO_X;
	SERVO_Z = ((Angle_Z >= 2000) && (Angle_Z <= 4000)) ? Angle_Z : SERVO_Z;
}
