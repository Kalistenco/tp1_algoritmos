#ifndef OPREACIONES_H
#define OPREACIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tipos.h"


#define MSJ_MEMORIA_INGRESADA_CERO "La memoria no puede ser cero"
/*Mensaje de Inicio/FIn */
#define MSJ_INICIO "*********INICIO DE EJECUCION DEL SIMPLETRON*********"
#define MSJ_FINAL "*********FINAL DE EJECUCION DEL SIMPLETRON*********"

/*Mensajes de entrada/salida*/
#define MSJ_OPERACION_ESCRIBIR "Ingrese una palabra : "
#define MSJ_OPERACION_LEER "Contenido de la posicion "


/*Mensajes de error */
#define MSJ_ERROR_OP_HALT "No se ha encontrado el final del programa\n"
#define MSJ_ERROR_OP_CODIGO_NO_CONOCIDO "No se ha introducido ninguna operacion valida en la memoria : "
#define MSJ_ERROR_OP_POSICION_FUERA_DE_RANGO "Se apunta a una memoria invalida en la instruccion de posicion : "
#define MSJ_ERROR_OP_VALOR_INGRESADO_INV "se ha ingresado un valor invalido\n"
#define MSJ_ERROR_PUNTERO_NULO "El puntero es nulo"
#define MSJ_NO_SE_PUDO_LEER_VALOR "No se pudo leer el valor ingresado"

/*Operacions y su codigo */
#define OPERACION_LEER 10
#define OPERACION_ESCRIBIR 11
#define OPERACION_CARGAR 20
#define OPERACION_GUARDAR 21
#define OPERACION_PCARGAR 22
#define OPERACION_PGUARDAR 23
#define OPERACION_SUMAR 30
#define OPERACION_RESTAR 31
#define OPERACION_DIVIDIR 32
#define OPERACION_MULTIPLICAR 33
#define OPERACION_JMP 40
#define OPERACION_JMPNEG 41
#define OPERACION_JMPZERO 42
#define OPERACION_JNZ 43
#define OPERACION_DJNZ 44
#define OPERACION_HALT 45

#define MAX_CANT_INGRESO_STDIN 20

/*Posibles errores en la lectura de palabras */
typedef enum{
    NO_HALT,
    NINGUN_CODIGO_CONOCIDO,
    POSICION_FUERA_DE_RANGO,
    VALOR_INGRESADO_INV,
    OK_OP,
/*	PUNTERO_NULO,*/
    NO_SE_PUDO_LEER_VALOR,
    CANT_MEMORIA_CERO
}status_op_t;

/*Verifica si se va de rango la memoria */
int verificar_posicion_memoria();

/*Funcion que ejectua las palabras que hay en la lista */
status_op_t ejecutar_instrucciones(int cantidad_memoria);

/*Funcion que imprime mensaje de error , devuelve FALSO si no hubo errores */
bool_t errores_instrucciones(status_op_t error);

/*Operaciones de entrada/salida */
status_op_t leer(int posicion_asignada);
void escribir(int posicion_asignada);

/*Operaciones de movimiento*/
void cargar(int posicion_asignada);
void guardar(int posicion_asignada);
status_op_t pcargar(int posicion_asignada);
status_op_t pguardar(int posicion_asignada);

/*Operaciones aritmeticas */
void suma(int posicion_asignada);
void resta(int posicion_asignada);
void division(int posicion_asignada);
void multiplicar(int posicion_asignada);

/*Operaciones de control */
void jmp(int posicion_asignada);
void jmpneg(int posicion_asignada);
void jmpzero(int posicion_asignada);
void jnz(int posicion_asignada);
void djnz(int posicion_asignada);

void prueba(int codigo, int posicion_asignada);

#endif
