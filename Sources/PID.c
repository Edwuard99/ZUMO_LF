#include "ZumoRobot.h"

int proportional(struct sensor s[6]){
	int64_t error,last_error=0,d,seen=1,i;

	s[0].dist=-500;
	s[1].dist=-300;
	s[2].dist=-100;
	s[3].dist=100;
	s[4].dist=300;
	s[5].dist=500;

	if(s[0].value<1200 && s[1].value<1200 && s[2].value<1200 && s[3].value<1200 && s[4].value<1200 && s[5].value<1200)
		seen=0;
	else
		seen=1;

	if(last_error<-460 && seen==0){
		error=-500;
	}
	else if (last_error>460 && seen==0){
		error=500;
	}
	else{
		for(i=0; i<6; i++){
			error+=s[i].value*s[i].dist;
			d+=s[i].value;
		}
	}

	error/=d;

	last_error=error;


}