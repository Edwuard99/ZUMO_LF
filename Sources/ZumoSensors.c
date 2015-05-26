/*#################################################################################################################################################################################
**		Fisierul sursa ZumoSensors.c contine functiile necesare citirii si calibrari valorilor
**senzoriilor, dar si stabileste cat de mult negru vede fiecare senzor. 
**Functiile din fisier sunt decalarate  in header-ul ZumoRobot.h.
**#################################################################################################################################################################################*/
#include "ZumoRobot.h"


void irSensors(struct sensor s[6]){
	/*#############################################################################################################################################################################
	**		Functia irSensors este folosita la citirea valorilor "raw" ale senzorilor.
	**Argumentul functiei este un vector de tip structura de date sensor.
	**Pasii pe care ii urmeaza:
	**	--declara pini care sunt conectati la senzori ca pini de output
	**	--seteaza valorile senzorilor pe HIGH -> se incarca condensatorul
	**	--asteapta 50us pentru incarcarea completa a condensatorului
	**	--declara pini care sunt conectati la senzori ca pini de input
	**	--reseteaza timer-ul deoarece poate iesi din limitele tipului de date int dupa un anumit timp
	**	--citirea valorii timer-ului
	**  --atribuirea valorii timer-ului variabilelor unde vom retine valorile senzorilor
	**	--intrarea in bucla de citire a senzorilor(se va termina cand toti pinii de la senzori au valoarea 0):
	**		++variabila timer este folosita pentru a iesi din bucla daca este depasita valoarea constantei prag(datele mai mari decat valoarea pragului nu sunt relevante + 
	**		  citire mai rapida)
	**      ++verificarea valorilor pinilor conectati la senzori
	**      ++valoarea unui senzor devine egala cu valoarea timer-ului daca pinul respectiv are valoarea 1 (in final valoarea unui senzor va fi egala cu ultima valoare a
	**		  timer-ului inainte ca pinul respectiv sa ia valoarea 0)
	**		++daca variabila timer este mai mare decat valoarea pragului atunci este intrerupta executia buclei
	**#############################################################################################################################################################################*/
	int v[6];
	int timer,i;
	const int prag=1000;
	IR_LED_SetOutput();
	IR_LED_PutVal(1);

	/*** Declararea senzorilor ca output.                            ***/
	A1_SetOutput();
	A3_SetOutput();
	D11_SetOutput();
	A0_SetOutput();
	A2_SetOutput();
	D5_SetOutput();

	/*** Setarea senzoriilor pe HIGH.                                ***/
	A1_PutVal(1);
	A3_PutVal(1);
	D11_PutVal(1);
	A0_PutVal(1);
	A2_PutVal(1);
	D5_PutVal(1);

	/*** Asteapta 50us pentru incarcarea completa a condensatorului. ***/
	WAIT1_Waitus(50);


	//Declararea senzorilor ca input.                                ***/
	A1_SetInput();
	A3_SetInput();
	D11_SetInput();
	A0_SetInput();	
	A2_SetInput();
	D5_SetInput();

	/*** Resetarea timer-ului.                                       ***/
	CountTimer_ResetCounter((LDD_TDeviceData *)NULL);

	/*** Citirea vaorii timer-ului.                                  ***/
	timer=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL); 
	
	s[0].value=timer;
	s[1].value=timer;
	s[2].value=timer;
	s[3].value=timer;
	s[4].value=timer;
	s[5].value=timer;
	
	
	/*** Bucla de citire -- executia buclei se va termina cand s-a terminat citirea tuturor senzorilor.                 ***/
	while(v[0] || v[1] || v[2] || v[3] || v[4] || v[5]){
		/*** Variabila timer este acum folosit ca un prag pentru a nu pierde prea mult timp cat senzorii sunt pe negru. ***/
		timer=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL);

		/*** Variabilelor s1-s6 le este atribuita valoarea intrarilor senzoriilor(0 sau 1).                             ***/
		v[0]=A1_GetVal();
		v[1]=A3_GetVal();
		v[2]=D11_GetVal();
		v[3]=A0_GetVal();
		v[4]=A2_GetVal();
		v[5]=D5_GetVal();


		/*** Daca intrarea unui senzor este 1 ii este atribuita variabilei s[i].value ultima valoare a timer-ului.      ***/
		for(i=0; i<6; i++){
			if(v[i])
				s[i].value=CountTimer_GetCounterValue((LDD_TDeviceData *)NULL);
		}

		if(timer>prag)
			break;

	}

}



