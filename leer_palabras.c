#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANT_INGRESO 50
#define MAX_LARGO_PALABRA 4
#define MAX_CANT_PALABRAS 3

typedef enum{
	ST_OK,
	ST_SALIR_CICLO,
	ST_EOF_Y_CADENA_VACIA,
	ST_ERROR_LECTURA_ARCHIVO,
	ST_ERROR_PALABRA_INCORRECTA,
	ST_ERROR_PALABRA_INCOMPLETA,
	ST_VECTOR_DE_ESPACIOS,
	ST_ERROR_PALABRA_NO_CONVERTIDA,
	ST_ERROR_PALABRA_NO_NUMERICA,
	ST_PUNTERO_NULO
}status_t;

status_t convertir_palabra_str_int(char * cadena_ingreso,int * palabra_convertida);
/*status_t procesar_entrada_archivo( size_t  cant_palabras , char * archivo_entrada ,int ** pvtr_palabras_convertidas )*/
int main(void){

	FILE * archivo;
	char  cadena_ingreso[MAX_CANT_INGRESO];
	size_t var_posc;
	int palabra_convertida_aux;
	int * vtr_palabras_convertidas_aux;
	size_t var_aux;
	status_t estado;


	archivo = fopen("file.txt","r");
	if( !archivo ){
		puts("No pudo abrir el archivo");
		return EXIT_FAILURE;
	}

	vtr_palabras_convertidas_aux =( int * )calloc( MAX_CANT_PALABRAS,sizeof(int) );
	if( !vtr_palabras_convertidas_aux ){
		puts("No hay memoria para crear un vector");
		fclose(archivo);
		return EXIT_FAILURE;
	}

	for( var_aux = 0,var_posc = 0;var_posc < MAX_CANT_PALABRAS
		 ;var_aux++){
		if( !fgets( cadena_ingreso,MAX_CANT_INGRESO,archivo )){
			if( feof(archivo) ){
				puts("Encontro fin de archivo y la cadena esta vacia");
				estado = ST_EOF_Y_CADENA_VACIA;
				break;
			}
			else{
				puts("Error al querer leer de ARCHIVO");
				estado = ST_ERROR_LECTURA_ARCHIVO;
				break;
			}
		}
		estado = convertir_palabra_str_int( cadena_ingreso,&palabra_convertida_aux );
		if( estado == ST_OK ){
			vtr_palabras_convertidas_aux[var_posc] = palabra_convertida_aux;
			var_posc++;
		}
		else if( estado == ST_VECTOR_DE_ESPACIOS )
							{}
		else{
			break;
		}
	}
	if( fclose( archivo ) == EOF ){
		puts("El archivo no pudo ser cerrado");
		free(vtr_palabras_convertidas_aux);
		return EXIT_FAILURE;
	}
	if( estado == ST_EOF_Y_CADENA_VACIA || estado == ST_OK ){
		if( var_posc != MAX_CANT_PALABRAS ){
			puts("No se lleno el vector");
			free(vtr_palabras_convertidas_aux);
			return EXIT_FAILURE;
		}
		else{
			puts("Fue cargado correctamente");
			/**pvtr_palabras_convertidas = vtr_palabras_convertidas_aux;*/
			free(vtr_palabras_convertidas_aux);
			return EXIT_SUCCESS;
		}
	}
	else{
		puts("Imprimir error");
		free(vtr_palabras_convertidas_aux);
		return EXIT_FAILURE;
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

	*palabra_convertida = -1;
	ptr_aux = strchr( cadena_ingreso,';' );
	if( ptr_aux ){
		*ptr_aux = '\0';
	}
	for( var_posc = 0,cant_espacios = 0;
		cadena_ingreso[var_posc] != '\0';
		var_posc++ ){
		caracter_aux = cadena_ingreso[var_posc];
		if(( caracter_aux > 'a' && caracter_aux < 'z' )||
			( caracter_aux > 'A' && caracter_aux < 'Z' )){
			puts("Error encontraste una letra en la palabra ingresada");
			return ST_ERROR_PALABRA_INCORRECTA;
		}
		if( caracter_aux == '+' ){
			for( var_aux = 0;
				 cadena_ingreso[var_posc + 1] != '\0'&&var_aux < MAX_LARGO_PALABRA;
				 var_posc++,var_aux++ ){
				cadena_palabra[var_aux] = cadena_ingreso[var_posc + 1];
			}
			break;
		}
		if( caracter_aux == ' ' ){
			cant_espacios++;
		}
	}

	if( cant_espacios == var_posc - 1 ){
		puts("Son todos espacios");
		return ST_VECTOR_DE_ESPACIOS;
	}
	if( var_aux == MAX_LARGO_PALABRA ){
		cadena_palabra[var_aux] = '\0';
	}
	else{
		puts("La palabra esta incompleta");
		return ST_ERROR_PALABRA_INCOMPLETA;
	}

	palabra_convertida_aux = strtol( cadena_palabra,&ptr_aux,10 );
	if( !palabra_convertida_aux ){
		for( var_aux = 0;cadena_palabra[var_aux] != '\0';var_aux++){
			if( cadena_palabra[var_aux] != '0' ){
				break;
			}
		}
		if( var_aux == MAX_LARGO_PALABRA ){
			puts("Ingreso el 0000");
			*palabra_convertida = 0;
			return ST_OK;
		}
		puts("Error al convertir la palabra");
		return ST_ERROR_PALABRA_NO_CONVERTIDA;
	}
	if( *ptr_aux != '\0' ){
		puts("Error la palabra no contiene solo numeros");
		return ST_ERROR_PALABRA_NO_NUMERICA;
	}
	*palabra_convertida = palabra_convertida_aux;
	printf("La palabra convertida es :%i\n",*palabra_convertida);
	return ST_OK;
}

