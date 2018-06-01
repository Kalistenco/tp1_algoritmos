#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argumentos.h"
#include "operacions.h"
#include "salida.h"
#include "entrada.h"

void imprimir_mensajero(struct  mensajero * y);

int main(int argc , char * argv[]){
    status_arg_t error_argumento;
    status_op_t error_operacion;
    struct mensajero msj;
	status_t_entrada estado;

    inicializar_mensajero(&msj);

    error_argumento = validar_argumentos(argc , argv ,&msj);
    if(argumentos_error_imprimir(error_argumento) == FALSO){
        return EXIT_FAILURE;
    }

    estado = procesar_entrada( &msj );

	if( estado != ST_OK ){
		imprimir_error_entrada(estado);
		return EXIT_SUCCESS;
	}
	puts("Hasta aca todo bien");


    cabeza.index = 0;
    cabeza.acumulador = 0;
/*
    Probe al archivo resta
    cabeza.lista_instrucciones[0] = 1009;
    cabeza.lista_instrucciones[1] = 1010;
    cabeza.lista_instrucciones[2] = 2009;
    cabeza.lista_instrucciones[3] = 3110;
    cabeza.lista_instrucciones[4] = 4107;
    cabeza.lista_instrucciones[5] = 1109;
    cabeza.lista_instrucciones[6] = 4008;
    cabeza.lista_instrucciones[7] = 1110;
    cabeza.lista_instrucciones[8] = 4500;
    cabeza.lista_instrucciones[9] = 0000;
    cabeza.lista_instrucciones[10] = 0000;
    cabeza.lista_instrucciones[11] = 0000;
*/
    error_operacion = ejecutar_instrucciones(msj.cant_memoria);
    if(errores_instrucciones(error_operacion) == FALSO){
        return EXIT_FAILURE;
    }

    if(seleccionar_salida(&msj) == FALSO){
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
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
