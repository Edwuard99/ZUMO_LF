#ifndef ZUMOROBOT_H
#define ZUMOROBOT_H

//In header am pus toate include-urile si toate declaratiile de functii

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
	int value;
	int dist;
	bool seen;
};

void irSensors(struct sensor s[6]);//Ia valorile raw ale snezoriilor
void motor(int x, int y);//Controlul motoarelor
void drive(int error);//Controlul motoarelor in functie de eroare
void takeAvg(int64_t min_avg[6], int64_t max_avg[6]);
void calibrate(int64_t min_avg[6], int64_t max_avg[6], struct sensor s[6]);//calibrarea
void readSensors(int64_t min_avg[6], int64_t max_avg[6], struct sensor s[6]);//Citirea senzoriilor(irSensors + calibrate)
int propder(struct sensor s[6], int error);//algoritmul PD
int see(struct sensor s[6]);//Decide daca un sezor vede sau nu linia
#endif
