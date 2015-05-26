/*#################################################################################################################################################################################
**		Fisierul sursa PID.c contine functia corespunzatoare algoritmului PD propriu-zis
**si o functie care stabileste cati senzori vad linia pentru a determina daca robotul a ajuns
**la linia de sosire, ce sa faca in caz ca a pierdut linia sau cum sa se redreseze pentru a
**urmari cat mai fidel linia.
**	Functiile din fisier sunt decalarate  in header-ul ZumoRobot.h.
**#################################################################################################################################################################################*/
#include "ZumoRobot.h"

int propder(struct sensor s[6]){
	/*#############################################################################################################################################################################
	**		In aceasta functie am implementat algoritmul PD propriu-zis.
	**Functia ia ca argument un vector de tip structura de date sensor.
	**Pasii pe care ii urmeaza:
	**	--determina pozitia liniei:
	**  	++in functie sunt setate distantele fata de centru(proportionale cu distantele reale fata de centru)
	**  	++apeleaza functia see si atribuie valoare variabilei seen
	**  	++in functie de variabila seen avem 3 cai de executie:
	**    		>>seen==-1 -> niciun senzor nu vede linia:
	**      		->daca cel mai din dreapta senzor a vazut ultimul linia(eroarea <= -450) robotul vireaza la maxim spre dreapta
	**      		->daca cel mai din stanga senzor a vazut ultimul linia(eorarea >= 450) robotul vireaza la maxim spre stanga
	**    		>>seen==0 -> doar unii senzori vad linia -> calculeaza pozitia cu ajutorul unei medii aritmetice ponderate:
	**                                                		(inmulteste valoarea senzorului cu distanta si aduaga rezultatul la eroare, apoi imparte eroarea la suma valorilor,
	**                                                 		daca senzorul respectiv a vazut linia - nu se afla pe alb)
	**    		>>seen==1 ->toti senzorii se afla pe negru -> oprirea motoarelor -> asteapta apasarea butonului pentru a porni din nou
	**	--calculeaza eroarea rezultata din pozitia fata de centru inmultind-o cu constanta kp
	**	--calculeaza eroarea in functie de cat de mult s-a modificat fata de ultima eroare inmultind diferenta cu kd
	**	--aduna cele doua erori si returneaza eroarea finala
	###############################################################################################################################################################################*/

	/*** i - contor folosi la for-uri                                  ***/
	/*** d - suma valorilo senzorilor senzorilor care au vazut linia   ***/
	/*** button - valoarea intrarii la care este conectat butonul      ***/
	int i,d=0,button=1; 
	int seen;
	/*** diff - diferenta dintre eroarea curenta si eroarea anterioara ***/
	int diff; 
	/*** last_error - eroarea anterioara                               ***/
	static int last_error=0;
	/*** error - eroarea                                               ***/
	int64_t error=0;
	/*** kd - cat participa componenta derivativa la eroare            ***/
	/*** kp - cat participa componenta proportionala la eroare         ***/
	const float kd=5,kp=3;

	/*** s[i].dist - distantele fata de centru                         ***/
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
		/*** Oprirea motoarelor.                                       ***/
		motor(0,0);
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
	/*#############################################################################################################################################################################
	**		Aceasta functie returneaza variabila seen a carui valoare depinde de cati senzori vad linia.
	**Functia ia ca argument un vector de tip structura de date sensor.
	**Pasii pe care ii urmeaza:
	**	--verifica daca toti senzorii vad un negru intens -> seen=1
	**  --verifica daca cel putin un senzor vede linia -> seen=0
	**  --daca conditiile de mai sus nu sunt indeplinite -> niciun senzor nu vede linia -> seen=-1
	**#############################################################################################################################################################################*/
	int seen;
	if(s[0].seen==1 && s[1].seen==1 && s[2].seen==1 && s[3].seen==1 && s[4].seen==1 && s[5].seen==1)
		seen=1;
	else if(s[0].seen>=0 || s[1].seen>=0 || s[2].seen>=0 || s[3].seen>=0 || s[4].seen>=0 || s[5].seen>=0)
		seen=0;
	else
		seen=-1;

	return seen;
}
