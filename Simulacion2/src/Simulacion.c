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

int main(void) {

	int varV;
	int varN;

	/*
	printf("Ingrese el valor de la variable de control V:");
	scanf("%d", &varV);
	printf("Ingrese el valor de la variable de control N:");
	scanf("%d", &varN);
	*/

	//realizarSimulacionAnual(varV, varN);

	/*Tests
	int tps = calculoProximaSalida(241);
	printf("%d\n", tps);
	*/

	return EXIT_SUCCESS;
}

void realizarSimulacionAnual(int varV, int varN){

	int i = 0;

	while(i < 365){
		realizarSimulacionDiaria(varV, varN);
	}
}

void realizarSimulacionDiaria(int varV, int varN){

	int tpll = 0, t = 0, tf = 36000, tps = 40000, nsn = 0, nsv = 0, ntn = 0, ntv= 0, stlln = 0, stllv = 0, stsn = 0, stsv = 0;

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
	}
	else
	{
		// Evento salida
	}
}

int calculoProximaSalida(int t){
	int tps;

	if(div(t,120).rem == 0){
		return t;
	}

	tps = (div(t,120).quot + 1) * 120;
	return tps;
}

int calcularIA(){

	int ia = random_number(2,10);

	//printf("%d\n",ia);

	return ia;
}

int random_number(int min_num, int max_num)
	{
		int result=0,low_num=0,hi_num=0;
		if(min_num<max_num)
		{
			low_num=min_num;
			hi_num=max_num+1; // this is done to include max_num in output.
		}else{
			low_num=max_num+1;// this is done to include max_num in output.
			hi_num=min_num;
		}
		srand(time(NULL));
		result = (rand()%(hi_num-low_num))+low_num;
		return result;
	}












