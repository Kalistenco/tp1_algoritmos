#ifndef TIPOS_H
#define TIPOS_H


#include <stdio.h>
#include <stdlib.h>

typedef struct palabras{
    int completo;
    size_t codigo;
    size_t direccion; 
}palabras_t;

typedef enum BOOLEAN{
    FALSO,
    VERDADERO
}bool_t;


struct procesador{
    int acumulador;
    size_t index;
    palabras_t ** lista_instrucciones;
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

#endif