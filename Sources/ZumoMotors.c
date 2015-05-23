#include "ZumoRobot.h"

void motor(int x, int y) //valorile pentru viteza sunt cele reale (65535=max)
{
	//stop();
	sens_dreapta_SetOutput();
	sens_stanga_SetOutput();

	if(x>0)
	{
		sens_stanga_PutVal(1);
	}
	else
	{
		sens_stanga_PutVal(0);
		x*=-1;
	}
	if(y>0)
	{
		sens_dreapta_PutVal(1);
	}
	else
	{
		sens_dreapta_PutVal(0);
		y*=-1;
	}
	const int maxspd=65535;

	PWM_stanga_SetRatio16(maxspd - x);
	PWM_dreapta_SetRatio16(maxspd - y);



}

void drive(int error){
	const int maxspd=60000, mxsp=65535;
	const int k=131;
	error*=k;
	if(error>0)
		motor(mxsp, maxspd-error);
	else{
		if(error>60000)
			motor(0, maxspd);
		else
			motor(maxspd+error, maxspd);
	}

}
