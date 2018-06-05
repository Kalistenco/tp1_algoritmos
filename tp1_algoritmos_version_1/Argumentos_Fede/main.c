#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argumentos.h"
#include "operacions.h"
#include "salida.h"
#include "entrada.h"


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
