
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CANTIDAD_EXPERIMENTOS 10000000
#define MAX_NUM_ALEATORIO 10

#define MSJ_CANT_EXPERIMENTOS_REALIZADOS "Cantidad de experimentos realizados"
#define MSJ_FREQ_RELATIVA_A "La probabilidad de 0 es"
#define MSJ_FREQ_RELATIVA_B "La probabilidad de 1 es"

int main(void){

	size_t freq_absoluta_A;
	size_t freq_absoluta_B;
	size_t cant_experimentos;
	float probabilidad_A = 0.2;

	srand( time(NULL) );

	printf("%s %i\n",MSJ_CANT_EXPERIMENTOS_REALIZADOS ,
					 MAX_CANTIDAD_EXPERIMENTOS);

	for( cant_experimentos = 0 , freq_absoluta_A = 0 , freq_absoluta_B = 0 ;
		 cant_experimentos < MAX_CANTIDAD_EXPERIMENTOS ; cant_experimentos++){
/*suma 1 para obtener valores de 1 a 10 y no trabajar con cero*/
			if( (rand() % MAX_NUM_ALEATORIO ) + 1 <=
			    probabilidad_A * MAX_NUM_ALEATORIO){
				freq_absoluta_A++;
			}
			else{
				freq_absoluta_B++;
			}
	}

/*se castea a float por que es una division de enteros y se rendondea a 1 decimal*/
	printf("%s: %.1f\n%s: %.1f\n", MSJ_FREQ_RELATIVA_A,
								   (float)freq_absoluta_A/cant_experimentos,
								   MSJ_FREQ_RELATIVA_B,
								   (float)freq_absoluta_B/cant_experimentos);

	return EXIT_SUCCESS;
}
