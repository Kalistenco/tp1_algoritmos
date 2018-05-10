
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CANTIDAD_EXPERIMENTOS 1000000
#define MAX_NUM_ALEATORIO 100

#define MSJ_CANT_EXPERIMENTOS_REALIZADOS "Cantidad de experimentos realizados"
#define MSJ_FREQ_RELATIVA_A "La probabilidad de 3 es"
#define MSJ_FREQ_RELATIVA_B "La probabilidad de 5 es"
#define MSJ_FREQ_RELATIVA_C "La probabilidad de 9 es"

int main(void){

	size_t freq_absoluta_A;
	size_t freq_absoluta_B;
	size_t freq_absoluta_C;
	size_t cant_experimentos;
	size_t num_aleatorio;
	float probabilidad_A = 0.10;
	float probabilidad_B = 0.55;

	srand( time(NULL) );

	printf("%s %i\n", MSJ_CANT_EXPERIMENTOS_REALIZADOS ,
					  MAX_CANTIDAD_EXPERIMENTOS);

	cant_experimentos = 0;
	for( freq_absoluta_A = 0 , freq_absoluta_B = 0 , freq_absoluta_C = 0 ;
		 cant_experimentos < MAX_CANTIDAD_EXPERIMENTOS ; cant_experimentos++){
/*suma 1 para obtener valores de 1 a 100 y no trabajar con cero*/
			if( ( num_aleatorio =  ( rand() % MAX_NUM_ALEATORIO ) + 1  ) <=
			    probabilidad_A * MAX_NUM_ALEATORIO  ){
				freq_absoluta_A++;
			}
/*recordar que el intervalo se divide en 0---P(A)---P(A)+P(B)---1 donde*/
/*el modulo del intervalo (0,P(A)) es la probabilidad de A*/
/*el modulo del intervalo (P(A),P(A)+P(B)) es la probabilidad de B*/
/*..... C*/
			else if( num_aleatorio <= ( probabilidad_B * MAX_NUM_ALEATORIO ) +
					 ( probabilidad_A * MAX_NUM_ALEATORIO ) ){
				freq_absoluta_B++;
			}
			else{
				freq_absoluta_C++;
			}
	}

/*se castea a float por que es una division de enteros y se rendondea a 1 decimal*/
	printf("%s: %.2f\n%s: %.2f\n%s: %.2f\n", MSJ_FREQ_RELATIVA_A,
										 (float)freq_absoluta_A/cant_experimentos,
										 MSJ_FREQ_RELATIVA_B,
										 (float)freq_absoluta_B/cant_experimentos,
										 MSJ_FREQ_RELATIVA_C,
										 (float)freq_absoluta_C/cant_experimentos );

	return EXIT_SUCCESS;
}
