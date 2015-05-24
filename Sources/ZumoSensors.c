#include "ZumoRobot.h"


void irSensors(struct sensor s[6]){
	int v[6],exit=0;
	int timer,i;
	IR_LED_SetOutput();
	IR_LED_PutVal(1);

	//Declararea senzorilor ca output
	A1_SetOutput();
	A3_SetOutput();
	D11_SetOutput();
	A0_SetOutput();
	A2_SetOutput();
	D5_SetOutput();

	//Setarea senzoriilor pe HIGH
	A1_PutVal(1);
	A3_PutVal(1);
	D11_PutVal(1);
	A0_PutVal(1);
	A2_PutVal(1);
	D5_PutVal(1);

	
	WAIT1_Waitus(50);//Asteapta 50us pentru incarcarea completa a capacitorului


	//Declararea senzorilor ca input
	A1_SetInput();
	A3_SetInput();
	D11_SetInput();
	A0_SetInput();	
	A2_SetInput();
	D5_SetInput();


	CountTimer_ResetCounter((LDD_TDeviceData *)NULL); //resetarea counter-ului
	timer=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL); //citirea vaorii counter-ului
	
	s[0].value=timer;
	s[1].value=timer;
	s[2].value=timer;
	s[3].value=timer;
	s[4].value=timer;
	s[5].value=timer;
	
	
	//Bucla de citire -- executia buclei se va termina cand s-a terminat citirea tuturor senzorilor
	while(v[0] || v[1] || v[2] || v[3] || v[4] || v[5]){
		//timer este acum folosit ca un prag pentru a nu pierde prea mult timp cat senzorii sunt pe negru
		timer=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL);

		//Variabilelor s1-s6 le este atribuita valoarea intrarilor senzoriilor(0 sau 1)
		v[0]=A1_GetVal();
		v[1]=A3_GetVal();
		v[2]=D11_GetVal();
		v[3]=A0_GetVal();
		v[4]=A2_GetVal();
		v[5]=D5_GetVal();


		//Daca intrarea unui senzor este 1 ii este atribuita variabilei s[i].value ultima valoare a timer-ului
		for(i=0; i<6; i++){
			if(v[i])
				s[i].value=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL);
		}

		if(timer>3000)
			break;

	}

}



void calibrate(int64_t min_avg[6], int64_t max_avg[6], struct sensor s[6]){
	/*Functia calibrate prelucreaza valorile maxime pe alb si negru si 
	**returneaza citiri mai precise si mai uniformizate ale senzorilor
	*/
	s[0].value=100*(9*s[0].value+max_avg[0]-10*min_avg[0])/(max_avg[0]-min_avg[0]);
	s[1].value=100*(9*s[1].value+max_avg[1]-10*min_avg[1])/(max_avg[1]-min_avg[1]);
	s[2].value=100*(9*s[2].value+max_avg[2]-10*min_avg[2])/(max_avg[2]-min_avg[2]);
	s[3].value=100*(9*s[3].value+max_avg[3]-10*min_avg[3])/(max_avg[3]-min_avg[3]);
	s[4].value=100*(9*s[4].value+max_avg[4]-10*min_avg[4])/(max_avg[4]-min_avg[4]);
	s[5].value=100*(9*s[5].value+max_avg[5]-10*min_avg[5])/(max_avg[5]-min_avg[5]);
}

void readSensors(int64_t min_avg[6], int64_t max_avg[6], struct sensor s[6]){
	/*Functia imbina functiile irSensors si calibrate si 
	**atribuie valoarea -1 variabilelor s[i].seen daca senzorul i 
	**vede linia si 0 in caz contrar
	*/
	int i;//contor
	const int seen=130, stop=700;//valoare minima pe care senzorul trebuie sa o ia pentru a se considera ce vede linia
	irSensors(s);
	calibrate(min_avg, max_avg, s);
	for(i=0; i<6; i++){
		if(s[i].value>stop)
			s[i].seen=1;
		else if(s[i].value>seen)
			s[i].seen=0;
		else
			s[i].seen=-1;
	}
}