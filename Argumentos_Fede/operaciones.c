#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operacions.h"




int verificar_posicion_memoria(int cantidad_memoria){
    int memoria = cabeza.lista_instrucciones[cabeza.index];
    memoria = memoria % 100;

    if(memoria > cantidad_memoria){
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
            fprintf(stderr , "%s : %s  %i\n" , MSJ_ERROR , MSJ_ERROR_OP_CODIGO_NO_CONOCIDO , (int) cabeza.index);
            break;
        case POSICION_FUERA_DE_RANGO:
            fprintf(stderr , "%s : %s %i \n",MSJ_ERROR ,MSJ_ERROR_OP_POSICION_FUERA_DE_RANGO ,(int) cabeza.index);
            break;
        case VALOR_INGRESADO_INV:
            fprintf(stderr , "%s : %s" ,MSJ_ERROR ,MSJ_ERROR_OP_VALOR_INGRESADO_INV);
            break;
        case OK_OP:
            printf("%s \n",MSJ_FINAL);
            return VERDADERO;
            break;
    }

    printf("%s \n",MSJ_FINAL);
    return FALSO;
}
status_op_t ejecutar_instrucciones(int cantidad_memoria){
    status_op_t estado;
    int posicion_asignada;
    int codigo;

    printf("%s \n", MSJ_INICIO);
    while(1){

    /*Si la operacion indica hacia memoria que esta fuera del rango, manda error */
    if((posicion_asignada = verificar_posicion_memoria(cantidad_memoria)) <= -1){
        return POSICION_FUERA_DE_RANGO;
    }

    codigo = cabeza.lista_instrucciones[cabeza.index] / 100;

     

        switch(codigo){
            /*Operaciones de entrada/salida */
            case OPERACION_LEER:
                estado = leer(posicion_asignada);
                /*En caso de que haya devueldo un error */
                if(estado != OK_OP){
                    return estado;
                }

                break;
            case OPERACION_ESCRIBIR:
                escribir(posicion_asignada);
                break;
            
            /*Operaciones de movimiento */
            case OPERACION_CARGAR:
                cargar(posicion_asignada);
                break;
            case OPERACION_GUARDAR:
                guardar(posicion_asignada);
                break;
            case OPERACION_PCARGAR:
                estado = pcargar(posicion_asignada);
                /*En caso de que haya devueldo un error */
                if(estado != OK_OP){
                    return estado;
                }

                break;
            case OPERACION_PGUARDAR:
                estado = pguardar(posicion_asignada);
                /*En caso de que haya devuelto un error*/
                if(estado != OK_OP){
                    return estado;
                }

                break;

            /*Operaciones aritemticas */
            case OPERACION_SUMAR:
                suma(posicion_asignada);
                break;
            case OPERACION_RESTAR:
                resta(posicion_asignada);
                break;
            case OPERACION_DIVIDIR:
                division(posicion_asignada);
                break;
            case OPERACION_MULTIPLICAR:
                multiplicar(posicion_asignada);
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
                printf("%s \n",MSJ_FINAL);
                break;
        }

        if(cabeza.index > cantidad_memoria){
            return NO_HALT;
        }
    }
}

/*******************************************************************/
/*Operaciones de entrada/salida */
/*******************************************************************/

status_op_t leer(int posicion_asignada){
    char * puntero;
    char numero_ingresado[20];

    /*Lectura */
    printf("%s",MSJ_OPERACION_ESCRIBIR);
    fgets(numero_ingresado , 20 , stdin);

    /*Si no ingresa numeros, devuelve error */
    if((strtol(numero_ingresado,&puntero,10) == 0 && *puntero != '\n')){
        return VALOR_INGRESADO_INV;
    }
    else if(*puntero != '\n'){
        return VALOR_INGRESADO_INV;
    }   
    
    cabeza.lista_instrucciones[posicion_asignada] = strtol(numero_ingresado,&puntero,10);
    cabeza.index++;

    return OK_OP;
}

void escribir(int posicion_asignada){

    printf("%s %i : %i \n",MSJ_OPERACION_LEER, posicion_asignada , cabeza.lista_instrucciones[posicion_asignada]);

    cabeza.index++;
}

/*******************************************************************/
/*Operacions de movimiento */
/*******************************************************************/

void cargar(int posicion_asignada){

    cabeza.acumulador = cabeza.lista_instrucciones[posicion_asignada];
    
    cabeza.index++;
}

void guardar(int posicion_asignada){

    cabeza.lista_instrucciones[posicion_asignada] = cabeza.acumulador;

    cabeza.index++;
}

status_op_t pcargar(int posicion_asignada){
    posicion_asignada = cabeza.lista_instrucciones[posicion_asignada] % 100;

    if( verificar_posicion_memoria(posicion_asignada) <= -1){
        return POSICION_FUERA_DE_RANGO;
    }

    cabeza.acumulador = cabeza.lista_instrucciones[posicion_asignada];
    cabeza.index++;

    return OK_OP;
}

status_op_t pguardar(int posicion_asignada){
    posicion_asignada = cabeza.lista_instrucciones[posicion_asignada] % 100;

    if(verificar_posicion_memoria(posicion_asignada) <= -1){
        return POSICION_FUERA_DE_RANGO;
    }

    cabeza.lista_instrucciones[posicion_asignada] = cabeza.acumulador;
    cabeza.index++;

    return OK_OP;
}
/*******************************************************************/
/*Operaciones aritmeticas */
/*******************************************************************/
void suma(int posicion_asignada){

    cabeza.acumulador = cabeza.acumulador + cabeza.lista_instrucciones[posicion_asignada];

    cabeza.index++;
}

void resta(int posicion_asignada){

    cabeza.acumulador = cabeza.acumulador - cabeza.lista_instrucciones[posicion_asignada];

    cabeza.index++;
}

void division(int posicion_asignada){

    cabeza.acumulador = cabeza.acumulador / cabeza.lista_instrucciones[posicion_asignada];

    cabeza.index++;
}

void multiplicar(int posicion_asignada){

    cabeza.acumulador = cabeza.acumulador * cabeza.lista_instrucciones[posicion_asignada];

    cabeza.index++;
}

/*******************************************************************/
/*Operaciones de control */
/*******************************************************************/
void jmp(int posicion_asignada){

    cabeza.index = posicion_asignada;

}

void jmpneg(int posicion_asignada){
    
    if(cabeza.acumulador < 0){
        cabeza.index = posicion_asignada;
    }
    else{
        cabeza.index++;
    }

}

void jmpzero(int posicion_asignada){

    if(cabeza.acumulador == 0){
        cabeza.index = posicion_asignada;
    }
    else{
        cabeza.index++;
    }

}

void jnz(int posicion_asignada){

    if(cabeza.acumulador != 0){
        cabeza.index = posicion_asignada;
    }
    else{
        cabeza.index++;
    }

}

void djnz(int posicion_asignada){

    cabeza.acumulador--;
    if(cabeza.acumulador != 0){
        cabeza.index = posicion_asignada;
    }
    else{
        cabeza.index++;
    }

}

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