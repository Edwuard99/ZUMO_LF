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

#include "ZumoRobot.h"
#define err 1000 //trebuie calibrat, asta ar fi gain-ul pentru componenta proportionala
#define nominalSpeed 60000

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	struct sensor s[6];

	int64_t min_avg[6], max_avg[6];
	int i;
	int pondere[6]={10, 20, 30, 40, 50, 60};
	int pos=0;
	int cnt=0;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  CountTimer_Init((LDD_TUserData *)NULL);
  takeAvg(min_avg, max_avg);




  while(1){
	  readSensors(min_avg, max_avg, s);
	  for(i=0;i<6;++i)
	  {
		  pos=pos+pondere[i]*s[i].seen;
		  cnt+=s[i].seen;
	  }
	  pos/=cnt;
		int error=pos-35;
		motor(err*error+nominalSpeed, err*error-nominalSpeed); //controlul proportional al motoarelor
		/*
	  if(pos==35)
		  motor(60000, 60000);
	  else if(pos<35&&pos>15)
		  motor(50000, 65000);
	  else if(pos>35&&pos<45)
		  motor(65000, 50000);
	  else if(pos<=15)
		  motor(40000, 65000);
	  else if(pos>=45)
		  motor(65000, 40000);

		*/
	  for(i=0; i<6; i++){
		  Term1_SendNum(s[i].value);
		  Term1_SendStr("  ");
	  }
	  for(i=0; i<6; i++){
		  Term1_SendNum(s[i].seen);
		  Term1_SendStr("  ");
	  }
	  proportional(s);
	  Term1_SendChar('\n');
	  Term1_SendChar('\r');

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
