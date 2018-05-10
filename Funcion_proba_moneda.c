
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MSJ_EXPERIMENTO_REALIZADO "Se lanza una moneda"
#define MSJ_RESULTADO_CARA "Salio Cara"
#define MSJ_RESULTADO_CECA "Salio Ceca"

typedef enum{ SALIO_CARA = 1 , SALIO_CECA = 2} resultado_moneda_t ;

int main(void){

	resultado_moneda_t resultado_moneda;

	srand( time(NULL) );

	puts(MSJ_EXPERIMENTO_REALIZADO);

/*los unicos posibles resultados del numero aleatorio son SALIO_CARA y SALIO_CECA*/
/*son eventos equiprobables*/
/*se suma uno para no trabajar con el cero*/
	if( ( rand() % 2 ) + 1 == SALIO_CARA ){
		  resultado_moneda = SALIO_CARA;
	}
	else{
		resultado_moneda = SALIO_CECA;
	}

	switch( resultado_moneda ){
		case SALIO_CARA:
			puts(MSJ_RESULTADO_CARA);
			break;
		case SALIO_CECA:
			puts(MSJ_RESULTADO_CECA);
	}


	return EXIT_SUCCESS;
}
