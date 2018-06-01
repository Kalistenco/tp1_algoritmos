#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrada.h"
#include "tipos.h"

/*
#include "argumentos.h"
esto solo para probar el programa
int main(void){
	struct mensajero msj;
	status_t_entrada estado;
	inicializar_mensajero( &msj);
	estado = procesar_entrada( &msj );
	free(cabeza.lista_instrucciones);
	if( estado != ST_OK ){
		return EXIT_FAILURE;
	}

return EXIT_SUCCESS;
}

*/

status_t_entrada procesar_entrada( struct mensajero * msj ){

	FILE * archivo;
	char  cadena_ingreso[MAX_CANT_INGRESO];
	size_t var_posc;
	int palabra_convertida_aux;
	int * vtr_palabras_convertidas_aux;
	size_t cant_memoria_aux;
	status_t_entrada estado;


	if( !msj ){
		return ST_PUNTERO_NULO;
	}


/*creo una variable auxiliar para no desreferenciar un puntero varias veces*/
	cant_memoria_aux = msj -> cant_memoria;

/*se crea el vector donde guardara las palabras convertidas*/
	vtr_palabras_convertidas_aux = (int*)calloc( cant_memoria_aux,sizeof(int) );
	if( !vtr_palabras_convertidas_aux ){
		return ST_ERROR_NO_MEMORIA;
	}

/*caso donde se lee por stdin*/
	if( msj -> entrada_archivo == FALSO ){
		var_posc = 0;
		while( var_posc < cant_memoria_aux ){
/********poner el formato en una cadena************/
			 printf("%2lu  :?",var_posc );
			if( !fgets( cadena_ingreso , MAX_CANT_INGRESO , stdin )){
/*no pudo leer por consola*/
				/*puts();*/
				estado = ST_ERROR_LEER_CONSOLA;
				break;
			}
			estado = convertir_palabra_str_int( cadena_ingreso,&palabra_convertida_aux );
			if( estado == ST_FIN_INGRESO ){
				break;
			}
			if( estado == ST_OK ){
/*si pudo convertir la palabra a un entero lo guarda en el vector*/
				vtr_palabras_convertidas_aux[var_posc] = palabra_convertida_aux;
				var_posc++;
			}
/*si se ingresa solo espacios sigue leytendo sobre la misma posicion del vector*/
			else if( estado == ST_VECTOR_DE_ESPACIOS ){
								continue;
			}
/*el estado puede ser un error o que se leyo la palabra final*/
			else{
				break;
			}
		}
	}
/*si se lee de un archivo*/
	else{
		archivo = fopen(msj -> entrada_archivo_nombre ,"r");
		if( !archivo ){
			free(vtr_palabras_convertidas_aux);
			return ST_ERROR_ABRIR_ARCHIVO;
		}
		var_posc = 0;
		while( var_posc < cant_memoria_aux ){
			if( !fgets( cadena_ingreso,MAX_CANT_INGRESO,archivo )){
				if( feof(archivo) ){
/*si fgets lee cadena vacia y EOF esta activo , entonces */
/*se termino de leer el archivo*/
					estado = ST_EOF_Y_CADENA_VACIA;
					break;
				}
				else{
/*si fgets devuelve NULL y no esta activo EOF entonces no pudo leer el archivo*/
					estado = ST_ERROR_LECTURA_ARCHIVO;
					break;
				}
			}
			estado = convertir_palabra_str_int( cadena_ingreso,&palabra_convertida_aux );
/*si se detecta el fin de ingreso , este valor no se carga y termina la carga*/
			if( estado == ST_FIN_INGRESO ){
				break;
			}
			if( estado == ST_OK ){
/*si pudo convertir la palabra a un entero y no fue el valor de salir lo guarda en el vector*/
				vtr_palabras_convertidas_aux[var_posc] = palabra_convertida_aux;
				var_posc++;
			}
/*si se ingresa solo espacios sigue leytendo sobre la misma posicion del vector*/
			else if( estado == ST_VECTOR_DE_ESPACIOS ){
								continue;
			}
/*el estado puede ser un error o que se leyo la palabra final*/
			else{
				break;
			}
		}
		if( fclose(archivo) == EOF ){
/*no pudo cerrar el archivo*/
			free(vtr_palabras_convertidas_aux);
			return ST_ERROR_CERRAR_ARCHIVO;
		}
	}

	if( estado == ST_EOF_Y_CADENA_VACIA || estado == ST_OK || estado == ST_FIN_INGRESO ){
		if( var_posc > 0 ){
			cabeza.lista_instrucciones = vtr_palabras_convertidas_aux;
			return ST_OK;
		}
		else{
			free(vtr_palabras_convertidas_aux);
			return ST_ERROR_VECTOR_VACIO;
		}
	}
/*se retorna el estado para luego evaluar e imprimir el error en main*/
	else{
		free(vtr_palabras_convertidas_aux);
		return estado ;
	}

}


