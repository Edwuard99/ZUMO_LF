#ifndef ZUMOROBOT_H
#define ZUMOROBOT_H

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
	int64_t value;
	int64_t dist;
};

void readSensors(struct sensor s[6]);
void motor(int x, int y);

#endif
