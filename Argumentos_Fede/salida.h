#ifndef SALIDA_H
#define SALIDA_H

#include <stdio.h>
#include <stdlib.h>

#include "tipos.h"

/*Mensajes de error */
#define MSJ_ERROR_SALIDA "Error al intentar crear/acceder al archivo"

/*Mensajes de salida */
#define MSJ_REGISTO_SALIDA "REGISTRO : \n"
#define MSJ_ACUMULADOR_SALIDA "Acumulador : "
#define MSJ_INDEX_SALIDA "Index : "
#define MSJ_INSTRUCCION_SALIDA "Instrucion : "
#define MSJ_OPCODE_SALIDA "Opcode : "
#define MSJ_OPERANDO_SALIDA "Operando : "
#define MSJ_MEMORIA_SALIDA "MEMORIA:"

/*Funcion que dependiendo del mensajero selecciona la forma de salida */
bool_t seleccionar_salida(struct mensajero * msj);

/*Funcion de salida por consola */
void salida_consola(int cant_memoria);
/*Funcion de salida por archivo de texto */
bool_t salida_archivo_texto(int cant_memoria , char * nombre_archivo);
/*Funcion de salida por archivo binario */
bool_t salida_archivo_binario(int cant_memoria, char * nombre_archivo);


#endif