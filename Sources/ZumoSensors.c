#include "ZumoRobot.h"


void irSensors(struct sensor s[6]){
	int a=1,b=1,c=1,d=1,e=1,f=1;
	int x;
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
	
	A1_SetInput();
	A3_SetInput();
	D11_SetInput();
	A0_SetInput();
	A2_SetInput();
	D5_SetInput();
	
	CountTimer_Init((LDD_TUserData *)NULL);
	CountTimer_ResetCounter((LDD_TDeviceData *)NULL);
	x=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL);
	
	s[0].value=x;
	s[1].value=x;
	s[2].value=x;
	s[3].value=x;
	s[4].value=x;
	s[5].value=x;
	
	
	//sa nu uit de delay

	while(a || b || c || d || e || f){
		a=A1_GetVal();
		b=A3_GetVal();
		c=D11_GetVal();
		d=A0_GetVal();
		e=A2_GetVal();
		f=D5_GetVal();
	
		if(a==0)
			s[0].value=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL)-s[0].value;
		if(b==0)
			s[1].value=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL)-s[1].value;
		if(c==0)
			s[2].value=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL)-s[2].value;
		if(d==0)
			s[3].value=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL)-s[3].value;
		if(e==0)
			s[4].value=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL)-s[4].value;
		if(f==0)
			s[5].value=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL)-s[5].value;

	}

}

void takeAvg(int min_avg[6], int max_avg[6]){
	int x=0,i;
	struct sensor s[6];
	while(x!=1){
		x=Button_GetVal();
	}
	for(i=0; i<1000; i++){
		irSensors(s);
		min_avg[0]+=s[0].value;
		min_avg[1]+=s[1].value;
		min_avg[2]+=s[2].value;
		min_avg[3]+=s[3].value;
		min_avg[4]+=s[4].value;
		min_avg[5]+=s[5].value;
	}
	min_avg[0]/=1000;
	min_avg[1]/=1000;
	min_avg[2]/=1000;
	min_avg[3]/=1000;
	min_avg[4]/=1000;
	min_avg[5]/=1000;

	x=0;

	while(x!=1){
		x=Button_GetVal();
	}
	for(i=0; i<1000; i++){
		irSensors(s);
		max_avg[0]+=s[0].value;
		max_avg[1]+=s[1].value;
		max_avg[2]+=s[2].value;
		max_avg[3]+=s[3].value;
		max_avg[4]+=s[4].value;
		max_avg[5]+=s[5].value;
	}

	max_avg[0]/=1000;
	max_avg[1]/=1000;
	max_avg[2]/=1000;
	max_avg[3]/=1000;
	max_avg[4]/=1000;
	max_avg[5]/=1000;

}


void calibrate(int min_avg[6], int max_avg[6], struct sensor s[6]){
	s[0].value=1000*(9*s[0].value+max_avg[0]-10*min_avg[0])/(max_avg[0]-min_avg[0]);
	s[1].value=1000*(9*s[1].value+max_avg[1]-10*min_avg[1])/(max_avg[1]-min_avg[1]);
	s[2].value=1000*(9*s[2].value+max_avg[2]-10*min_avg[2])/(max_avg[2]-min_avg[2]);
	s[3].value=1000*(9*s[3].value+max_avg[3]-10*min_avg[3])/(max_avg[3]-min_avg[3]);
	s[4].value=1000*(9*s[4].value+max_avg[4]-10*min_avg[4])/(max_avg[4]-min_avg[4]);
	s[5].value=1000*(9*s[5].value+max_avg[5]-10*min_avg[5])/(max_avg[5]-min_avg[5]);

}

void readSensors(int min_avg[6], int max_avg[6], struct sensor s[6]){
	irSensors(s);
	calibrate(min_avg, max_avg, s);
}
