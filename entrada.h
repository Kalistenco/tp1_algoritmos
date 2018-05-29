#ifndef ENTRADA__H
#define ENTRADA__H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"

#define MAX_CANT_INGRESO 50
#define MAX_LARGO_PALABRA 4

#endif

typedef enum{
	ST_OK,
	ST_SALIR_CICLO,
	ST_EOF_Y_CADENA_VACIA,
	ST_ERROR_LECTURA_ARCHIVO,
	ST_ERROR_PALABRA_INCORRECTA,
	ST_ERROR_PALABRA_INCOMPLETA,
	ST_VECTOR_DE_ESPACIOS,
	ST_ERROR_PALABRA_NO_CONVERTIDA,
	ST_ERROR_PALABRA_NO_NUMERICA,
	ST_PUNTERO_NULO,
	ST_ERROR_ABRIR_ARCHIVO,
	ST_ERROR_NO_MEMORIA,
	ST_ERROR_CERRAR_ARCHIVO,
	ST_ERROR_VECTOR_INCOMPLETO,
	ST_ERROR_LEER_CONSOLA
}status_t;

/*archivo_entrada es el archivo de donde se leen los datos*/
/*pvtr_palabras_convertidas es la direccion del vector donde se guardo las palabras*/
status_t convertir_palabra_str_int(char * cadena_ingreso,int * palabra_convertida);
status_t procesar_entrada_archivo( size_t  cant_palabras ,
								   char * archivo_entrada ,
								   int ** pvtr_palabras_convertidas ,
								   bool_t entrada_archivo ,
								   archivo_t entrada_tipo );
