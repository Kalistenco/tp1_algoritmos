#ifndef ARGUMENTOS__H1
#define ARGUMENTOS__H1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tipos.h"


/*Mensajes error entrada/salida 1 */
#define MSJ_ARG_TIPO_ENTRADA " -if :  No se especificto tipo de archivo de entrada\n"
#define MSJ_ARG_TIPO_ENTRADA_INV "-if : Invalido valor de tipo de archivo de entrada\n"
#define MSJ_ARG_NOMBRE_ENTRADA "-i : No se especifico nombre del archivo de entrada\n"


#define MSJ_ARG_TIPO_SALIDA " -of : No se especifico tipo de archivo de salida\n"
#define MSJ_ARG_TIPO_SALIDA_INV "-of : Invalido valor del tipo de archivo de salida\n"
#define MSJ_ARG_NOMBRE_SALIDA " -o : No se especifico el nombre del archivo de salida\n"

/*Mensajes error entrada/salida 2*/
#define MSJ_ARG_TIPO_SALIDA2 "se especifico el nombre del archivo de salida, pero no su tipo con -of\n"
#define MSJ_ARG_NOMBRE_SALIDA2 "se especifico el tipo del archivo de salida, pero no el nombre con -o\n"
#define MSJ_ARG_TIPO_ENTRADA2 "se especifico el nombre del archivo de entrada, pero no su tipo con -if\n"
#define MSJ_ARG_NOMBRE_ENTRADA2 "se especifico el tipo del archivo de entrada , pero no el nombre con -i\n"

/*Mensajes error memoria */
#define MSJ_ARG_MEMORIA_NO_ESPECIFICADA " -m : No se especifico la cantidad de memoria a asignar\n"
#define MSJ_ARG_MEMORIA_INV " -m : Se ingreso un valor invalido\n"

/*Mensajes de error Cantidad de argumentos/argumento invalido */
#define MSJ_ARG_MUCHOS " se han ingresado mas argumentos de lo permitido\n"
#define MSJ_ARG_INV " se ha ingresado un argumento invalido\n"

/*Mensajedes de la funcion ayuda */
#define MSJ_ARG_AYUDA_INICIO "*********AYUDA*********"
#define MSJ_ARG_AYUDA_H "-h  -- Muetra la ayuda"
#define MSJ_ARG_AYUDA_M "-m  -- Numero Cantidad de memoria que usara el programa"
#define MSJ_ARG_AYUDA_I "-i -- Nombre de archivo EL programa leera el archivo pasado , en caso contrario, de stdin"
#define MSJ_ARG_AYUDa_IF "-if bin/txt -- Tipo del archivo de entrada : binario/texto"
#define MSJ_ARG_AYUDA_O "-o Nombre de archivo -- La salida se hara en el archivo pasado , en caso contrariom desde stdout"
#define MSJ_ARG_AYUDA_OF "-of bin/txt -- Tipo del archivo de salida : binario/texto"
#define MSJ_ARG_AYUDA_FIN "*********FIN DE AYUDA*********"

/*Cantidad maxima de argumentos */
#define MAX_ARG 12

/*Extension de los archivos de entrada esperados */
#define ARCHIVO_ENTRADA_EXTENSION_TXT ".lms"
#define ARCHIVO_ENTRADA_EXTENSION_BIN ".bin"


/*Valores DEFAULT del mensajero */
#define NOMBRE_DEFAULT " "
#define TIPO_DEFAULT NO_ESPECIFICADO
#define VALOR_BOOL_DEFAULT FALSO
#define CANTIDAD_MEMORIA_DEFAULT 50

/*Cantidad de argumentos en diccionario*/
#define OPCIONES_ARG 6

/*Diccionario de argumentos que acepta el programa */
/*OPCIONES_ARG = Cantidad de argumentos, si se modifica biblioteca, modificar cantidad */
static const char * const argumentos_lista[] = {"-h" ,"-m" , "-i" , "-if" , "-o" , "-of" };
enum argumentos_index {
    ARG_H = 0,
    ARG_M = 1,
    ARG_I = 2,
    ARG_IF = 3,
    ARG_O = 4,
    ARG_OF = 5
};


/*Enum para registrar errores relacionados con la validacion de argumentos */
typedef enum status_arg {
    ERROR_TIPO_SALIDA_NO_ESPECIFICADO,
    ERROR_TIPO_SALIDA_INV,
    ERROR_NOMBRE_SALIDA_NO_ESPECIFICADO,
    ERROR_INV_ARGUMENTO,
    ERROR_TIPO_ENTRADA_NO_ESPECIFICADO,
    ERROR_TIPO_ENTRADA_INV,
    ERROR_NOMBRE_ENTRADA_NO_ESPECIFICADO,
    ERROR_TIPO_SALIDA_NO_ESPECIFICADO2,
    ERROR_NOMBRE_SALIDA_NO_ESPECIFICADO2,
    ERROR_TIPO_ENTRADA_NO_ESPECIFICADO2,
    ERROR_NOMBRE_ENTRADA_NO_ESPECIFICADO2,
    ERROR_MUCHOS_ARGUMENTOS,
    ERROR_MEMORIA_NO_ESPECIFICADA,
    ERROR_MEMORIA_INV,
    OK
}status_arg_t;


/*Inicializa el mensajero con los valores predeterminados */
void inicializar_mensajero(struct mensajero * x);

/*Impresion de errores */
bool_t argumentos_error_imprimir(status_arg_t estado);

/*Funciones relacionadas con la validacion de argumentos */
bool_t validar_no_argumento(char * argv_lista[], int posicion );
bool_t validar_tipo_archivo(char * argv_lista[] , int posicion , size_t * contador);
status_arg_t validar_argumentos(int argc_cantidad , char * argv_lista[], struct mensajero * mandar);

/*Imprime la ayuda */
void imprimir_ayuda();

#endif