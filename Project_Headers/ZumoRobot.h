/*#################################################################################################################################################################################
**		Acesta este fisierul header folosit pentru intregul proiect.
**	Fisierul contine declaratiile tuturor functiilor create de echipa noastra si
**o structura de date de tip sensor care contine:
**	--o varibila de tip int unde va fi retinuta valoarea senzorului
**	--o variabil de tip int unde va fi retinuta distanta
**	--o varibila de tip int unde va fi retinut daca senzorul vede sau nu linia
**Structura respectiva este folosita in majoritatea functiilor ce fac parte din proiect.
**#################################################################################################################################################################################*/
#ifndef ZUMOROBOT_H
#define ZUMOROBOT_H

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Cpu.h"
#include "Events.h"
#include "WAIT1.h"
#include "sens_dreapta.h"
#include "BitIoLdd2.h"
#include "sens_stanga.h"
#include "BitIoLdd3.h"
#include "PWM_dreapta.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "PWM_stanga.h"
#include "PwmLdd2.h"
#include "TU2.h"
#include "CountTimer.h"
#include "A1.h"
#include "BitIoLdd4.h"
#include "A3.h"
#include "BitIoLdd5.h"
#include "D11.h"
#include "BitIoLdd6.h"
#include "A0.h"
#include "BitIoLdd7.h"
#include "A2.h"
#include "BitIoLdd8.h"
#include "D5.h"
#include "BitIoLdd9.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd2.h"
#include "IR_LED.h"
#include "BitIoLdd10.h"
#include "Button.h"
#include "BitIoLdd11.h"
#include "PullUpButton.h"
#include "PE_Types.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "IO_Map.h"


struct sensor{
	/*** value - valoarea                  ***/
	int value;
	/*** dist - distanta fata de centru    ***/
	int dist;
	/*** seen - senzorul vede sau nu linia ***/
	int seen;
};

/*** Citeste valorile "raw" ale senzorilor.                                                  ***/
void irSensors(struct sensor s[6]);

/*** Calibreaza valorile senzorilor.                                                         ***/
void calibrate(int64_t min_avg[6], int64_t max_avg[6], struct sensor s[6]);

/*** Combina functiile irSensors si calibrate si stabileste daca un sezor vede sau nu linia. ***/
void readSensors(int64_t min_avg[6], int64_t max_avg[6], struct sensor s[6]);

/*** Algoritmul PD propriu-zis.                                                              ***/
int propder(struct sensor s[6]);

/*** Transmite o valoare in functie de cati senzor vad linia.                                ***/
int see(struct sensor s[6]);

/*** Controlul motoarelor.                                                                   ***/
void motor(int left, int right);

/*** Controlul motoarelor in functie de eroare.                                              ***/
void drive(int64_t error);

#endif
