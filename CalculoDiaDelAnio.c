#include <stdio.h>
#include <stdlib.h>

#define TOTAL_DIAS_ANIO 365      /*puede cambiarse a 366 año bisiesto*/

#define MSJ_INGRESO_DIA "Ingrese el dia (numero) del año para saber que dia es"
#define MSJ_DIA_DOMINGO "Es domingo"
#define MSJ_DIA_LUNES "Es lunes"
#define MSJ_DIA_MARTES "Es martes"
#define MSJ_DIA_MIERCOLES "Es miercoles"
#define MSJ_DIA_JUEVES "Es jueves"
#define MSJ_DIA_VIERNES " Es viernes"
#define MSJ_DIA_SABADO "Es sabado"

#define MSJ_ERROR_PREFIJO "ERROR"
#define MSJ_ERROR_INGRESO_INVALIDO "Debe ingresar un dia del año ( 1,2...366)"
#define MSJ_ERROR_CAMBIO_INESPERADO "Se produjo un error mientras se ejecutaba el programa"
#define MSJ_ERROR_INGRESO_CERO_NEGATIVO "Ingreso un numero negativo o cero"
#define MSJ_ERROR_INGRESO_CANTIDAD_DIAS "Los dias comienzan en 1 y acaban en 365 o 366"

enum { DOMINGO = 1 , LUNES = 2 , MARTES = 3, MIERCOLES = 4, JUEVES  = 5,
			VIERNES = 6 , SABADO = 7 } ;          /* se necesita un orden creciente de saltos de a 1 */
                                                                              /*que comiencen en DOMINGO*/
int main (void)
{

	short unsigned int primer_dia_anio;

	short int dia_ingresado;
	int var_aux;

	primer_dia_anio = DOMINGO;                /* todas las opciones son las de enum*/

	puts(MSJ_INGRESO_DIA);
	if ( (scanf("%hi",&dia_ingresado) ) != 1 ) {          /* si scanf lee bien la entrada , debe devolver 1*/
		fprintf(stderr,"%s: %s\n",MSJ_ERROR_PREFIJO,MSJ_ERROR_INGRESO_INVALIDO);
		return EXIT_FAILURE;
	}
	while( ( var_aux = getchar() ) != '\n' && var_aux != EOF){
	}                                                                                     /*limpia el buffer*/

	if( dia_ingresado <= 0 ){
		fprintf(stderr,"%s: %s\n",MSJ_ERROR_PREFIJO,MSJ_ERROR_INGRESO_CERO_NEGATIVO);
		return EXIT_FAILURE;
	}

 	if( dia_ingresado > TOTAL_DIAS_ANIO ){
		fprintf(stderr,"%s: %s\n",MSJ_ERROR_PREFIJO,MSJ_ERROR_INGRESO_CANTIDAD_DIAS);
		return EXIT_FAILURE;
	}


	if( !( dia_ingresado =(dia_ingresado % 7) ) ){         			 /* dia_ingresado pasa a ser la posicion del dia */
		dia_ingresado  += 7;                         					 /* tomando el orden definido en enum*/
	}                                                                                   /* suma 7 para considerar la posicion 0 como 7*/

	if( (dia_ingresado = (dia_ingresado + primer_dia_anio - 1 ) )  > 7 ){    /*para otro pri.._dia_año*/
		dia_ingresado -=7;                                                 /*dia_ingresado pasa a ser la cantidad de saltos */
	}                                                                                  /* que se hacen a partir del primer_dia_año*/
                                                                                        /* si supera 7 vuelve a comenzar desde el */
	switch(dia_ingresado)                                               /*primer dia de la semana considerado en enum*/
	{

		case DOMINGO :
			puts(MSJ_DIA_DOMINGO) ;
			break;

		case LUNES :
			 puts(MSJ_DIA_LUNES)  ;
			break;

		case MARTES :
			puts(MSJ_DIA_MARTES) ;
			break;

		case MIERCOLES :
			puts(MSJ_DIA_MIERCOLES) ;
			break;

		case JUEVES :
			puts(MSJ_DIA_JUEVES) ;
			break;

		case VIERNES :
			puts(MSJ_DIA_VIERNES) ;
			break;

		case SABADO :
			puts(MSJ_DIA_SABADO) ;
			break;

	    default :
			printf("%s: %s\n",MSJ_ERROR_PREFIJO,MSJ_ERROR_CAMBIO_INESPERADO);
	}

	return EXIT_SUCCESS;

}


