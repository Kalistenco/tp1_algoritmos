#ifndef SALIDA_H
#define SALIDA_H

#include <stdio.h>
#include <stdlib.h>

#include "tipos.h"

#define MSJ_ERROR_SALIDA "Error al intentar crear/acceder al archivo"

#define MSJ_REGISTO_SALIDA "REGISTRO : \n"
#define MSJ_ACUMULADOR_SALIDA "Acumulador : "
#define MSJ_INDEX_SALIDA "Index : "
#define MSJ_INSTRUCCION_SALIDA "Instrucion : "
#define MSJ_OPCODE_SALIDA "Opcode : "
#define MSJ_OPERANDO_SALIDA "Operando : "
#define MSJ_MEMORIA_SALIDA "MEMORIA:"

bool_t seleccionar_salida(struct mensajero * msj);

void salida_consola(int cant_memoria);
bool_t salida_archivo_texto(int cant_memoria , char * nombre_archivo);
bool_t salida_archivo_binario(int cant_memoria, char * nombre_archivo);


#endif