#include "ZumoRobot.h"

int proportional(struct sensor s[6]){
	int error=0,d=0,i,maxspd=65535;
	bool seen;
	const int a=131;
	static int last_error=0;

	s[0].dist=-500;
	s[1].dist=-300;
	s[2].dist=-100;
	s[3].dist=100;
	s[4].dist=300;
	s[5].dist=500;

	if(s[0].seen || s[1].seen || s[2].seen || s[3].seen || s[4].seen || s[5].seen)
		seen=1;
	else
		seen=0;


	if(last_error==-500 && !seen){
		error=-500;
	}
	else if (last_error==500 && !seen){
		error=500;
	}
	else{
		for(i=0; i<6; i++){
			error+=s[i].value*s[i].dist*s[i].seen;
			d+=s[i].value*s[i].seen;
		}
	}

	error/=d;

	last_error=error;

	Term1_SendNum(error);
}