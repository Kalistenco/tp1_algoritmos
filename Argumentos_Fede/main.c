#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argumentos.h"

void imprimir_mensajero(struct  mensajero * y);

int main(int argc , char * argv[]){
    status_arg_t n;
    struct mensajero x;

    inicializar_mensajero(&x);

    imprimir_mensajero(&x);

    n = validar_argumentos(argc , argv ,&x);
    argumentos_error_imprimir(n);

    imprimir_mensajero(&x);

    return 0;
}

void imprimir_mensajero(struct mensajero * y){
    printf("\n ------------------- Mensajero ------------\n");
    printf("Opcion ayuda : %i\n", y->opcion_ayuda);
    printf("\nEntrada Archivo : %i\n" , y->entrada_archivo);
    printf("Entrada archivo nombre : %s\n",y->entrada_archivo_nombre);
    printf("Entrada Tipo archivo : %i",y->entrada_tipo);
    printf("\nSalida archivo : %i\n",y->salida_archivo);
    printf("Salida archivo nombre : %s \n",y->salida_archivo_nombre);
    printf("Salida Tipo archivo : %i\n",y->salida_tipo);
    printf("\nCantidad de memoria %i\n",(int) (y->cant_memoria));
    printf("\n----------------------------\n");
}