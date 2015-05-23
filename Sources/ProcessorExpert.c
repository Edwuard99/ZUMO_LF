/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 20xx-xx-xx, xx:xx, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file ProcessorExpert.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
**  @{
*/
/* MODULE ProcessorExpert */



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
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "ZumoRobot.h"
#define DEBUG FALSE

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

	bool button=1;

	struct sensor s[6];
	
	int64_t min_avg[6]={25, 16, 14, 14, 17, 20};
	int64_t max_avg[6]={300, 102, 94, 88, 99, 204};
	int i,error;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  CountTimer_Init((LDD_TUserData *)NULL);
  PWM_dreapta_SetRatio16(65535);
  PWM_stanga_SetRatio16(65535);
  PWM_stanga_Enable();
  PWM_dreapta_Enable();
  
  IR_LED_PutVal(0);
  while(button==1);
	button=Button_GetVal();
  IR_LED_PutVal(1);
  //takeAvg(min_avg, max_avg);
#if DEBUG==TRUE
  for(i=0; i<6; i++){
		Term1_SendNum(min_avg[i]);
		Term1_SendChar("   ");
	}
	Term1_SendChar('\n');
	Term1_SendChar('\r');
	for(i=0; i<6; i++){
		Term1_SendNum(max_avg[i]);
		Term1_SendChar("   ");
	}
	Term1_SendChar('\n');
	Term1_SendChar('\r');
#endif
  

  while(1){
	  readSensors(min_avg, max_avg, s);
	  
#if DEBUG==TRUE
  takeAvg(min_avg, max_avg);
  while(1){
	  readSensors(min_avg, max_avg, s);
	  for(i=0; i<6; i++){
		  Term1_SendNum(s[i].value);
		  Term1_SendStr("  ");
	  }
	  for(i=0; i<6; i++){
		  Term1_SendNum(s[i].seen);
		  Term1_SendStr("  ");
	  }
#endif
	  error=propder(s, error);
#if DEBUG==TRUE
	  Term1_SendNum(error);
	  Term1_SendChar('\n');
	  Term1_SendChar('\r');
#endif
	  drive(error);

  }




  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
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
