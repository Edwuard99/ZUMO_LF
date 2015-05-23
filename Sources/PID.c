#include "ZumoRobot.h"

int propder(struct sensor s[6], int error){
	int d=0,i,maxspd=45000;
	int seen;
	const int a=131;
	const double kp=1;
	float diff;
	static int last_error=0;
	const float kd=0.7;
	int x=1;


	s[0].dist=-600;
	s[1].dist=-300;
	s[2].dist=-100;
	s[3].dist=100;
	s[4].dist=300;
	s[5].dist=600;

	seen=see(s);

	error=0;


	if(last_error<=-500 && seen==-1){
		error=-1000;
	}
	else if (last_error>=500 && seen==-1){
		error=1000;
	}
	/*else if(seen==1){
		x=1;
		while(x){
			x=Button_GetVal();
		}
	}*/
	else{
		for(i=0; i<6; i++){
			error+=s[i].value*s[i].dist*s[i].seen;
			d+=s[i].value*s[i].seen;
		}
		error/=d;
		diff=error-last_error;

	}
	last_error=error;
	error*=kp;



	diff*=kd;
	error+=diff;

	return error;
}

int see(struct sensor s[6]){
	int seen;
	if(s[0].seen && s[1].seen && s[2].seen && s[3].seen && s[4].seen && s[5].seen)
		seen=1;
	else if(s[0].seen || s[1].seen || s[2].seen || s[3].seen || s[4].seen || s[5].seen)
		seen=0;
	else
		seen=-1;

	return seen;
}

/*int derivative(struct sensor s[6], int error){
	bool seen;
	seen=see(s);
	float diff;
	static int last_error=0;
	const float kd=0.5;
	if(error==-500 && !seen){
		diff=-500;
	}
	else if(error==500 && !seen){
		diff=500;
	}
	else{
		diff=error-last_error;
		last_error=error;
	}

	diff*=kd;
	error+=diff;
	return error;
}*/

int control(struct sensor s[6], int error){
	error=proportional(s, error);
	error=derivative(s, error);
	return error;
}
