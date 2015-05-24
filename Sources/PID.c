#include "ZumoRobot.h"

int propder(struct sensor s[6]){
	/*In aceasta functie am implementat algoritmul PD propriu-zis.
	**Functia ia ca argument un vector de tip structura de date sensor.
	**Functia:
	**--determina pozitia liniei:
	**  ++in functie sunt setate distantele fata de centru(proportionale cu distantele reale fata de centru)
	**  ++apeleaza functia see si atribuie valoare variabilei seen
	**  ++in functie de variabila seen avem 3 cai de executie:
	**    >>seen==-1 -> niciun senzor nu vede linia:
	**      ->daca cel mai din dreapta senzor a vazut ultimul linia(eroarea <= -450) robotul vireaza la maxim spre dreapta
	**      ->daca cel mai din stanga senzor a vazut ultimul linia(eorarea >= 450) robotul vireaza la maxim spre stanga
	**    >>seen==0 -> doar unii senzori vad linia -> calculeaza pozitia cu ajutorul unei medii aritmetice ponderate:
	**                                                (inmulteste valoarea senzorului cu distanta si aduaga rezultatul la eroare, apoi imparte eroarea la suma valorilor,
	**                                                 daca senzorul respectiv a vazut linia - nu se afla pe alb)
	**    >>seen==1 ->toti senzorii se afla pe negru -> oprirea motoarelor -> asteapta apasarea butonului pentru a porni din nou
	**--calculeaza eroarea rezultata din pozitia fata de centru inmultind-o cu constanta kp
	**--calculeaza eroarea in functie de cat de mult s-a modificat fata de ultima eroare inmultind diferenta cu kd
	**--aduna cele doua erori si returneaza eroarea finala
	*/
	int i,d=0,button=1;
	int seen; 
	float diff;
	static int last_error=0; //Tine minte ultima eroare in aceasta variabila
	int64_t error=0;
	const float kd=10,kp=5; //Cele doua constante(kd si kp) modifica cat de mult participa derivativul/proportionalul la eroare

	s[0].dist=-500;
	s[1].dist=-270;
	s[2].dist=-80;
	s[3].dist=80;
	s[4].dist=270;
	s[5].dist=500;

	seen=see(s);

	if(seen==-1){
		if(last_error<-450)
			error=-1000;
		else if (last_error>450)
			error=1000;
	}
	else if (seen==0){
		for(i=0; i<6; i++){
			if(s[i].seen>=0){
				error+=s[i].value*s[i].dist;
				d+=s[i].value;
			}
		}
		error/=d;
		diff=error-last_error;
	}
	else if (seen==1){
		//Incepe o bucla infinita cand toti senzorii vad linia--robotul a ajuns la FINISH
		PWM_dreapta_SetRatio16(65535);
		PWM_stanga_SetRatio16(65535);
		while(button)
			button=Button_GetVal();
		WAIT1_Waitms(500);
	}

	last_error=error;
	error*=kp;

	diff*=kd;
	error+=diff;

	return error;
}

int see(struct sensor s[6]){
	int seen;
	if(s[0].seen==1 && s[1].seen==1 && s[2].seen==1 && s[3].seen==1 && s[4].seen==1 && s[5].seen==1)
		seen=1;
	else if(s[0].seen>=0 || s[1].seen>=0 || s[2].seen>=0 || s[3].seen>=0 || s[4].seen>=0 || s[5].seen>=0)
		seen=0;
	else
		seen=-1;

	return seen;
}
