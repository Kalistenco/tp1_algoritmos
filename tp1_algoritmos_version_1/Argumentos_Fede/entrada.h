#ifndef ENTRADA__H
#define ENTRADA__H 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"

#define MSJ_ERROR_PREFIJO_ENTRADA "ERROR_ENTRADA"
#define MSJ_ERROR_LECTURA_ARCHIVO "No se puedo leer el archivo"
#define MSJ_ERROR_PALABRA_INCORRECTA "La palabra es incorrecta"
#define MSJ_ERROR_PALABRA_INCOMPLETA "La palabra esta incompleta"
#define MSJ_ERROR_PUNTERO_NULO "El puntero es nulo"
#define MSJ_ERROR_ABRIR_ARCHIVO "No se pudo abrir el archivo"
#define MSJ_ERROR_NO_MEMORIA "No hay mas memoria"
#define MSJ_ERROR_CERRAR_ARCHIVO "No se pudo cerrar el archivo correctamente"
#define MSJ_ERROR_LEER_CONSOLA "No se pudo leer desde consola"
#define MSJ_ERROR_PALABRA_FUERA_DE_RANGO "La palabra esta fuera de rango"
#define MSJ_ERROR_VECTOR_VACIO "No ingreso nada , el vector esta vacio"
#define MSJ_ERROR_ENTRADA "Se produjo un error en la entrada"

#define FORMATO_PREFIJO_INGRESO "%2lu  :?"

#define MAX_CANT_INGRESO 126
#define MAX_LARGO_PALABRA 5
#define MAX_LARGO_PALABRA_FIN 6
#define PALABRA_FIN_INGRESO -99999
#define MAX_PALABRA_ACEPTADA 9999
#define MIN_PALABRA_ACEPTADA 0
#define INICIO_COMENTARIO ';'
#define CARACTER_A_OMITIR ' '
#define INICIO_PALABRA '+'
#define INICIO_FIN_INGRESO '-'
#define CARACTER_BARRA_N '\n'

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
	ST_ERROR_LEER_CONSOLA,
	ST_FIN_INGRESO,
	ST_ERROR_PALABRA_FUERA_DE_RANGO,
	ST_ERROR_VECTOR_VACIO
}status_t_entrada;

/*archivo_entrada es el archivo de donde se leen los datos*/
/*pvtr_palabras_convertidas es la direccion del vector donde se guardo las palabras*/
void imprimir_error_entrada( status_t_entrada estado_entrada );
status_t_entrada convertir_palabra_str_int(char * cadena_ingreso,int * palabra_convertida);
status_t_entrada procesar_entrada( struct mensajero * msj );
