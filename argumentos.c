#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argumentos.h"


status_t validar_cant_palabras( char * arg , long * cant_palabras ){

	long cant_palabras_aux;
	char * ptr_aux;

	if( !arg || !cant_palabras ){
		return ST_PUNTERO_NULO;
	}
	*cant_palabras = 0;
	if( !(cant_palabras_aux = strtol( arg , &ptr_aux , 10 )) ){
		return ST_ERROR_N_INGRESADO;
	}
	if( *ptr_aux != '\0' ){
		return ST_ERROR_N_INGRESADO;
	}
	if( cant_palabras_aux < 0 || cant_palabras_aux > MAX_CANT_PALABRAS ){
		return ST_ERROR_CANT_N;
	}
	*cant_palabras = cant_palabras_aux;
	return ST_OK;
}

/*funcion para validar argumentos */
status_t validar_argumento( char * arg_recibido ,
							argumentos_t * argumento ,
							diccionario_t * ptr_diccionario ){
/*en clase se vio que estaba bueno trabajar con un nivel menos de puntero*/
/*siguiendo esa idea , se crea argumento_aux y se trabaja con ella*/
/*en la ultima parte , si todo sale bien , se lo asigna a *argumento */
	size_t var_conteo;
	argumentos_t argumento_aux;

	if( !arg_recibido  || !argumento || !ptr_diccionario ){
		return ST_PUNTERO_NULO;
	}
/*esta parte es para independizarse de los argumentos como cadenas */
/*y comenzar a trabajar solo con las constantes simbolicas (ARG_H , ARG_M ...)*/
/*obiamente depende de los valores que se asignan en el diccionario*/
/*pero se supone que esos valores lo elegimos*/
	for( var_conteo = 0 ; var_conteo < MAX_CANT_ARGUMENTOS; var_conteo++){
		if( !strcmp(arg_recibido, ptr_diccionario -> vtr_argumentos[var_conteo])){
			break;
		}
	}
	switch( var_conteo ){
		case ARG_H:
			argumento_aux = ARG_H;
			break;
		case ARG_M:
			argumento_aux = ARG_M;
			break;
		case ARG_I:
			argumento_aux = ARG_I;
			break;
		case ARG_IF:
			argumento_aux = ARG_IF;
			break;
		case ARG_O:
			argumento_aux = ARG_O;
			break;
		case ARG_OF:
			argumento_aux = ARG_OF;
			break;
		case ARG_INVALIDO:
			argumento_aux = ARG_INVALIDO;
	}
	*argumento = argumento_aux;
	if( argumento_aux == ARG_INVALIDO ){
	return ST_ARGUMENTO_INVALIDO;
	}
	return ST_OK;
}

/*se sigue la misma idea de la funcion anterior*/
status_t validar_frmt_if_of( char * arg_recibido ,
							 frmt_if_of_t * frmt_if_of,
							 diccionario_t * diccionario){

	frmt_if_of_t frmt_if_of_aux;
	size_t var_conteo;

	if( !arg_recibido || !frmt_if_of || !diccionario ){
		return ST_PUNTERO_NULO;
	}

	*frmt_if_of = FRMT_INCORRECTO;

	for( var_conteo = 0; var_conteo < MAX_CANT_FRMT; var_conteo++){
		if( !strcmp( arg_recibido , diccionario -> vtr_parametro_if_of[var_conteo] )){
			break;
		}
	}
	switch(var_conteo){
		case FRMT_BIN:
			frmt_if_of_aux = FRMT_BIN;
			break;
		case FRMT_TXT:
			frmt_if_of_aux = FRMT_TXT;
			break;
		default:
			frmt_if_of_aux = FRMT_INCORRECTO;
	}
	*frmt_if_of = frmt_if_of_aux;
	if( frmt_if_of_aux == FRMT_INCORRECTO ){
		return ST_FRMT_INCORRECTO;
	}
	return ST_OK;
}

/*por lo general todas las funciones que hago retornan un status_t ,*/
/*pero si esta funcion devolviera un status_t*/
/*¿donde se imprime el error de esta funcion?*/
void imprimir_error(status_t estado){

	switch( estado ){
		case ST_PUNTERO_NULO:
			puts("Puntero Nulo");
			break;
		case ST_ARGUMENTO_INVALIDO:
			puts("Argumento invalido");
			break;
		case ST_FRMT_INCORRECTO:
			puts("Formato incorrecto");
			break;
		case ST_ERROR_CANT_N:
			puts("Error en la cantidad de N");
			break;
		case ST_ERROR_N_INGRESADO:
			puts("Error en el N ingresado");
			break;
		case ST_OK:
			puts("Termino por que se encontro un argumento donde iva un aprametro");
			break;
		default:
			puts("Error");
	}
	return;
}

/*aunque esta parte del codigo se repita una vez */
/*creo que es una buena idea hacerla funcion para la parte de modularizacion*/
status_t cargar_frmt_if_of( frmt_if_of_t frmt_if_of ,
							parametro_argumentos_t * parametro_argumentos,
							argumentos_t argumento ){

	if( !parametro_argumentos ){
		return ST_PUNTERO_NULO;
	}
	if( argumento == ARG_IF ){
		switch( frmt_if_of ){
			case FRMT_BIN:
				parametro_argumentos -> frmt_entrada = FRMT_BIN;
				break;
			case FRMT_TXT:
				break;
			default:
				parametro_argumentos -> frmt_entrada = FRMT_INCORRECTO;
				return ST_FRMT_INCORRECTO;
		}
	}
	return ST_OK;
}

/*falta rellenar pero la idea seria que imprima la ayuda*/
void imprimir_ayuda(void){
	puts("Imprimir ayuda");
	return;
}
