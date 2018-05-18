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
	parametro_argumentos.frmt_lectura = STDIO;
	parametro_argumentos.frmt_volcado = STDIO;
	parametro_argumentos.frmt_entrada = FRMT_TXT;
	parametro_argumentos.frmt_salida = FRMT_BIN;

	while( var_conteo < argc - 1 ){
/*el programa empieza a trabakar con argv[1]*/
/*recordar que argv[0] es ./programa*/
		var_conteo++;
/*valida que argv[1] sea un argumento valido*/
		estado = validar_argumento( argv[var_conteo] , &argumento , &diccionario);
		if( estado != ST_OK){
			imprimir_error(estado);
			return EXIT_FAILURE;
		}
/*si el argumento fuera -h imprime la ayuda y sale no tiene que hacer nada mas*/
		if( argumento == ARG_H ){
			imprimir_ayuda();
			return EXIT_SUCCESS;
		}
		var_conteo++;
/*hasta aca se que argv[1] es un argumento valido y no es -h*/
/*entonces el siguiente no tiene que ser un argumento */
/*seria el ejemplo -if -o es un error , si se pone -if se tiene que agregar*/
/*un parametro*/
		estado = validar_argumento( argv[var_conteo] , &argumento_aux , &diccionario);
		if( estado != ST_ARGUMENTO_INVALIDO ){
/*estado puede ser ST_OK que es contradictorio terminar cuando tenemos ese estado*/
/*si se pasa este estado a la funcion imprimir_error */
/*es por que hubo un argumento donde iva un parametro*/
			imprimir_error(estado);
			return EXIT_FAILURE;
		}
		if( argumento == ARG_IF || argumento == ARG_OF ){
			estado = validar_frmt_if_of( argv[var_conteo] , &frmt_if_of , &diccionario);
			if( estado != ST_OK ){
				imprimir_error(estado);
				return EXIT_FAILURE;
			}
			estado = cargar_frmt_if_of( frmt_if_of , &parametro_argumentos , argumento);
			if( estado != ST_OK ){
				imprimir_error(estado);
				return EXIT_FAILURE;
			}
		}
		else if( argumento == ARG_I || argumento == ARG_O ){
/*si aparecen estos argumentos , solo puede ser de la forma */
/*-if archivo , -of archivo  y si no aparece -if o -of se toman los valores por*/
/*omision , -if -of es invalido*/
			if( argumento == ARG_I ){
				parametro_argumentos.frmt_lectura = ARCHIVO;
			}
			else{
				parametro_argumentos.frmt_volcado = ARCHIVO;
			}
		}

		else if( argumento == ARG_M ){
			estado = validar_cant_palabras( argv[var_conteo] , &Na );
			if( estado != ST_OK ){
				imprimir_error(estado);
				return EXIT_FAILURE;
			}
/*en este punto se que el parametro de -m es correcto entonces se carga */
			parametro_argumentos.N = Na ;
		}
		else{
			return EXIT_FAILURE;
		}
	}
	return ST_OK;
}



