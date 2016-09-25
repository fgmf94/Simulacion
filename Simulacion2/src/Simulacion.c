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

int tpll, t, tf, tps, nsn, nsv, ntn, ntv, stlln, stllv, stsn, stsv, varN, varV, rnsv, rnsn, j, sn, sv, c, finalizo, ia;

int main(void) {


	printf("Ingrese el valor de la variable de control V:");
	scanf("%d", &varV);
	printf("Ingrese el valor de la variable de control N:");
	scanf("%d", &varN);

	realizarSimulacionDiaria();

	return EXIT_SUCCESS;
}

void realizarSimulacionAnual(int varV, int varN){

	int i = 0;

	while(i < 365){
		realizarSimulacionDiaria(varV, varN);
	}

}

void realizarSimulacionDiaria(){
	tpll = 0, t = 0, tf = 36000, tps = 400000, nsn = 0, nsv = 0, ntn = 0, ntv= 0, stlln = 0, stllv = 0, stsn = 0, stsv = 0;
	ramas();
}

void calculoProximaSalida(){

	if(div(t,120).rem == 0){
		tps = t;
	}

	tps = (div(t,120).quot + 1) * 120;
}

int calcularIA(){

	int iac;

	if(t <= 10800){
		//De 9 AM a 12 PM
		iac = random_number(1,7);
	} else if (t > 10800 && t <= 21600){
		//De 12 PM a 3 PM
		iac = random_number(10,30);
	} else if (t <= 36000){
		//De 3 PM a 7 PM
		iac = random_number(5,15);
	}

	return iac;
}

int random_number(int min_num, int max_num){
	int result=0,low_num=0,hi_num=0;
	if(min_num<max_num)
	{
		low_num=min_num;
		hi_num=max_num+1; // this is done to include max_num in output.
	}else{
		low_num=max_num+1;// this is done to include max_num in output.
		hi_num=min_num;
	}
	srand(j*time(0));
	result = (rand()%(hi_num-low_num))+low_num;
	j++;
	if(j == 2147483646){
		j = 0;
	}
	return result;
}

//Prototipo de funcion
int cambioCola(){
	if(div(nsv,varV).quot <= div(nsn,varN).quot){
		return 0;
	}
	return 1;
}

void ramas(){
	if (tpll <= tps)
	{
		//Evento llegada
		t = tpll;
		ia = calcularIA();
		tpll = t + ia;
		int random = random_number(1,100);
		if(random <= 80){
			//Persona normal
			//Entra cola normal
			nsn = nsn + 1;
			stlln = stlln + t;
		}
		else
		{
			//Persona VIP
			int colaNormal = cambioCola();
			if(colaNormal==0){
				nsv = nsv + 1;
				stllv = stllv + t;
			}else{
				nsn = nsn + 1;
				stlln = stlln + t;
			}
		}

		if(tps >= 400000){
			//Genera una salida
			calculoProximaSalida();
		}
		else
		{
			//No genera salida
		}
	}
	else
	{
		//Evento salida
		t = tps;
		algoritmoResta();
		nsv = nsv - rnsv;
		nsn = nsn - rnsn;
		ntn = ntn + rnsn;
		ntv = ntv + rnsv;
		stsn = stsn + rnsn*t;
		stsv = stsv + rnsv*t;
		if(nsv + nsn >= 1){
			tps = tps + 120;
		} else {
			tps = 400000;
		}
	}

	//Impresion de vector de estado

	printf("Vector de estado: \n");
	printf("nsn = %d, nsv = %d, t = %d, tps = %d, tpll = %d, ia = %d", nsn, nsv, t, tps, tpll, ia);
	printf("\n \n");

	//Finalizó simulación?
	if(t <= tf)
	{
		ramas();
	}
	else
	{
		if(nsn+nsv >= 1)
		{
			//Rutina de vaciamiento
			tpll = 500000;
			ramas();
		}
		else
		{
			calculoEImpresionResultados();
		}
	}
}

void algoritmoResta(){
	sn = nsn;
	sv = nsv;
	c = 0;
	finalizo = 0;
	rnsn = 0;
	rnsv = 0;

	int corte = iteracionRestar();

	while(corte == 1){
		corte = iteracionRestar();
	}
}

int iteracionRestar(){
	if(sn == 0 && sv == 0)
	{
		return 0;
	}
	else
	{
		if(c < 24)
		{
			if(sv > 0)
			{
				if(sv >= varV)
				{
					if(c + varV <= 24)
					{
						sv = sv - varV;
						c = c + varV;
						rnsv = rnsv + varV;
					}
					else
					{
						int e;
						e = c + varV - 24;
						sv = sv - (varV - e);
						c = c + (varV - e);
						rnsv = rnsv + (varV - e);
					}
				}
				else
				{
					if(sv + c <= 24)
					{
						c = c + sv;
						rnsv = rnsv + sv;
						sv = 0;
					}
					else
					{
						int e;
						e = c + sv - 24;
						c = c + (sv - e);
						rnsv = rnsv + (sv - e);
						sv = e;
					}
				}
			}

			if (c < 24)
			{
				if(sn > 0)
				{
					if(sn >= varN)
					{
						if(c + varN <= 24)
						{
							sn = sn - varN;
							c = c + varN;
							rnsn = rnsn + varN;
						}
						else
						{
							int e;
							e = c + varN - 24;
							sn = sn - (varN - e);
							c = c + (varN - e);
							rnsn = rnsn + (varN - e);
						}
					}
					else
					{
						if(sn + c <= 24)
						{
							c = c + sn;
							rnsn = rnsn + sn;
							sn = 0;
						}
						else
						{
							int e;
							e = c + sn - 24;
							c = c + (sn - e);
							rnsn = rnsn + (sn - e);
							sn = e;
						}
					}
				}
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

/*
void algoritmoResta(){

	sn=0,sv=0,c=0,finalizo=0;
	restos.rnsn=0;
	restos.rnsn =0;

	while(finalizo !=1){
		finalizo = volverArriba();
	}

}

int restar(int cola, int distrib){
		int resto=0,e=0;

		if(cola >0){
				if(cola >= distrib){
					if(c+distrib<= 24){
						cola = cola-distrib;
						c = c + distrib;
						resto = resto + distrib;
					}else{
						e= (c+distrib)-24;
						cola=cola -(distrib-e);
						c= c + (distrib-e);
						resto = resto + (distrib-e);
					}
				}else{
					if(cola + c <= 24){
						c = c + cola;
						resto = resto + cola;
						cola=0;
					}else{
						e=(c+cola)-24;
						c=c+(cola - e);
						resto = resto + (cola-e);
					}
				}
			}
	return resto;
}

int volverArriba(){
	int finalizo=0;

	if(sn==0 && sv==0){
		finalizo = 1;
	}else{
		if(c <= 24){
			restos.rnsv = restar(sv,varV);
			restos.rnsn = restar(sn,varN);
			//volver arriba
		}else{finalizo=1;}
	}
	return finalizo;
}
*/

void calculoEImpresionResultados(){

	float pten = (float) (stsn-stlln) / (float) ntn;
	float ptev = (float) (stsv-stllv) / (float) ntv;
	printf("El PTEN es: %f \n", pten);
	printf("El PTEV es: %f \n", ptev);
	float porcentajeEsperaVip = (float) ptev / (float) pten;
	printf("Relacion tiempo de espera VIP/Normal: %f", porcentajeEsperaVip);

}