/*recibe la cadena completa lo que se lee por stdin o una line del archivo*/
/*limpia la cadena y retorna la palabra convertida por la interfaz */
status_t_entrada convertir_palabra_str_int( char * cadena_ingreso , int * palabra_convertida ){
	size_t var_aux;
	size_t var_posc;
	char cadena_palabra[MAX_LARGO_PALABRA + 1];
	int palabra_convertida_aux;
	char * ptr_aux;
	size_t cant_caract_omitir;
	char caracter_aux;

	if( !cadena_ingreso || !palabra_convertida ){
		return ST_PUNTERO_NULO;
	}
/*no trabajo con la variable recibida , utiliza una variable auxiliar */
/*cualqueir error que ocurra se devolvera un valor invalido */
	*palabra_convertida = -1;

/*busca si se inicio un comentario*/
	ptr_aux = strchr( cadena_ingreso,INICIO_COMENTARIO );
	if( ptr_aux ){
/*no se trabaja con el comentario , asi que se corta la cadena ahi*/
		*ptr_aux = '\0';
	}
/*existe el caso de leer por consola y tener un \n en la cadena */
/*lo cambio por un \0 para no tener problemas con este caracter mas adelante*/
	ptr_aux = strchr( cadena_ingreso,CARACTER_BARRA_N );
	if( ptr_aux ){
		*ptr_aux = '\0';
	}

	for( var_posc = 0,cant_caract_omitir = 0;
		cadena_ingreso[var_posc] != '\0';
		var_posc++ ){
/*se utiliza una variable auxiliar para no desreferencia mas de una vez*/
		caracter_aux = cadena_ingreso[var_posc];
		switch( caracter_aux ){
/*se puede ingresar caracteres especificos(espacios) entre el inicio y la palabra */
/*y/o la palabra y el inicio , esos caracteres se deben omitir */
/*esto pasa cuando el comentario es largo y no alcanza escribirlo en una linea*/
			case CARACTER_A_OMITIR:
				cant_caract_omitir++;
				break;

/*toda "palabra" comienza con un signo + (mas) */
			case INICIO_PALABRA:
				for( var_aux = 0 ;
/*leo el siguiente caracter despues del + , y se guardo en un vector*/
/*se lee MAX_LARGO_PALABRA(4) caracteres + 1 por el igual */
					 cadena_ingreso[++var_posc] != '\0' &&var_aux <= MAX_LARGO_PALABRA;
					 var_aux++ ){
					cadena_palabra[var_aux] = cadena_ingreso[var_posc];
				}
/*si carga la cadena con MAX_LAR....(4) caracteres + 1 */
				if( var_aux == MAX_LARGO_PALABRA + 1 ){
/*entonces en la ultima POSICION del vector debe hacer un caracter valido ,es decir un espacio o \0 */
					caracter_aux = cadena_palabra[var_aux - 1];
					if( caracter_aux != CARACTER_A_OMITIR ){
						return ST_ERROR_PALABRA_INCORRECTA;
					}
					else{
/*si era un CARACTER_A.....R se cabia por un \0 */
					cadena_palabra[var_aux - 1] = '\0';
					}
				}
/*si carga la cadena con MAX_LARGO...(4) caracteres */
/*es por que se encontro con un \0 en la posicion MAX_LARGO....*/
				else if( var_aux == MAX_LARGO_PALABRA ){
/*cierro la cadena con ese \0*/
					cadena_palabra[var_aux] = cadena_ingreso[var_posc];
				}
/*de no pasar los casos anteriores , entonces solo pudo leer menos caracteres que el MAX_LARGO...*/
				else{
					return ST_ERROR_PALABRA_INCOMPLETA;
				}
				break;

			case INICIO_FIN_INGRESO:
				for( var_aux = 0 ;
/*leo el siguiente caracter despues del - , y se guardo en un vector*/
/*se lee MAX_LARGO_PALABRA_FIN(5) caracteres + 1 por el igual */
					 cadena_ingreso[++var_posc] != '\0' &&var_aux <= MAX_LARGO_PALABRA_FIN;
					 var_aux++ ){
					cadena_palabra[var_aux] = cadena_ingreso[var_posc];
				}
/*si carga la cadena con MAX_LAR....(5) caracteres + 1 */
				if( var_aux == MAX_LARGO_PALABRA_FIN + 1 ){
/*entonces en la ultima POSICION del vector debe hacer un caracter valido ,es decir un espacio o \0 */
					caracter_aux = cadena_palabra[var_aux - 1];
					if( caracter_aux != CARACTER_A_OMITIR ){
						return ST_ERROR_PALABRA_INCORRECTA;
					}
					else{
/*si era un CARACTER_A.....R se cabia por un \0 */
					cadena_palabra[var_aux - 1] = '\0';
					}
				}
/*si carga la cadena con MAX_LARGO...(4) caracteres */
/*es por que se encontro con un \0 en la posicion MAX_LARGO....*/
				else if( var_aux == MAX_LARGO_PALABRA_FIN ){
/*cierro la cadena con ese \0*/
					cadena_palabra[var_aux] = cadena_ingreso[var_posc];
				}
/*de no pasar los casos anteriores , entonces solo pudo leer menos caracteres que el MAX_LARGO...*/
				else{
					return ST_ERROR_PALABRA_INCOMPLETA;
				}
				break;
			default:
				return ST_ERROR_PALABRA_INCORRECTA;
		}
/*si paso por el caso INICIO_PALABRA o INICIO_FI.., var_posc es la posicion del \0 */
/*entonces saldria del ciclo , esto si sale todo bien , en el caso que ocurra un error sale con return*/
	}
	if( cant_caract_omitir == var_posc ){
/*son todos espacios*/
		return ST_VECTOR_DE_ESPACIOS;
	}

	palabra_convertida_aux = strtol( cadena_palabra,&ptr_aux,10 );
	/*se valida que convirtio los 4 caracteres a un numero */
	if( *ptr_aux != '\0' ){
/*la palabra no contiene solo numeros*/
		return ST_ERROR_PALABRA_INCORRECTA;
	}
	if( !palabra_convertida_aux ){
/*como strtol devuelve 0 si apareciera un error */
/*se tiene que validar que no se ingreso el 0000 */
/*considero que puedo ingresar menos ceros y se considerara como +0000 (es necesario el signo))*/
		for( var_aux = 0 ; cadena_palabra[var_aux] != '\0' ; var_aux++){
			if( cadena_palabra[var_aux] != '0' ){
/*si no es el 0 es por que hubo un error en strtol entonces para que se identifique ese error */
/*cargo a var_aux un valor incorrecto por ejemplo : */
				var_aux = MAX_LARGO_PALABRA + 1;
				break;
			}
		}
/*si devuelve 0 (strtol) y la palabra no era 0000, entonces es un error*/
		if( var_aux > MAX_LARGO_PALABRA ){
			return ST_ERROR_PALABRA_INCORRECTA;
		}
	}
/*si llega a este punto es por que la palabra era cero o se pudo convertir a un numero */

	if( palabra_convertida_aux == PALABRA_FIN_INGRESO ){
		return ST_FIN_INGRESO;
	}
	if( palabra_convertida_aux > MAX_PALABRA_ACEPTADA ||
		palabra_convertida_aux < MIN_PALABRA_ACEPTADA ){
		return ST_ERROR_PALABRA_FUERA_DE_RANGO;
	}
/*en este punto todo salio bien ,esta dentro de rango y no es la palabra para terminar el ingreso*/
/*entonces se carga el valor*/
	*palabra_convertida = palabra_convertida_aux;
	printf("La palabra convertida es :%i\n",*palabra_convertida);
	return ST_OK;
}



