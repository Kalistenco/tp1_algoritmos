#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrada.h"

status_t procesar_entrada_archivo( size_t  cant_palabras ,
								   char * archivo_entrada ,
								   int ** pvtr_palabras_convertidas ,
								   bool_t entrada_archivo ,
								   archivo_t entrada_tipo ){
	FILE * archivo;
	char  cadena_ingreso[MAX_CANT_INGRESO];
	size_t var_posc;
	int palabra_convertida_aux;
	int * vtr_palabras_convertidas_aux;
	size_t var_aux;
	status_t estado;

	if( !archivo_entrada || !pvtr_palabras_convertidas ){
		return ST_PUNTERO_NULO;
	}
/*se crea el vector donde guardara las palabras convertidas*/
	vtr_palabras_convertidas_aux =( int * )calloc( cant_palabras,sizeof(int) );
	if( !vtr_palabras_convertidas_aux ){
		return ST_ERROR_NO_MEMORIA;
	}
/*caso donde se lee por stdin*/
	if( entrada_archivo == FALSO ){
		for( var_aux = 0,var_posc = 0;var_posc < cant_palabras
			 ;var_aux++){
			if( !fgets( cadena_ingreso,MAX_CANT_INGRESO,stdin )){
/*no pudo leer por consola*/
				estado = ST_ERROR_LEER_CONSOLA;
				break;
			}
			estado = convertir_palabra_str_int( cadena_ingreso,&palabra_convertida_aux );
			if( estado == ST_OK ){
/*si pudo convertir la palabra a un entero lo guarda en el vector*/
				vtr_palabras_convertidas_aux[var_posc] = palabra_convertida_aux;
				var_posc++;
			}
			else if( estado == ST_VECTOR_DE_ESPACIOS )
								{}
			else{
				break;
			}
		}
	}
	else{
		archivo = fopen(archivo_entrada,"r");
		if( !archivo ){
			free(vtr_palabras_convertidas_aux);
			return ST_ERROR_ABRIR_ARCHIVO;
		}
		for( var_aux = 0,var_posc = 0;var_posc < cant_palabras
			 ;var_aux++){
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
			if( estado == ST_OK ){
/*si pudo convertir la palabra a un entero lo guarda en el vector*/
				vtr_palabras_convertidas_aux[var_posc] = palabra_convertida_aux;
				var_posc++;
			}
			else if( estado == ST_VECTOR_DE_ESPACIOS )
								{}
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

	if( estado == ST_EOF_Y_CADENA_VACIA || estado == ST_OK ){
		if( var_posc != cant_palabras ){
/*si termina de leer el archivo y no se lleno el vector es un error*/
			free(vtr_palabras_convertidas_aux);
			return ST_ERROR_VECTOR_INCOMPLETO;
		}
		else{
			puts("Fue cargado correctamente");
			*pvtr_palabras_convertidas = vtr_palabras_convertidas_aux;
			return ST_OK;
		}
	}
	else{
/*se retorna el estado para luego evaluar e imprimir el error en main*/
		free(vtr_palabras_convertidas_aux);
		return estado;
	}
}


status_t convertir_palabra_str_int( char * cadena_ingreso , int * palabra_convertida ){
	size_t var_aux;
	size_t var_posc;
	char cadena_palabra[MAX_LARGO_PALABRA + 1];
	int palabra_convertida_aux;
	char * ptr_aux;
	size_t cant_espacios;
	char caracter_aux;

	if( !cadena_ingreso || !palabra_convertida ){
		return ST_PUNTERO_NULO;
	}
/*no trabajo con la variable recibida , utiliza una variable auxiliar */
/*cualqueir error que ocurra se devolvera un valor invalido */
	*palabra_convertida = -1;
/*busca si se inicio un comentario*/
	ptr_aux = strchr( cadena_ingreso,';' );
	if( ptr_aux ){
/*no se trabaja con el comentario , asi que se corta la cadena ahi*/
		*ptr_aux = '\0';
	}
	for( var_posc = 0,cant_espacios = 0;
		cadena_ingreso[var_posc] != '\0';
		var_posc++ ){
/*se utiliza una variable auxiliar para no desreferencia mas de una vez*/
		caracter_aux = cadena_ingreso[var_posc];
/*se descarto un comentario , entonces si apareciera una letra se trata como error*/
		if(( caracter_aux > 'a' && caracter_aux < 'z' )||
			( caracter_aux > 'A' && caracter_aux < 'Z' )){
/*se encontro una letra en la palabra*/
			return ST_ERROR_PALABRA_INCORRECTA;
		}
/*toda "palabra" comienza con un signo + (mas) */
		if( caracter_aux == '+' ){
/*cuando se encuentra el signo mas , se copia los siguientes 4 caracteres */
/*si no llegara a ser un numero se sabra en el momento de convertirlo*/
			for( var_aux = 0;
				 cadena_ingreso[var_posc + 1] != '\0'&&var_aux <= MAX_LARGO_PALABRA;
				 var_posc++,var_aux++ ){
				cadena_palabra[var_aux] = cadena_ingreso[var_posc + 1];
			}
/*si pudo leer la palabra y un caracter mas */
			if( var_aux == MAX_LARGO_PALABRA + 1){
/*pregunta si el ultimo caracter es valido ( \n, \0 , ESPACIO) */
/*es decir no ingreso una palabra incorrecta ( por ejemplo +12345 )*/
				caracter_aux = cadena_palabra[var_aux - 1];
				if( caracter_aux == ' ' || caracter_aux == '\n' ){
/*cambia ese caracter por un \0*/
					cadena_palabra[var_aux - 1] = '\0';
				}
				else if( caracter_aux != '\0' ){
					return ST_ERROR_PALABRA_INCORRECTA;
				}
			}
/*si solo pudo leer los 4 caracteres de la palabra*/
			else if( var_aux == MAX_LARGO_PALABRA ){
				cadena_palabra[var_aux] = '\0';
			}
/*si lee menos de 4 caracteres */
			else{
				return ST_ERROR_PALABRA_INCOMPLETA;
			}
			break;
		}
/*se puede ingresar espacios en blanco y comentarios */
/*esto pasa cuando el comentario es largo y no alcanza escribirlo en una linea*/
/*se deben omitir*/
		if( caracter_aux == ' ' ){
			cant_espacios++;
		}
	}

	if( cant_espacios == var_posc ){
/*son todos espacios*/
		return ST_VECTOR_DE_ESPACIOS;
	}

	palabra_convertida_aux = strtol( cadena_palabra,&ptr_aux,10 );
	if( !palabra_convertida_aux ){
/*como strtol devuelve 0 si apareciera un error */
/*se tiene que validar que no se ingreso el 0000 */
		for( var_aux = 0;cadena_palabra[var_aux] != '\0';var_aux++){
			if( cadena_palabra[var_aux] != '0' ){
				break;
			}
		}
		if( var_aux == MAX_LARGO_PALABRA ){
/*como el 0 es un valor correcto , se carga y termian la funcion*/
			*palabra_convertida = 0;
			return ST_OK;
		}
/*si devuelve 0 (strtol) y no es el 0 , entonces s un error*/
		return ST_ERROR_PALABRA_NO_CONVERTIDA;
	}
/*se valida que convirtio los 4 caracteres a un numero */
	if( *ptr_aux != '\0' ){
/*la palabra no contiene solo numeros*/
		return ST_ERROR_PALABRA_NO_NUMERICA;
	}
/*en este punto todo salio bien , entonces se carga el valor*/
	*palabra_convertida = palabra_convertida_aux;
	printf("La palabra convertida es :%i\n",*palabra_convertida);
	return ST_OK;
}

