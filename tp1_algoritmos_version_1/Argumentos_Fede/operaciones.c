#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operacions.h"



/*verifica que la posicion( los dos ultimos numeros de la palabra) este en rango*/
int verificar_posicion_memoria(int cantidad_memoria){
    int memoria = cabeza.lista_instrucciones[cabeza.index];
    memoria = memoria % 100;
/*como la memoria no puede ser negativa , retorna un valor negativo para decir qeu fallo*/
/*se puede leer hasta la posicion cant_memoria - 1*/
    if(memoria >= cantidad_memoria){
        return -1;
    }

    return memoria;
}


bool_t errores_instrucciones(status_op_t error){
    switch(error){
        case NO_HALT:
            fprintf(stderr , "%s : %s" ,MSJ_ERROR , MSJ_ERROR_OP_HALT);
            break;
        case NINGUN_CODIGO_CONOCIDO:
            fprintf(stderr , "%s : %s  %lu\n" , MSJ_ERROR , MSJ_ERROR_OP_CODIGO_NO_CONOCIDO ,cabeza.index);
            break;
        case POSICION_FUERA_DE_RANGO:
            fprintf(stderr , "%s : %s %lu \n",MSJ_ERROR ,MSJ_ERROR_OP_POSICION_FUERA_DE_RANGO , cabeza.index);
            break;
        case VALOR_INGRESADO_INV:
            fprintf(stderr , "%s : %s" ,MSJ_ERROR ,MSJ_ERROR_OP_VALOR_INGRESADO_INV);
            break;
  		case NO_SE_PUDO_LEER_VALOR:
			fprintf(stderr,"%s : %s", MSJ_ERROR, MSJ_NO_SE_PUDO_LEER_VALOR);
			break;
		case CANT_MEMORIA_CERO:
			fprintf(stderr,"%s : %s\n", MSJ_ERROR,MSJ_MEMORIA_INGRESADA_CERO);
			break;
		default:
			fprintf( stderr,"%s: %s\n", MSJ_ERROR , MSJ_ERROR_OPERACIONES );
    }

    printf("\n%s\n",MSJ_FINAL);

    return OK_OP;

}

status_op_t ejecutar_instrucciones(int cantidad_memoria){
    status_op_t estado;
    int posicion_asignada;
    int codigo;

    printf("\n%s\n", MSJ_INICIO);
    if( !cantidad_memoria ){
		return CANT_MEMORIA_CERO;
    }
    while( cabeza.index < cantidad_memoria ){

/*Si la operacion indica hacia memoria que esta fuera del rango, manda error */
		if((posicion_asignada = verificar_posicion_memoria(cantidad_memoria)) <= -1){
			return POSICION_FUERA_DE_RANGO;
		}

		codigo = cabeza.lista_instrucciones[cabeza.index] / 100;

        switch(codigo){
            /*Operaciones de entrada/salida */
            case OPERACION_LEER:
                estado = leer(posicion_asignada );
                /* En caso de que haya devueldo un error */
                if(estado != OK_OP){
/* me parece mas claro tener esto fuera de la funcion , por que queda mas claro que aumentas el index */
						return estado;
				}
				else{
                   cabeza.index++;
                }
                break;

            case OPERACION_ESCRIBIR:
                escribir(posicion_asignada);
                cabeza.index++;
                break;

            /*Operaciones de movimiento */
            case OPERACION_CARGAR:
                cargar(posicion_asignada);
                cabeza.index++;
                break;
            case OPERACION_GUARDAR:
                guardar(posicion_asignada);
                cabeza.index++;
                break;
            case OPERACION_PCARGAR:
                estado = pcargar(posicion_asignada);
                /*En caso de que haya devueldo un error */
                if(estado != OK_OP){
                    return estado;
                }
				cabeza.index++;
                break;
            case OPERACION_PGUARDAR:
                estado = pguardar(posicion_asignada);
                /*En caso de que haya devuelto un error*/
                if(estado != OK_OP){
                    return estado;
                }
			    cabeza.index++;
                break;

            /*Operaciones aritemticas */
            case OPERACION_SUMAR:
                suma(posicion_asignada);
                cabeza.index++;
                break;
            case OPERACION_RESTAR:
                resta(posicion_asignada);
				cabeza.index++;
                break;
            case OPERACION_DIVIDIR:
                division(posicion_asignada);
				cabeza.index++;
                break;
            case OPERACION_MULTIPLICAR:
                multiplicar(posicion_asignada);
				cabeza.index++;
                break;

            /*Operaciones de control */
            case OPERACION_JMP:
                jmp(posicion_asignada);
                break;
            case OPERACION_JMPNEG:
                jmpneg(posicion_asignada);
                break;
            case OPERACION_JMPZERO:
                jmpzero(posicion_asignada);
                break;
            case OPERACION_JNZ:
                jnz(posicion_asignada);
                break;
            case OPERACION_DJNZ:
                djnz(posicion_asignada);
                break;

            /*Termina el programa */
            case OPERACION_HALT:
                return OK_OP;
                break;

            default:
                printf("%s\n",MSJ_FINAL);
                return NINGUN_CODIGO_CONOCIDO;
        }
    }
	return OK_OP;
}

/*******************************************************************/
/*Operaciones de entrada/salida */
/*******************************************************************/

