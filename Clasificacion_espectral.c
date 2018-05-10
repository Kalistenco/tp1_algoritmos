#include <stdio.h>
#include <stdlib.h>
#include "Clasificacion_espectral.h"

int main(void)
{
	estado_t estado;
/*Se inicializa con los valores minimo y maximo de las clases en enum*/
/*Pensado para el caso de agregar mas clases sin tener que cambiar mucho el codigo*/
/*o hacer los cambio en la parte de declaracion de variables*/
	espectral_t min_clase = CLASE_M;
	espectral_t max_clase = CLASE_O ;
    int temperatura_ingresada;
    int vtr_temp_limite_max_clases[] = { MIN_TEMP_CLASES,
									     MAX_TEMP_CLASE_M,
									     MAX_TEMP_CLASE_K,
									     MAX_TEMP_CLASE_G,
									     MAX_TEMP_CLASE_F,
									     MAX_TEMP_CLASE_A,
									     MAX_TEMP_CLASE_B,
									     MAX_TEMP_CLASE_O };


    puts(MSJ_INGRESO_TEMP);
	if( scanf("%d", &temperatura_ingresada) != 1 ){
		fprintf(stderr,"%s: %s\n",MSJ_ERROR_PREFIJO,MSJ_ERROR_INGRESO_TEMP);
		return EXIT_FAILURE;
	}
	if( limpiar_buffer() == ST_BUFFER_SUCIO ){
		fprintf(stderr,"%s: %s\n",MSJ_ERROR_PREFIJO,MSJ_ERROR_INGRESO_TEMP);
		return EXIT_FAILURE;
	}

	if( temperatura_ingresada < MIN_TEMP_CLASES ||
	    temperatura_ingresada > vtr_temp_limite_max_clases[max_clase ] ){
			fprintf(stderr,"%s\n",MSJ_CLASE_NO_DEFINIDA);
			return EXIT_SUCCESS;
	    }
	if( temperatura_ingresada < 0 ){
		fprintf(stderr,"%s: %s\n",MSJ_ERROR_PREFIJO,MSJ_ERROR_TEMP_NEGATIVA);
		return EXIT_FAILURE;
	}

	for( estado = ST_OK ; estado != ST_SALIR ; min_clase++ ){
		if( temperatura_ingresada <= vtr_temp_limite_max_clases[min_clase]){
            estado = ST_SALIR;
		}
	}

	switch(min_clase - 1){
		case CLASE_M:
			printf("%s %s\n",MSJ_IMPRIMIR_COLOR_CLASE,COLOR_CLASE_M);
			break;
		case CLASE_K:
			printf("%s %s\n",MSJ_IMPRIMIR_COLOR_CLASE,COLOR_CLASE_K);
			break;
		case CLASE_G:
			printf("%s %s\n",MSJ_IMPRIMIR_COLOR_CLASE,COLOR_CLASE_G);
			break;
		case CLASE_F:
			printf("%s %s\n",MSJ_IMPRIMIR_COLOR_CLASE,COLOR_CLASE_F);
			break;
		case CLASE_B:
			printf("%s %s\n",MSJ_IMPRIMIR_COLOR_CLASE,COLOR_CLASE_B);
			break;
		case CLASE_A:
			printf("%s %s\n",MSJ_IMPRIMIR_COLOR_CLASE,COLOR_CLASE_A);
			break;
		case CLASE_O:
			printf("%s %s\n",MSJ_IMPRIMIR_COLOR_CLASE,COLOR_CLASE_O);
			break;
		default:
			puts(MSJ_CLASE_NO_DEFINIDA);
	}

	return EXIT_SUCCESS;
}


estado_t limpiar_buffer(void)
{
	int caracter_no_leido_scanf , var_aux = 0;

	while( (caracter_no_leido_scanf = getchar()) != '\n'
		   && caracter_no_leido_scanf != EOF ){
		var_aux++;
	}

	if( var_aux == 0){
		return ST_OK;
	}
	else
		return ST_BUFFER_SUCIO;
}