void calibrate(int64_t min_avg[6], int64_t max_avg[6], struct sensor s[6]){
	/*#############################################################################################################################################################################
	**		Functia calibrate incearca(si reuseste) sa ajusteze valorile senzorilor astfel incat pe alb toti senzorii vor arata 100, iar pe negru 
	**aproape 1000 in majoritatea cazurilor, calibrari extrem de exacte nefiind necesare.
	**Aceasta functie foloseste ca argumente doi vectori de cate 6 elemente reprezentand valoarea "raw" pe alb si respectiv pe negru pentru fiecare
	**dintre cei 6 senzori. Se folosesc functii matematice de gradul I pentru a determina formula corespunzatoare calibrarii:
	**f(min)=a*min+b;
	**f(min)=100;
	**->a*min+b=100;
	**->b=100-a*min; (1)
	**
	**f(max)=a*max+b;
	**f(max)=1000;
	**->a*max+b=1000;
	**->b=1000-a*max; (2)
	**
	**Din (1) si (2) ->
	**->100-a*min=1000-a*max;
	**->a*(max-min)=900;
	**->a=900/(max-min);
	**->b=100-[(900*min)/(max-min)];
	**->b=100*(max-10*min)/(max-min);
	**
	**f(s)=a*s+b;
	**<=>f(s)=[900*s+10*(max-10*min)]/(max-min);
	**<=>f(s)=[100*(9*s+max-10*min)]/(max-min);
	**#############################################################################################################################################################################*/
	s[0].value=100*(9*s[0].value+max_avg[0]-10*min_avg[0])/(max_avg[0]-min_avg[0]);
	s[1].value=100*(9*s[1].value+max_avg[1]-10*min_avg[1])/(max_avg[1]-min_avg[1]);
	s[2].value=100*(9*s[2].value+max_avg[2]-10*min_avg[2])/(max_avg[2]-min_avg[2]);
	s[3].value=100*(9*s[3].value+max_avg[3]-10*min_avg[3])/(max_avg[3]-min_avg[3]);
	s[4].value=100*(9*s[4].value+max_avg[4]-10*min_avg[4])/(max_avg[4]-min_avg[4]);
	s[5].value=100*(9*s[5].value+max_avg[5]-10*min_avg[5])/(max_avg[5]-min_avg[5]);
}

void readSensors(int64_t min_avg[6], int64_t max_avg[6], struct sensor s[6]){
	/*#############################################################################################################################################################################
	**		Functia readSensors combina functiile irSensors si calibrate, dar si stabileste cat si daca un senzor vede negru/linia.
	**Functia ia argumentele necesare celorlalte doua functii.
	**Pasii pe care ii urmeaza:
	**	--apeleaza functia irSensors pentru valorile "raw" ale senzorilor
	**	--calibreaza valorile "raw" apeland functia calibrate
	**	--pentru fiecare senzor verifica daca acesta depaseste pragul de seen(valoarea va depasi acest prag daca linia este cat de cat prin apropiere), iar 
	**	  variabila s[i].seen va avea valoarea 1
	**	--pentru fiecare senzor verifica daca acesta depaseste pragul de stop(valoarea va depasi de obicei acest prag daca senzorii se afla pe o pata mare neagra - sosire), iar
	**	  variabila s[i].seen va avea valoarea 0
	**  --daca nicuna din cele doua conditii nu este indeplinita variabila s[i].seen va avea valoarea -1
	**#############################################################################################################################################################################*/
	int i;
	const int seen=120, stop=800;
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