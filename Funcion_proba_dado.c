
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MSJ_PRESENTACION_PROGRAMA "Se lanza un dado"

#define MSJ_ERROR_PREFIJO "Error"
#define MSJ_ERROR_PROGRAMA "Ocurrio un error en el programa mientras se ejecutaba"

#define DADO_PARTE_BLANCO "|     |"
#define DADO_PARTE_SIMBOLO_DERECHA "|    *|"
#define DADO_PARTE_SIMBOLO_MEDIO "|  *  |"
#define DADO_PARTE_SIMBOLO_IZQ "|*    |"
#define DADO_PARTE_SIMBOLO_DOBLE "|*   *|"

typedef enum{ SALIO_CARA_1 = 1,
			  SALIO_CARA_2 = 2,
			  SALIO_CARA_3 = 3,
			  SALIO_CARA_4 = 4,
			  SALIO_CARA_5 = 5,
			  SALIO_CARA_6 = 6} result_dado_t;

int main(void){

	result_dado_t result_dado;
	size_t num_aleatorio;

	srand( time(NULL) );

	puts(MSJ_PRESENTACION_PROGRAMA);

/*suma 1 para obtener valores de 1 a 6 y no trabajar con cero*/
/*un dado solo puede tener 6 resultados*/
	num_aleatorio =  ( rand() % 6 ) + 1 ;
/*asigna result_dado al valor de num_aleatorio que salio*/
	for( result_dado = SALIO_CARA_1 ; result_dado < num_aleatorio ; result_dado++)
		 {}

	switch( result_dado ){

		case SALIO_CARA_1:
			puts(DADO_PARTE_BLANCO);
			puts(DADO_PARTE_SIMBOLO_MEDIO);
			puts(DADO_PARTE_BLANCO);
			break;

		case SALIO_CARA_2:
			puts(DADO_PARTE_SIMBOLO_DERECHA);
			puts(DADO_PARTE_BLANCO);
			puts(DADO_PARTE_SIMBOLO_IZQ);
			break;

		case SALIO_CARA_3:
			puts(DADO_PARTE_SIMBOLO_IZQ);
			puts(DADO_PARTE_SIMBOLO_MEDIO);
			puts(DADO_PARTE_SIMBOLO_DERECHA);
			break;

		case SALIO_CARA_4:
			puts(DADO_PARTE_SIMBOLO_DOBLE);
			puts(DADO_PARTE_BLANCO);
			puts(DADO_PARTE_SIMBOLO_DOBLE);
			break;

		case SALIO_CARA_5:
			puts(DADO_PARTE_SIMBOLO_DOBLE);
			puts(DADO_PARTE_SIMBOLO_MEDIO);
			puts(DADO_PARTE_SIMBOLO_DOBLE);
			break;

		case SALIO_CARA_6:
			puts(DADO_PARTE_SIMBOLO_DOBLE);
			puts(DADO_PARTE_SIMBOLO_DOBLE);
			puts(DADO_PARTE_SIMBOLO_DOBLE);
			break;

		default:
			fprintf(stderr,"%s: %s\n" , MSJ_ERROR_PREFIJO , MSJ_ERROR_PROGRAMA);
	}

	return EXIT_SUCCESS;
}
