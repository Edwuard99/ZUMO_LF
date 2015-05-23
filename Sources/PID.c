#include "ZumoRobot.h"

int propder(struct sensor s[6], int error){
	int i,d;
	int seen; //Variabila poate lua valorile:-1(niciun senzor nu vede linia), 0(unii senzori vad linia) sau 1(toti senzorii vad linia)
	float diff;
	static int last_error=0; //Tine minte ultima eroare in aceasta variabila
	const float kd=0.7,kp=1; //Cele doua constante modifica cat de mult participa derivativul/proportionalul la eroare

	//Ponderile folosite pentru a calcula pozitia liniei(sunt direct proportionale cu distantele reale ale senzorilor fata de centru)
	s[0].dist=-500;
	s[1].dist=-270;
	s[2].dist=-80;
	s[3].dist=80;
	s[4].dist=270;
	s[5].dist=500;

	seen=see(s);

	if(last_error<=-500 && seen==-1){
		error=-1000;
	}
	else if (last_error>=500 && seen==-1){
		error=1000;
	}
	else if(seen==1){
		//Incepe o bucla infinita cand toti senzorii vad linia--robotul a ajuns la FINISH
		while(1);
	}
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
