#include <stdio.h>
#include <stdlib.h>

#include "salida.h"


bool_t seleccionar_salida(struct mensajero * msj){
    switch(msj->salida_tipo){
        case NO_ESPECIFICADO:
            salida_consola(msj->cant_memoria);
            break;
        case TXT:
            if(salida_archivo_texto(msj->cant_memoria , msj->salida_archivo_nombre) == FALSO){
                fprintf(stderr , "%s : %s ", MSJ_ERROR ,MSJ_ERROR_SALIDA);
                return FALSO;
            }
            break;
        case BIN:
            if(salida_archivo_binario(msj->cant_memoria , msj->salida_archivo_nombre) == FALSO){
                fprintf(stderr , "%s : %s ", MSJ_ERROR ,MSJ_ERROR_SALIDA);
                return FALSO;
            }
            break;
    }
    return VERDADERO;
}

void salida_consola(int cant_memoria){
    size_t i;

    printf("%15s",MSJ_REGISTO_SALIDA);
    printf("%15s  %i\n", MSJ_ACUMULADOR_SALIDA ,(int) cabeza.acumulador);
    printf("%15s  %i\n",MSJ_INDEX_SALIDA , (int) cabeza.index);
    printf("%15s  +%i\n",MSJ_INSTRUCCION_SALIDA , cabeza.lista_instrucciones[cabeza.index]);
    printf("%15s  %i\n", MSJ_OPCODE_SALIDA , cabeza.lista_instrucciones[cabeza.index] / 100);
    printf("%15s  %i\n\n", MSJ_OPERANDO_SALIDA , cabeza.lista_instrucciones[cabeza.index] % 100);

    printf("%s\n", MSJ_MEMORIA_SALIDA);

    printf("%10s"," ");
    for(i = 0; i < 10;i++){
        printf("%10i", (int)i);
        if(i == 9){
            printf("\n");
        }
    }

    for(i = 0; i < cant_memoria; i++){
        if(i % 10 == 0){
            printf("\n");
            printf("%10i", (int) i);
        }

        printf("%10i", cabeza.lista_instrucciones[i]);
    }

    printf("\n");

}

bool_t salida_archivo_texto(int cant_memoria , char * nombre_archivo){
    size_t i;
    FILE * puntero_archivo;

    puntero_archivo = fopen(nombre_archivo ,"wt");

    if(puntero_archivo == NULL){
        return FALSO;
    }

    fprintf(puntero_archivo ,"%15s",MSJ_REGISTO_SALIDA );
    fprintf(puntero_archivo,"%15s : %i\n", MSJ_ACUMULADOR_SALIDA ,(int) cabeza.acumulador);
    fprintf(puntero_archivo,"%15s : %i\n",MSJ_INDEX_SALIDA , (int) cabeza.index);
    fprintf(puntero_archivo, "%15s : +%i\n",MSJ_INSTRUCCION_SALIDA , cabeza.lista_instrucciones[cabeza.index]);
    fprintf(puntero_archivo , "%15s : %i\n", MSJ_OPCODE_SALIDA , cabeza.lista_instrucciones[cabeza.index] / 100);
    fprintf(puntero_archivo , "%15s : %i\n\n", MSJ_OPERANDO_SALIDA , cabeza.lista_instrucciones[cabeza.index] % 100);

    fprintf(puntero_archivo, "%s\n", MSJ_MEMORIA_SALIDA);

    fprintf(puntero_archivo , "%10s"," ");
    for(i = 0; i < 10;i++){
        fprintf(puntero_archivo,"%10i", (int)i);
        if(i == 9){
            fprintf(puntero_archivo,"\n");
        }
    }

    for(i = 0; i < cant_memoria; i++){
        if(i % 10 == 0){
            fprintf(puntero_archivo,"\n");
            fprintf(puntero_archivo,"%10i", (int) i);
        }

        fprintf(puntero_archivo,"%10i", cabeza.lista_instrucciones[i]);
    }

    fclose(puntero_archivo);
    return VERDADERO;

}

bool_t salida_archivo_binario(int cant_memoria , char * nombre_archivo){
    FILE * puntero_archivo;
    size_t i;
    int * puntero_informacion = (int *) malloc(sizeof(int));

    puntero_archivo = fopen(nombre_archivo ,"wb");

    if(puntero_archivo == NULL){
        return FALSO;
    }
    fwrite(&cabeza.acumulador , sizeof(cabeza.acumulador), 1 ,puntero_archivo);
    fwrite(&cabeza.index,sizeof(cabeza.index),1,puntero_archivo);
    fwrite(&cabeza.lista_instrucciones[cabeza.index], sizeof(cabeza.lista_instrucciones[cabeza.index]),1, puntero_archivo);

    *puntero_informacion = cabeza.lista_instrucciones[cabeza.index] / 100 ;
    fwrite(puntero_informacion, sizeof(cabeza.lista_instrucciones[cabeza.index]),1,puntero_archivo);

    *puntero_informacion = cabeza.lista_instrucciones[cabeza.index] % 100;
    fwrite(puntero_informacion , sizeof(cabeza.lista_instrucciones[cabeza.index]), 1, puntero_archivo);

    for(i = 0; i < cant_memoria ; i++){
        fwrite(&cabeza.lista_instrucciones[i], sizeof(cabeza.lista_instrucciones[i]),1, puntero_archivo);
    }

    fclose(puntero_archivo);
    free(puntero_informacion);
    return VERDADERO;

}