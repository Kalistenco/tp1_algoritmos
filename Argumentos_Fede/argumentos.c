#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argumentos.h"

/*Crea el mensajero con los valores predeterminados*/
void inicializar_mensajero(struct mensajero * msj){

    /*No muestra la ayuda, a menos que se lo pida */
    msj->opcion_ayuda = VALOR_BOOL_DEFAULT;

    /*La entrada es por consola, a menos que se le pida por archivo */
    msj->entrada_archivo = VALOR_BOOL_DEFAULT;
    strcpy(msj->entrada_archivo_nombre , NOMBRE_DEFAULT);
    msj->entrada_tipo = TIPO_DEFAULT;

    /*La salida es por consola, a menos que se le pida por archivo*/
    msj->salida_archivo = VALOR_BOOL_DEFAULT;
    strcpy(msj->salida_archivo_nombre , NOMBRE_DEFAULT);
    msj->salida_tipo = TIPO_DEFAULT;

    /*La cantidad de memoria es 50, a menos que se le espeficique la cantidad por consola*/
    msj->cant_memoria = CANTIDAD_MEMORIA_DEFAULT;
}

bool_t argumentos_error_imprimir(status_arg_t estado){
    if( estado != OK){
        switch(estado){
            /*Mensajes de error relacionados con entrada/salida 1 */
            case ERROR_TIPO_SALIDA_NO_ESPECIFICADO:
                fprintf(stderr , "%s : %s" ,MSJ_ERROR ,MSJ_ARG_TIPO_SALIDA);
                break;
            case ERROR_TIPO_SALIDA_INV:
                fprintf(stderr , "%s : %s ", MSJ_ERROR , MSJ_ARG_TIPO_SALIDA_INV);
                break;
            case ERROR_NOMBRE_SALIDA_NO_ESPECIFICADO:
                fprintf(stderr , "%s : %s", MSJ_ERROR ,MSJ_ARG_NOMBRE_SALIDA);
                break;
            case ERROR_TIPO_ENTRADA_NO_ESPECIFICADO:
                fprintf(stderr , "%s : %s" , MSJ_ERROR ,MSJ_ARG_TIPO_ENTRADA);
                break;
            case ERROR_TIPO_ENTRADA_INV:
                fprintf(stderr , "%s : %s" ,MSJ_ERROR , MSJ_ARG_TIPO_ENTRADA_INV);
                break;
            case ERROR_NOMBRE_ENTRADA_NO_ESPECIFICADO:
                fprintf(stderr , "%s : %s" ,MSJ_ERROR ,MSJ_ARG_NOMBRE_ENTRADA);
                break;

            /*Mensaje de error relacionados con entrada/salida 2*/
            case ERROR_TIPO_SALIDA_NO_ESPECIFICADO2:
                fprintf(stderr , "%s : %s", MSJ_ERROR ,MSJ_ARG_TIPO_SALIDA2);
                break;
            case ERROR_NOMBRE_SALIDA_NO_ESPECIFICADO2:
                fprintf(stderr , "%s : %s", MSJ_ERROR, MSJ_ARG_NOMBRE_SALIDA2);
                break;
            case ERROR_TIPO_ENTRADA_NO_ESPECIFICADO2:
                fprintf(stderr , "%s : %s",MSJ_ERROR ,MSJ_ARG_TIPO_ENTRADA2);
                break;
            case ERROR_NOMBRE_ENTRADA_NO_ESPECIFICADO2:
                fprintf(stderr , "%s : %s", MSJ_ERROR , MSJ_ARG_NOMBRE_ENTRADA2);
                break;

            /*Mensajes de error relacionado con cantidad y argumentos invalidos */
            case ERROR_INV_ARGUMENTO:
                fprintf(stderr , "%s : %s" , MSJ_ERROR ,MSJ_ARG_INV);
                break;
            case ERROR_MUCHOS_ARGUMENTOS:
                fprintf(stderr , "%s : %s" ,MSJ_ERROR, MSJ_ARG_MUCHOS);
                break;
            
            /*Mensaje de error relacionado con la memoria */
            case ERROR_MEMORIA_NO_ESPECIFICADA:
                fprintf(stderr , "%s : %s" , MSJ_ERROR ,MSJ_ARG_MEMORIA_NO_ESPECIFICADA);
                break;
            case ERROR_MEMORIA_INV:
                fprintf(stderr , "%s : %s", MSJ_ERROR ,MSJ_ARG_MEMORIA_INV);
            case OK:
                break;
        }
        return FALSO;
    }
    else{
        return VERDADERO;
    }
}

