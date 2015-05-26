/*#################################################################################################################################################################################
**		Fisierul sursa ZumoSensors.c contine functiile necesare controlului motoarelor 
**in functie de eroare.
**	Functiile din fisier sunt decalarate  in header-ul ZumoRobot.h.
**#################################################################################################################################################################################*/
#include "ZumoRobot.h"

void motor(int left, int right) 
{
	/*#############################################################################################################################################################################
	**		Functia motor este functia de control al motoarelor.
	**Aceasta functie ia ca si argument vitezele celor doua motoare(-65535 -> 65535), iar in cazul in care viteza este negativa robotul va merge inapoi.
	**Pasii pe care ii urmeaza:
	**	--seteaza pinii corespunzatori motoarelor ca pini de output
	**	--daca viteza motorului din stanga/dreapta este negativa sa inverseaza directia
	**	--scade din viteza maxima viteza data deoarece 65535 este valoarea pentru viteza 0, iar 0 este valoarea pentru viteza 65535, astfel inversand valorile pentru viteza
	**#############################################################################################################################################################################*/
	const int maxspd=65535;

	sens_dreapta_SetOutput();
	sens_stanga_SetOutput();

	if(left>0)
	{
		sens_stanga_PutVal(1);
	}
	else
	{
		sens_stanga_PutVal(0);
		left=-left;
	}
	if(right>0)
	{
		sens_dreapta_PutVal(1);
	}
	else
	{
		sens_dreapta_PutVal(0);
		right=-right;
	}

	PWM_stanga_SetRatio16(maxspd - left);
	PWM_dreapta_SetRatio16(maxspd - right);
	PWM_stanga_Enable();
	PWM_dreapta_Enable();


}

void drive(int64_t error){
	/*#############################################################################################################################################################################
	**		Functia drive controleaza motoarele in functie de valoarea erorii.
	**Argumentul functiei este eroarea.
	**Pasii pe care ii urmeaza:
	**	--eroarea este inmultita cu constanta k(eroarea de 500 va fi acum de 65535), pentru a ridica valoarea acesteia la nivelul necesar pentru a controla motoarele
	**	--daca eroarea este pozitiva -> apeleaza funcita motor unde argumentul din stanga va fi viteza maxima, iar cel din stanga diferenta dintre viteza maxima si
	**	  eroarea -> motorul va incetini sau chiar se va roti in directie opusa in functie de eroare
	**	--daca eroarea este negativa -> apeleaza funcita motor unde argumentul din stanga va fi suma dintre viteza maxima si eroarea, iar cel din stanga viteza
	**	  maxima -> motorul va incetini sau chiar se va roti in directie opusa in functie de eroare
	**#############################################################################################################################################################################*/
	const int maxspd=65535;
	const int k=131;
	error*=k;
	/*if(error<-65535)
		error=-65535;
	if(error>65535)
		error=65535;*/
	if(error>0)
		motor(maxspd, maxspd-error);
	else{
		motor(maxspd+error, maxspd);
	}
}
