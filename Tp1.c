#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argumentos.h"

int main( int argc , char * argv[] ){

	argumentos_t argumento;
	argumentos_t argumento_aux;
	diccionario_t diccionario;
	frmt_if_of_t frmt_if_of;
	parametro_argumentos_t parametro_argumentos;
	long Na;
	status_t estado;
	size_t var_conteo = 0;

	char * vtr_arg[6] = {"-h","-m","-i","-if","-o","-of"};
	char * vtr_param_if_of[2] = {"bin", "txt"};
/* esto va en otra funcion cargar valores por omision*/
	diccionario.vtr_argumentos[0] = vtr_arg[0];
	diccionario.vtr_parametro_if_of[0] = vtr_param_if_of[0];
	diccionario.vtr_argumentos[1] = vtr_arg[1];
	diccionario.vtr_parametro_if_of[1] = vtr_param_if_of[1];
	diccionario.vtr_argumentos[2] = vtr_arg[2];
	diccionario.vtr_argumentos[3] = vtr_arg[3];
	diccionario.vtr_argumentos[4] = vtr_arg[4];
	diccionario.vtr_argumentos[5] = vtr_arg[5];


	parametro_argumentos.imprimir_ayuda = FALSO;
	parametro_argumentos.N= 50 ;
/*de donde lee y donde imprime*/
	parametro_argumentos.frmt_lectura = STDIO;
	parametro_argumentos.frmt_volcado = STDIO;
/*el formato en que lee y el formato en que entrega la informacion*/
	parametro_argumentos.frmt_entrada = FRMT_INCORRECTO;
	parametro_argumentos.frmt_salida = FRMT_INCORRECTO;

/*se inicializa estado a ST_OK , es para cuando no entre al ciclo (./programa) */
	estado = ST_OK;
	while( var_conteo < argc - 1 ){
/*el programa empieza a trabakar con argv[1]*/
/*recordar que argv[0] es ./programa*/
		var_conteo++;
/*valida que argv[1] sea un argumento valido*/
		estado = validar_argumento( argv[var_conteo] , &argumento , &diccionario);
		if( estado != ST_OK){
			break;
		}
/*si el argumento fuera -h imprime la ayuda y sale no tiene que hacer nada mas*/
		if( argumento == ARG_H ){
			parametro_argumentos.imprimir_ayuda = VERDADERO;
			break;
		}
		var_conteo++;
/*si lo que lee es lo ultimo del argv (NULL) es por que ingreso un argumento*/
/*sin parametro*/
		if( var_conteo == argc ){
			estado = ST_ERROR_ARG_SIN_PARAMETRO;
			break;
		}
/*hasta aca se que argv[1] es un argumento valido y no es -h*/
/*entonces el siguiente no tiene que ser un argumento */
/*seria el ejemplo -if -o es un error , si se pone -if se tiene que agregar*/
/*un parametro de -if (bin , txt)*/
		estado = validar_argumento( argv[var_conteo] , &argumento_aux , &diccionario);
		if( estado != ST_ERROR_ARG_INVALIDO ){
			if( estado == ST_ERROR_PUNTERO_NULO ){
				break;
			}
			else{
/*el unico caso que queda es ST_OK que significa que es un argumento*/
				estado = ST_ERROR_ARG_ARG;
				break;
			}
		}
		if( argumento == ARG_IF || argumento == ARG_OF ){
			estado = validar_frmt_if_of( argv[var_conteo] , &frmt_if_of , &diccionario);
			if( estado != ST_OK ){
				break;
			}
			estado = cargar_frmt_if_of( frmt_if_of , &parametro_argumentos , argumento);
			if( estado != ST_OK ){
				break;
			}
		}
		else if( argumento == ARG_I || argumento == ARG_O ){
/*si aparecen estos argumentos , solo puede ser de la forma */
/*-i archivo , -o archivo , asi que si aparece se carga */
/*creo que no hay forma de validar que el archivo sea correcto*/
			estado = cargar_parametro_i_o( &parametro_argumentos , argumento ,
										   argv[var_conteo] );
			if( estado != ST_OK){
				break;
			}
		}

		else if( argumento == ARG_M ){
			estado = validar_cant_palabras( argv[var_conteo] , &Na );
			if( estado != ST_OK ){
				break;
			}
/*en este punto se que el parametro de -m es correcto entonces se carga */
			parametro_argumentos.N = Na ;
		}
		else{
			estado = ST_ERROR_ARG_INVALIDO;
			break;
		}
	}
/*se supone que tien que igresar un formato de entrada y salida por que no hay*/
/* valores por omision*/
	if( parametro_argumentos.frmt_entrada == FRMT_INCORRECTO ||
		parametro_argumentos.frmt_salida == FRMT_INCORRECTO ){
		estado = ST_ERROR_FRMT_INDEFINIDO;
	}
	if( estado != ST_OK ){
		imprimir_error(estado);
		return EXIT_FAILURE;
	}
	return ST_OK;
}