status_op_t leer( int posicion_asignada ){
    char * ptr_aux;
    char numero_ingresado[MAX_CANT_INGRESO_STDIN];
	int num_convertido;
	int var_aux;

    /*Lectura */
    printf("%s",MSJ_OPERACION_ESCRIBIR);

    if( !fgets(numero_ingresado , MAX_CANT_INGRESO_STDIN , stdin) ){
		return NO_SE_PUDO_LEER_VALOR;
    }
/*como ingrsa por stdin le borro el \n para no tener problemas mas adelante*/
	ptr_aux = strchr( numero_ingresado , '\n' );
/* si lo en cuentra , es decir no retorna NULL , entonces le pone el \0*/
	if( ptr_aux ){
		*ptr_aux = '\0';
	}
    /*Si no ingresa numeros, devuelve error */
    num_convertido = strtol( numero_ingresado,&ptr_aux,10 );

/*como strtol devuelve 0 si apareciera un error */
/*se tiene que validar que no se ingreso el 0 */
    if( !num_convertido ){
		for( var_aux = 0 ; numero_ingresado[var_aux] != '\0' ; var_aux++){
			if( numero_ingresado[var_aux] != '0' ){
/*si no es el 0 es por que hubo un error en strtol entonces para que se identifique ese error */
/*cargo a var_aux un valor incorrecto por ejemplo : */
				var_aux = -1;
				break;
			}
		}
/*si devuelve 0 (strtol) y la palabra no era 0000, entonces es un error*/
		if( var_aux == -1 ){
			return VALOR_INGRESADO_INV;
		}
/*si llega a este puento entonces ingreso el 0*/
    }

/*ahora valido que toda la cadena sea un numero */
/*comparo contra \0 por que puede ingresar un valor y cerrarle el flujo*/
	if( *ptr_aux != '\0' && *ptr_aux != '\n' ){
		return VALOR_INGRESADO_INV;
	}
	cabeza.lista_instrucciones[posicion_asignada] = num_convertido;
    return OK_OP;
}

void escribir(int posicion_asignada){

    printf("%s %i : %i \n",MSJ_OPERACION_LEER, posicion_asignada , cabeza.lista_instrucciones[posicion_asignada]);
	return;
}

/*******************************************************************/
/*Operacions de movimiento */
/*******************************************************************/

void cargar(int posicion_asignada){

    cabeza.acumulador = cabeza.lista_instrucciones[posicion_asignada];
	return;
}

void guardar(int posicion_asignada){

    cabeza.lista_instrucciones[posicion_asignada] = cabeza.acumulador;
	return;
}

status_op_t pcargar(int posicion_asignada){
    posicion_asignada = cabeza.lista_instrucciones[posicion_asignada] % 100;

    if( verificar_posicion_memoria(posicion_asignada) <= -1){
        return POSICION_FUERA_DE_RANGO;
    }

    cabeza.acumulador = cabeza.lista_instrucciones[posicion_asignada];

    return OK_OP;
}

status_op_t pguardar(int posicion_asignada){
    posicion_asignada = cabeza.lista_instrucciones[posicion_asignada] % 100;

    if(verificar_posicion_memoria(posicion_asignada) <= -1){
        return POSICION_FUERA_DE_RANGO;
    }

    cabeza.lista_instrucciones[posicion_asignada] = cabeza.acumulador;
    return OK_OP;
}
/*******************************************************************/
/*Operaciones aritmeticas */
/*******************************************************************/
void suma(int posicion_asignada){

    cabeza.acumulador = cabeza.acumulador + cabeza.lista_instrucciones[posicion_asignada];
	return;
}

void resta(int posicion_asignada){

    cabeza.acumulador = cabeza.acumulador - cabeza.lista_instrucciones[posicion_asignada];
	return;
}

void division(int posicion_asignada){

    cabeza.acumulador = cabeza.acumulador / cabeza.lista_instrucciones[posicion_asignada];
	return;
}

void multiplicar(int posicion_asignada){

    cabeza.acumulador = cabeza.acumulador * cabeza.lista_instrucciones[posicion_asignada];
	return;
}

/*******************************************************************/
/*Operaciones de control */
/*******************************************************************/
void jmp(int posicion_asignada){

    cabeza.index = posicion_asignada;
	return;
}

void jmpneg(int posicion_asignada){

    if(cabeza.acumulador < 0){
        cabeza.index = posicion_asignada;
    }
    else{
        cabeza.index++;
    }
	return;
}

void jmpzero(int posicion_asignada){

    if(cabeza.acumulador == 0){
        cabeza.index = posicion_asignada;
    }
    else{
        cabeza.index++;
    }
	return;
}

void jnz(int posicion_asignada){

    if(cabeza.acumulador != 0){
        cabeza.index = posicion_asignada;
    }
    else{
        cabeza.index++;
    }
	return;
}

void djnz(int posicion_asignada){

    cabeza.acumulador--;
    if(cabeza.acumulador != 0){
        cabeza.index = posicion_asignada;
    }
    else{
        cabeza.index++;
    }
	return;
}
/*
void prueba(int codigo, int posicion_asignada){
    int i;
    printf("******************************************\n");
    printf("\nIndex : %i\n", (int) cabeza.index);
    printf("Codigo : %i \n", codigo);
    printf("Acumulador : %i\n",cabeza.acumulador);
    printf("Posicion de memoria a acceder : %i \n", posicion_asignada);
    printf("Que hay en esa memoria : %i \n", cabeza.lista_instrucciones[posicion_asignada]);
    printf("******************************************\n");
    for(i = 0; i < 12 ; i++){
        printf("%i : %i \n", i , cabeza.lista_instrucciones[i]);
    }
    printf("******************************************\n");
}
*/
