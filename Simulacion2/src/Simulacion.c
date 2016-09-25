/*
 ============================================================================
 Name        : Simulacion2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int tpll, t, tf, tps, nsn, nsv, ntn, ntv, stlln, stllv, stsn, stsv, varN, varV, rnsv, rnsn;

int main(void) {

	/*
	printf("Ingrese el valor de la variable de control V:");
	scanf("%d", &varV);
	printf("Ingrese el valor de la variable de control N:");
	scanf("%d", &varN);
	*/

	//realizarSimulacionDiaria();

	/*Tests

	1-

	int tps = calculoProximaSalida(241);
	printf("%d\n", tps);
	*/

	int i = 0;
	while(i<1000){
		int ran = random_number(2,10,i);
		printf("%d\n",ran);
		i++;
	}


	return EXIT_SUCCESS;
}

void realizarSimulacionAnual(int varV, int varN){

	int i = 0;

	while(i < 365){
		realizarSimulacionDiaria(varV, varN);
	}
}

void realizarSimulacionDiaria(){

	tpll = 0, t = 0, tf = 36000, tps = 40000, nsn = 0, nsv = 0, ntn = 0, ntv= 0, stlln = 0, stllv = 0, stsn = 0, stsv = 0;

	ramas();

	if(t <= tf){
		ramas();
	}else{
		if(nsn+nsv >= 1){
			ramas();
		}else{
			calculoEImpresionResultados();
		}
	}
}

int calculoProximaSalida(){
	int tps;

	if(div(t,120).rem == 0){
		return t;
	}

	tps = (div(t,120).quot + 1) * 120;
	return tps;
}

int calcularIA(){

	int ia;

	if(t <= 10800){
		//De 9 AM a 12 PM
		ia = random_number(2,10);
	} else if (t > 10800 && t <= 21600){
		//De 12 PM a 3 PM
		ia = random_number(30,120);
	} else if (t <= 36000){
		//De 3 PM a 7 PM
		ia = random_number(10,20);
	}

	return ia;
}

int random_number(int min_num, int max_num, int i){
	int result=0,low_num=0,hi_num=0;
	if(min_num<max_num)
	{
		low_num=min_num;
		hi_num=max_num+1; // this is done to include max_num in output.
	}else{
		low_num=max_num+1;// this is done to include max_num in output.
		hi_num=min_num;
	}
	srand(i*time(0));
	result = (rand()%(hi_num-low_num))+low_num;
	return result;
}

//Prototipo de funcion
int cambioCola(){
	if(div(nsv,varV).quot<= div(nsn,varN).quot){
		return 0;
	}
	return 1;
}

void ramas(){
	if (tpll <= tps){
			// Evento llegada

			t = tpll;

			int ia = calcularIA();

			tpll = t + ia;

			if(tps == 40000){
				//Genera una salida
				tps = calculoProximaSalida(t);
			}
			else
			{
				//No genera salida
			}

			float random; //= random_number(0,1);
			if(random <= 0.8 ){
				//Persona normal
				//Entra cola normal
				nsn+=1;
				stlln+=t;

			}else{
				//Persona VIP
				int colaNormal = cambioCola();
				if(colaNormal==0){
					nsv += 1;
					stllv += t;
				}else{
					nsn += 1;
					stlln += t;
				}
			}
		}
		else
		{
			// Evento salida
			algoritmoResta();
			nsv = nsv - rnsv;
			nsn = nsn - rnsn;
			ntn = ntn + rnsn;
			ntv = ntv + rnsv;
			stsn = stsn + rnsn*t;
			stsv = stsv + rnsv*t;

			if(nsv+nsn >= 1){

			} else {

			}
		}
}

void algoritmoResta(){

}

void calculoEImpresionResultados(){

	//printf("%f","El PTEN es:"((stsn-stlln)/ntn));
	//printf("%f","El PTEV es:"((stsv-stllv)/ntv));

}







