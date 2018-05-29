#ifndef TIPOS_H
#define TIPOS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Mensaje de error */
#define MSJ_ERROR "Ha ocurrido un error  "

/*Maximo del largo del nombre del archivo */
#define MAX_LARGO_ARCHIVO 50

/*Cantidad de tipos en diccionario */
#define OPCIONES_TIPO_ARCHIVO 2

/*Diccionario de tipos de archivos */
/*OPCIONES_TIPO_ARCHIVO = Cantidad de opciones, si se modifica biblioteca, modificar cantidad */
static const char * const archivos_tipo_lista[] = {"txt" , "bin"};
typedef enum archivos_index {
    NO_ESPECIFICADO = -1,
    TXT = 0,
    BIN = 1
}archivo_t;


typedef enum BOOLEAN{
    FALSO,
    VERDADERO
}bool_t;


struct procesador{
    int acumulador;
    size_t index;
    int * lista_instrucciones;
};


/*Estructura de mensajero para conectar las validaciones con la ejecucion de argumentos */
struct mensajero{
    bool_t opcion_ayuda;
    bool_t entrada_archivo;
    char entrada_archivo_nombre[MAX_LARGO_ARCHIVO];
    archivo_t entrada_tipo;
    bool_t salida_archivo;
    char salida_archivo_nombre[MAX_LARGO_ARCHIVO];
    archivo_t salida_tipo;
    size_t cant_memoria;
};



extern struct procesador cabeza;
struct procesador cabeza;

#endif