/*Funcion que valida el que el nombre siguiente no sea un argumento */
bool_t validar_no_argumento(char * argv_lista[], int posicion){
    size_t j;

    for(j = 0; j < OPCIONES_ARG; j++){
        if(strcmp((argv_lista[posicion + 1]), argumentos_lista[j]) == 0){
            return FALSO;
        }
    }
    return VERDADERO;
}

/*Funcion que valida el tipo de archivo , si no encuentra un tipo adecuado de archivo, devuelve falso */
/*Si encuentra, a travez del contador devuelve cual es */
bool_t validar_tipo_archivo(char * argv_lista[] , int posicion ,size_t * contador){
    
    for(*contador = 0; *contador < OPCIONES_TIPO_ARCHIVO; (*contador)++){
        if(strcmp(argv_lista[posicion + 1], archivos_tipo_lista[*contador]) == 0){
            return VERDADERO;
        }
    }
    return FALSO;
}


/*Valida los argumentos del programa, si no hay ningun error, todas las opciones son guardadas en el struct mensajero */
status_arg_t validar_argumentos(int argc_cantidad , char * argv_lista[] , struct mensajero * mandar){
    size_t i , j;

    /* Si hay mas argumentos de los que deberia haber, devuelve error*/
    if(argc_cantidad > MAX_ARG){
        return ERROR_MUCHOS_ARGUMENTOS;
    }

    for(i = 1; i < argc_cantidad ; i++){

        /*En caso de que se usa el argumento -h */
        if(strcmp( argv_lista[i] , argumentos_lista[H]) == 0){
            mandar->opcion_ayuda = VERDADERO;
        }

        /*En caso de que se use el argumento -m y sus validaciones */
        else if(strcmp( argv_lista[i] , argumentos_lista[M]) == 0){
            /*Si es el ultimo argumento, significa que no le pasaron la cantidad de memoria */
            if( (i+1) == argc_cantidad){
                return ERROR_MEMORIA_NO_ESPECIFICADA;
            }

            /*Si  es 0 , significa que no se ingreso un numero , y si se ingreso un numero y es menor o igual a 0 , devuelve error */
            else if (atoi(argv_lista[i + 1]) == 0 || atoi(argv_lista[i + 1]) < 0 ){
                return ERROR_MEMORIA_INV;
            }

            else{
                mandar->cant_memoria = atoi(argv_lista[i + 1]);
                i++;
            }
        }

        /*En caso de que se use el argumento -i y sus validaciones */
        else if(strcmp( argv_lista[i], argumentos_lista[I]) == 0){
            
            /*Si encuentra que la palabra siguiente a -i es otro argumento o es el ultimo elemento de la lista , devuelve error
            porque faltaria el nombre del archivo , sino, copia el nombre al mensajero */
            if( (i +1) != argc_cantidad  && validar_no_argumento(argv_lista , i ) == VERDADERO){
                strcpy(mandar->entrada_archivo_nombre , argv_lista[i + 1]);
                mandar->entrada_archivo = VERDADERO;
                i++;
            }
            else{
                return ERROR_NOMBRE_ENTRADA_NO_ESPECIFICADO;
            }
        }

        /*En caso de que se use el argumento -if y sus validaciones */
        else if(strcmp( argv_lista[i] , argumentos_lista[IF]) == 0){
            
            /* Primero mira si despues del -if encuentra una palabra que no sea otro argumento o es el final de la cadena
            Si encuentra una cadena distina a un argumento , valida si esa cadena es un txt o bin
            Si no es txt ni bin , retorna error, sino, guarda en el mensajero la informacion */

            if((i + 1) == argc_cantidad || validar_no_argumento(argv_lista , i) == FALSO){
                return ERROR_TIPO_ENTRADA_NO_ESPECIFICADO;
            }

            else if((validar_tipo_archivo(argv_lista , i , &j)) == VERDADERO){
                mandar->entrada_tipo = (int) j;
                i++;
            }

            else{
                return ERROR_TIPO_ENTRADA_INV;
            }
        }

        /*En caso de que se use el argumento -o y sus validaciones*/
        else if(strcmp ( argv_lista[i] , argumentos_lista[O]) == 0){

            /*Si encuentra que la palabra siguiente a -o es otro argumento o es el final de la cadena , devuelve error
            porque faltaria el nombre del archivo , sino, copia el nombre al mensajero */

            if((i +1) != argc_cantidad   && validar_no_argumento(argv_lista, i) == VERDADERO){
                strcpy(mandar->salida_archivo_nombre , argv_lista[i + 1]);
                (mandar)->salida_archivo = VERDADERO;
                i++;
            }
            else{
                return ERROR_NOMBRE_SALIDA_NO_ESPECIFICADO;
            }
        }

        /*En caso de que se use el argumento -of y sus validaciones */
        else if(strcmp( argv_lista[i] , argumentos_lista[OF]) == 0){
            
             /* Primero mira si despues del -of encuentra una palabra que no sea otro argumento o que no sea el final de la cadena
            Si encuentra una cadena distina a un argumento , valida si esa cadena es un txt o bin
            Si no es txt ni bin , retorna error, sino, guarda en el mensajero la informacion */

            if((i + 1) == argc_cantidad || validar_no_argumento(argv_lista , i) == FALSO){
                return ERROR_TIPO_ENTRADA_NO_ESPECIFICADO;
            }
            
            else if(validar_tipo_archivo(argv_lista , i , &j) == VERDADERO){
                mandar->salida_tipo = (int) j;
                i++;
            }
            else{
                return ERROR_TIPO_SALIDA_INV;
            }
        }

        /*Si no coincide con ningun elemento de la lista de argumentos, devuelve error 
        Una vez que se valido correctamente un argumento, nunca se leeran las opciones de los argumentos (por es el i++ en validaciones anteriores)
        Ejemplo : nombre del archivo, tipo, cantidad de memoria etcetera */
        else{
            return ERROR_INV_ARGUMENTO;
        }
    }

    /*Manda error en caso de que se haya subido el nombre del achivo pero no el tipo
     Y en caso de que se haya subido el tipo del archivo pero no el nombre */
    if(mandar->entrada_archivo == VERDADERO && mandar->entrada_tipo == NO_ESPECIFICADO){
        return ERROR_TIPO_ENTRADA_NO_ESPECIFICADO2;
    }
    else if(mandar->entrada_archivo == FALSO && mandar->entrada_tipo != NO_ESPECIFICADO){
        return ERROR_NOMBRE_ENTRADA_NO_ESPECIFICADO2;
    }

    if(mandar->salida_archivo == VERDADERO && mandar->salida_tipo == NO_ESPECIFICADO){
        return ERROR_TIPO_SALIDA_NO_ESPECIFICADO2;
    }
    else if(mandar->salida_archivo == FALSO && mandar->salida_tipo != NO_ESPECIFICADO){
        return ERROR_NOMBRE_SALIDA_NO_ESPECIFICADO2;
    }

    /* Si todas las validaciones salen sin error, devuelve OK */
    return OK;
}

