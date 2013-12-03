/*
 * Motors.cpp
 *
 * Created: 29/10/2013 20:47:52
 *  Author: ClementC
 */

 #include "Robot.h"

void timer4_Init(void)
{
	TCCR4A = 0x21;
	TCCR4B = 0x05;
	TCCR4C = 0x29;
	TCCR4D = 0x00;
	TCCR4E = 0x00;
	
	OCR4C  = 0xFF;
}

void MoteurInit(void)
{
	timer4_Init();
	
	MOT1 = 0x7F;
	MOT2 = 0x7F;
}

void computeMotors(void)
{
	uint16_t RC[6] = {0};
	int16_t  mot1  =  0;
	int16_t  mot2  =  0;
	
	// backup des données pour les calculs
	for(uint8_t i = 0 ; i<6 ; i++)
		RC[i] = RC_Values[i];
		
	// calcul des lois de commande
	//if (RC[2] < 1490 || RC[2] > 1510)
		U1 = (RC[1] >= 1500) ? RC[1]-1500 : -1*(500-(RC[1]-1000));
	
	//if (RC[1] < 1490 || RC[1] > 1510)
		U2 = (RC[2] >= 1500) ? RC[2]-1500 : -1*(500-(RC[2]-1000));
	
	// calcul de la vitesse des moteurs
	mot1 = (U1 + U2) / 2;
	mot2 = (U2 - U1) / 2;
	
	// mise à jour matérielle
	if (mot1 < 0)				// marche arrière
	{
		MOT1_REV;
		MOT1 = abs(mot1) / 1.96;
	}
	else
	{
		MOT1_FWD;
		MOT1 = mot1 / 1.96;
	}
	
	if (mot2 < 0)
	{
		MOT2_REV;
		MOT2 = abs(mot2) / 1.96;
	}
	else
	{
		MOT2_FWD;
		MOT2 = mot2 / 1.96;
	}
}