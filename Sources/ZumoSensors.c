#include "ZumoRobot.h"


void readSensors(struct sensor s[6]){
	int64_t a=1,b=1,c=1,d=1,e=1,f=1;
	int64_t i;
	int64_t x;
	IR_LED_SetOutput();
	IR_LED_PutVal(1);
	
	A1_SetOutput();
	A3_SetOutput();
	D11_SetOutput();
	A0_SetOutput();
	A2_SetOutput();
	D5_SetOutput();
	
	A1_PutVal(1);
	A3_PutVal(1);
	D11_PutVal(1);
	A0_PutVal(1);
	A2_PutVal(1);
	D5_PutVal(1);
	
	WAIT1_Waitus(50);

	A1_SetInput();
	A3_SetInput();
	D11_SetInput();
	A0_SetInput();
	A2_SetInput();
	D5_SetInput();

	CountTimer_ResetCounter((LDD_TDeviceData *)NULL);
	x=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL);
	
	s[0].value=x;
	s[1].value=x;
	s[2].value=x;
	s[3].value=x;
	s[4].value=x;
	s[5].value=x;
	
	

	while(a || b || c || d || e || f){
		x=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL);

		a=A1_GetVal();
		b=A3_GetVal();
		c=D11_GetVal();
		d=A0_GetVal();
		e=A2_GetVal();
		f=D5_GetVal();
	
		if(a)
			s[0].value=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL);
		if(b)
			s[1].value=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL);
		if(c)
			s[2].value=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL);
		if(d)
			s[3].value=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL);
		if(e)
			s[4].value=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL);
		if(f)
			s[5].value=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL);

		if(x>70)
			break;

	}

	for(i=0; i<6; i++){
			if(s[i].value>=35)
				s[i].value=1;
			else
				s[i].value=0;
	}

}

