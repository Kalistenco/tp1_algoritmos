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



extern struct procesador cabeza;

#endif