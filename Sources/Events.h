/* ###################################################################
**     Filename    : Events.h
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 20xx-xx-xx, xx:xx, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
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

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