void imprimir_error_entrada( status_t_entrada estado_entrada ){

	switch( estado_entrada ){
		case ST_ERROR_LECTURA_ARCHIVO:
			fprintf( stderr,"%s:%s\n", MSJ_ERROR_PREFIJO , MSJ_ERROR_LECTURA_ARCHIVO );
			break;
		case ST_ERROR_PALABRA_INCORRECTA:
			fprintf( stderr,"%s:%s\n", MSJ_ERROR_PREFIJO , MSJ_ERROR_PALABRA_INCORRECTA );
			break;
		case ST_ERROR_PALABRA_INCOMPLETA:
			fprintf( stderr,"%s:%s\n", MSJ_ERROR_PREFIJO , MSJ_ERROR_PALABRA_INCOMPLETA );
			break;
		case ST_PUNTERO_NULO:
			fprintf( stderr,"%s:%s\n", MSJ_ERROR_PREFIJO , MSJ_ERROR_PUNTERO_NULO );
			break;
		case ST_ERROR_ABRIR_ARCHIVO:
			fprintf( stderr,"%s:%s\n", MSJ_ERROR_PREFIJO , MSJ_ERROR_ABRIR_ARCHIVO );
			break;
		case ST_ERROR_NO_MEMORIA:
			fprintf( stderr,"%s:%s\n", MSJ_ERROR_PREFIJO , MSJ_ERROR_NO_MEMORIA );
			break;
		case ST_ERROR_CERRAR_ARCHIVO:
			fprintf( stderr,"%s:%s\n", MSJ_ERROR_PREFIJO , MSJ_ERROR_CERRAR_ARCHIVO );
			break;
		case ST_ERROR_LEER_CONSOLA:
			fprintf( stderr,"%s:%s\n", MSJ_ERROR_PREFIJO , MSJ_ERROR_LEER_CONSOLA );
			break;
		case ST_ERROR_PALABRA_FUERA_DE_RANGO:
			fprintf( stderr,"%s:%s\n", MSJ_ERROR_PREFIJO , MSJ_ERROR_PALABRA_FUERA_DE_RANGO);
		case ST_ERROR_VECTOR_VACIO:
			fprintf( stderr,"%s:%s\n", MSJ_ERROR_PREFIJO , MSJ_ERROR_VECTOR_VACIO);
			break;
		default:
			fprintf( stderr,"%s:%s\n", MSJ_ERROR_PREFIJO,"Error no especifivado" );
	}
	return;
}
