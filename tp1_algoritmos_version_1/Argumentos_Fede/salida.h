#ifndef SALIDA_H
#define SALIDA_H

#include <stdio.h>
#include <stdlib.h>

#include "tipos.h"

#define MSJ_REGISTO_SALIDA "REGISTROS"
#define MSJ_ACUMULADOR_SALIDA "Acumulador"
#define MSJ_INDEX_SALIDA "Index"
#define MSJ_INSTRUCCION_SALIDA "Instrucion"
#define MSJ_OPCODE_SALIDA "Opcode"
#define MSJ_OPERANDO_SALIDA "Operando"
#define MSJ_MEMORIA_SALIDA "MEMORIA"

#define MSJ_ERROR_PREFIJO_SALIDA "ERROR_SALIDA"
#define MSJ_ERROR_TIPO_SALIDA_INCORRECTO "No se encontro el tipo de salida"
#define MSJ_ERROR_ABRIR_ARCHIVO_SALIDA "No se pudo abrir el archivo de salida"
#define MSJ_ERROR_CARGAR_ARCHIVO_SALIDA "No se pudo cargar al archivo de salida"
#define MSJ_ERROR_CERRAR_ARCHIVO_SALIDA "No se pudo cerrar el archivo de salida correctamente"
#define MSJ_ERROR_SALIDA "Ocurrio un error en la salida"

typedef enum{
	ST_ERROR_TIPO_SALIDA_INCORRECTO,
	ST_PUNTERO_SALIDA_NULO,
	ST_ERROR_ABRIR_ARCHIVO_SALIDA,
	ST_ERROR_CARGAR_ARCHIVO_SALIDA,
	ST_ERROR_CERRAR_ARCHIVO_SALIDA,
	ST_SALIDA_OK
}status_salida_t;

void imprimir_error_salida( status_salida_t estado_salida );
void salida_consola(int cant_memoria);
status_salida_t seleccionar_salida(struct mensajero * msj);
status_salida_t salida_archivo_texto(int cant_memoria , char * nombre_archivo);
status_salida_t salida_archivo_binario(int cant_memoria, char * nombre_archivo);

#endif

