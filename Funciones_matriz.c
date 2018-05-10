#include "Funciones_matriz.h"
#include <stdio.h>

status_t cargar_matriz( int (* ptr_matriz )[][CANT_MAX_COLUMS] ,
						size_t cant_filas ,
						size_t cant_colums )
{
	size_t posc_fila;
	size_t posc_columna;

	if( ptr_matriz == NULL ){
		return ST_PUNTERO_NULL;
	}
	for( posc_fila = 0 ; posc_fila < cant_filas ; posc_fila++){
		for( posc_columna = 0 ; posc_columna < cant_colums ; posc_columna++){
			printf("%s:[%lu][%lu]\n", MSJ_INGRESO_ELEMENTOS_MATRIZ ,
									posc_fila + 1 , posc_columna + 1 );
			if( scanf("%i", &((*ptr_matriz)[posc_fila][posc_columna])) != 1 ){
				return ST_ERROR_INGRESO_ELEMENTOS;
			}
			if( limpiar_buffer() == ST_BUFFER_SUCIO){
				return ST_ERROR_INGRESO_ELEMENTOS;
			}

		}
	}
	return ST_OK;
}

status_t determinante_matriz( int matriz[][CANT_MAX_FILAS] ,
							  int * determinante ,
							  size_t rango_matriz )
{
	int pos_fila;
	int pos_fila_inferior;
	int pos_fila_superior;

	if( matriz == NULL || determinante == NULL ){
		return ST_PUNTERO_NULL;
	}
	if(rango_matriz > 3 || !rango_matriz){
		return ST_RANGO_MATRIZ_INCALCULABLE;
	}
/*ya se valido que el rango sea el permitido para esta funcion (1,2,3)*/
	if(rango_matriz == 3){
		for(determinante[0]=0 , pos_fila = rango_matriz - 1 , pos_fila_superior = 0;
			pos_fila >= 0 ;
			pos_fila_superior++){
			for(pos_fila_inferior = pos_fila_superior + 1 ;
				pos_fila_inferior < rango_matriz  ;
				pos_fila-- , pos_fila_inferior++ ){
/*el determinante se calcula con los coeficientes de la primer columna (0)y */
/*tomando los subdeterminantes de las columnas 2 y 3*/
/*(o 1 y 2 , en C las columnas son 0, 1 y 2 )*/
					determinante[0] +=
									  matriz[pos_fila][0]*
									  (matriz[pos_fila_superior][1]
									  *(matriz[pos_fila_inferior][2])
									  - (matriz[pos_fila_superior][2])
									  *(matriz[pos_fila_inferior][1]));
					if( pos_fila%2){
						determinante[0] = (-1) * (determinante[0]);
					}
			}
		}
	return ST_OK;
	}
	else if(rango_matriz == 2){
		determinante[0] = matriz[0][0]*(matriz[1][1])
						  - matriz[1][0]*(matriz[0][1]);
		return ST_OK;
	}
	else{
		determinante[0] = matriz[0][0];
		return ST_OK;
	}
}

status_t calcular_traza_matriz( int matriz[][CANT_MAX_FILAS] ,
								int * ptr_traza , const size_t rango_matriz){
	size_t poscn_matriz;
	if( matriz == NULL || ptr_traza == NULL){
		return ST_PUNTERO_NULL;
	}
	if(!rango_matriz){
		return ST_RANGO_MATRIZ_INVALIDO;
	}
	for(*ptr_traza = 0 , poscn_matriz = 0 ; poscn_matriz < rango_matriz ;
		poscn_matriz++){
		*ptr_traza += matriz[poscn_matriz][poscn_matriz];
	}
	return ST_OK;
}

status_t limpiar_buffer(void)
{
	int caracter_no_leido_scanf , var_aux = 0;

	while( (caracter_no_leido_scanf = getchar()) != '\n'
		   && caracter_no_leido_scanf != EOF ){
		var_aux++;
	}
	if( !var_aux ){
		return ST_OK;
	}
	else
		return ST_BUFFER_SUCIO;
}
