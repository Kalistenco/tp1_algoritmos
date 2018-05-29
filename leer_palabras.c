#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrada.h"

int main(void){
	char archivo_entrada[] = "file.txt";
	size_t cant_palabras = 3;
	int * vtr_palabras_convertidas;
	status_t estado;

	estado = procesar_entrada_archivo( cant_palabras,archivo_entrada,&vtr_palabras_convertidas );
	if( estado != ST_OK ){
		puts("Imprime error");
		free(vtr_palabras_convertidas);
		return EXIT_FAILURE;
	}
	else{
		puts("Todo salio bien en el main");
		free(vtr_palabras_convertidas);
		return EXIT_SUCCESS;
	}
}
/*esta funcion lee el archivo de entrada */
 /* y dvuelve un vector de palabras convertidas a enteros */
status_t procesar_entrada_archivo( size_t  cant_palabras , char * archivo_entrada ,
								   int ** pvtr_palabras_convertidas ){
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

	archivo = fopen(archivo_entrada,"r");
	if( !archivo ){
		puts("No pudo abrir el archivo");
		return ST_ERROR_ABRIR_ARCHIVO;
	}

	vtr_palabras_convertidas_aux =( int * )calloc( cant_palabras,sizeof(int) );
	if( !vtr_palabras_convertidas_aux ){
/*si no se puede crear el vector para las palabras ,*/
/* entonces se cierra el archivo y termina*/
		puts("No hay memoria para crear un vector");
		fclose(archivo);
		return ST_ERROR_NO_MEMORIA;
	}

	for( var_aux = 0,var_posc = 0;var_posc < cant_palabras
		 ;var_aux++){
		if( !fgets( cadena_ingreso,MAX_CANT_INGRESO,archivo )){
			if( feof(archivo) ){
/*si fgets lee cadena vacia y EOF esta activo , entonces */
/*se termino de leer el archivo*/
				puts("Encontro fin de archivo y la cadena esta vacia");
				estado = ST_EOF_Y_CADENA_VACIA;
				break;
			}
			else{
/*si fgets devuelve NULL y no esta activo EOF entonces no pudo leer el archivo*/
				puts("Error al querer leer de ARCHIVO");
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
/*como no se va seguir leyendo el archivo , se cierra el flujo*/
	if( fclose( archivo ) == EOF ){
/*si aparece un error se debe liberar la memoria y terminar*/
		puts("El archivo no pudo ser cerrado");
		free(vtr_palabras_convertidas_aux);
		return ST_ERROR_CERRAR_ARCHIVO;
	}
	if( estado == ST_EOF_Y_CADENA_VACIA || estado == ST_OK ){
		if( var_posc != cant_palabras ){
/*si termina de leer el archivo y no se lleno el vector es un error*/
			puts("No se lleno el vector");
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
		puts("Imprimir error");
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
			puts("Error encontraste una letra en la palabra ingresada");
			return ST_ERROR_PALABRA_INCORRECTA;
		}
/*toda "palabra" comienza con un signo + (mas) */
		if( caracter_aux == '+' ){
/*cuando se encuentra el signo mas , se copia los siguientes 4 caracteres */
/*si no llegara a ser un numero se sabra en el momento de convertirlo*/
			for( var_aux = 0;
				 cadena_ingreso[var_posc + 1] != '\0'&&var_aux < MAX_LARGO_PALABRA;
				 var_posc++,var_aux++ ){
				cadena_palabra[var_aux] = cadena_ingreso[var_posc + 1];
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

	if( cant_espacios == var_posc - 1 ){
		puts("Son todos espacios");
		return ST_VECTOR_DE_ESPACIOS;
	}
/*si pudo guardar los 4 caracteres despues del + , entonces , cierra la cadena*/
	if( var_aux == MAX_LARGO_PALABRA ){
		cadena_palabra[var_aux] = '\0';
	}
	else{
		puts("La palabra esta incompleta");
		return ST_ERROR_PALABRA_INCOMPLETA;
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
			puts("Ingreso el 0000");
/*como el 0 es un valor correcto , se carga y termian la funcion*/
			*palabra_convertida = 0;
			return ST_OK;
		}
/*si devuelve 0 (strtol) y no es el 0 , entonces s un error*/
		puts("Error al convertir la palabra");
		return ST_ERROR_PALABRA_NO_CONVERTIDA;
	}
/*se valida que convirtio los 4 caracteres a un numero */
	if( *ptr_aux != '\0' ){
		puts("Error la palabra no contiene solo numeros");
		return ST_ERROR_PALABRA_NO_NUMERICA;
	}
/*en este punto todo salio bien , entonces se carga el valor*/
	*palabra_convertida = palabra_convertida_aux;
	printf("La palabra convertida es :%i\n",*palabra_convertida);
	return ST_OK;
}

