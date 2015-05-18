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

	if(s[0].value || s[1].value || s[2].value || s[3].value || s[4].value || s[5].value)
		seen=1;
	else
		seen=0;


	if(last_error==-5 && !seen){
		error=-5;
	}
	else if (last_error==5 && !seen){
		error=5;
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