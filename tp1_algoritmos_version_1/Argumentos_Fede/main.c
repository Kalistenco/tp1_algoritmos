#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argumentos.h"
#include "operacions.h"
#include "salida.h"
#include "entrada.h"

/*void imprimir_mensajero(struct  mensajero * y);*/

int main(int argc , char * argv[]){

    status_arg_t estado_arg;
    status_op_t estado_op;
    status_salida_t estado_salida;
	status_t_entrada estado_entrada;
	struct mensajero msj;

/****se inicializa la estructura con los valores por omision****/
    inicializar_mensajero(&msj);

/**** Se procesan los argumentos ****/
    estado_arg = validar_argumentos(argc , argv ,&msj);
	if( estado_arg != OK ){
		argumentos_error_imprimir( estado_arg );
		return EXIT_FAILURE;
	}

/**** Se Cargan las palabras a memoria ****/
    estado_entrada = procesar_entrada( &msj );
	if( estado_entrada != ST_OK ){
/*si hubo un error la funcion elimina el vector , no hace falta un free*/
		imprimir_error_entrada(estado_entrada);
		return EXIT_SUCCESS;
	}

/**** Se inicia el programa e inicializa a cero las variables ****/
/*recordar qeu si todo sale bien , existe el vector , entonces*/
/* a partir de aca se debe liberar la memoria(cabeza.lista_instrucciones)antes de terminar el progrma*/
	puts( MSJ_CARGA_COMPLETA );
	puts( MSJ_COMIENZO_EJECUCION );

/*se inicializa las variables de cabeza*/
    cabeza.index = 0;
    cabeza.acumulador = 0;

/**** Se ejecutan las instrucciones ****/
    estado_op = ejecutar_instrucciones(msj.cant_memoria);
    if( estado_op != OK_OP ){
		errores_instrucciones(estado_op);
		free( cabeza.lista_instrucciones );
        return EXIT_FAILURE;
    }

/**** Salida del programa ****/
	estado_salida = seleccionar_salida(&msj);
    if( estado_salida != ST_SALIDA_OK ){
		imprimir_error_salida( estado_salida );
		free( cabeza.lista_instrucciones );
        return EXIT_FAILURE;
    }

/**** Se libera la memoria pedida ****/
	free( cabeza.lista_instrucciones );
    return EXIT_SUCCESS;
}




/*
int main(int argc , char * argv[]){

    status_arg_t error_argumento;
    status_op_t error_operacion;
    status_salida_t estado_salida
	status_t_entrada estado_entrada;
	struct mensajero msj;
    inicializar_mensajero(&msj);
    error_argumento = validar_argumentos(argc , argv ,&msj);
    if(argumentos_error_imprimir(error_argumento) == FALSO){
        return EXIT_FAILURE;
    }
    estado = procesar_entrada( &msj );
	if( estado != ST_OK ){
si hubo un error la funcion elimina el vector , no hace falta un free
		imprimir_error_entrada(estado);
		free( cabeza.lista_instrucciones );
		return EXIT_SUCCESS;
	}
recordar qeu si todo sale bien , existe el vector , entonces
 a partir de aca se debe liberar la memoria(cabeza.lista_instrucciones)antes de terminar el progrma
	puts( MSJ_CARGA_COMPLETA );
	puts( MSJ_COMIENZO_EJECUCION );
se inicializa las variables de cabeza
    cabeza.index = 0;
    cabeza.acumulador = 0;

    error_operacion = ejecutar_instrucciones(msj.cant_memoria);
    if(errores_instrucciones(error_operacion) == FALSO){
		free( cabeza.lista_instrucciones );
        return EXIT_FAILURE;
    }

    if(seleccionar_salida(&msj) == FALSO){
		free( cabeza.lista_instrucciones );
        return EXIT_FAILURE;
    }
	free( cabeza.lista_instrucciones );
    return EXIT_SUCCESS;
}

*/

void imprimir_mensajero(struct mensajero * y){
    printf("\n ------------------- Mensajero ------------\n");
    printf("Opcion ayuda : %i\n", y->opcion_ayuda);
    printf("\nEntrada Archivo : %i\n" , y->entrada_archivo);
    printf("Entrada archivo nombre : %s\n",y->entrada_archivo_nombre);
    printf("Entrada Tipo archivo : %i",y->entrada_tipo);
    printf("\nSalida archivo : %i\n",y->salida_archivo);
    printf("Salida archivo nombre : %s \n",y->salida_archivo_nombre);
    printf("Salida Tipo archivo : %i\n",y->salida_tipo);
    printf("\nCantidad de memoria %lu\n",(y->cant_memoria));
    printf("\n----------------------------\n");
}
