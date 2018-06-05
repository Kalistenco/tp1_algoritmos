#include <stdio.h>
#include <stdlib.h>

#include "salida.h"


status_salida_t seleccionar_salida(struct mensajero * msj){
	status_salida_t estado_salida;

	if( !msj ){
		return ST_PUNTERO_SALIDA_NULO;
	}
    switch(msj->salida_tipo){
        case NO_ESPECIFICADO:
            salida_consola(msj->cant_memoria);
            break;
        case TXT:
			estado_salida = salida_archivo_texto(msj->cant_memoria , msj->salida_archivo_nombre);
            if(estado_salida != ST_SALIDA_OK){
                return estado_salida;
            }
            break;
        case BIN:
			estado_salida = salida_archivo_binario(msj->cant_memoria , msj->salida_archivo_nombre);
            if(estado_salida != ST_SALIDA_OK ){
                return estado_salida;
            }
/*aunque salida_tipo solo pueda tomar los 3 valores anteriores */
/* me parece una buena idea siempre tener un default */
        default:
			return ST_ERROR_TIPO_SALIDA_INCORRECTO;
    }
    return ST_SALIDA_OK;
}


void salida_consola(int cant_memoria){

    size_t i;

    printf("\n%15s:\n",MSJ_REGISTO_SALIDA);
    printf("%15s : %i\n", MSJ_ACUMULADOR_SALIDA , cabeza.acumulador);
    printf("%15s : %02lu\n",MSJ_INDEX_SALIDA , cabeza.index);
    printf("%15s : %+i\n",MSJ_INSTRUCCION_SALIDA , cabeza.lista_instrucciones[cabeza.index]);
    printf("%15s : %i\n", MSJ_OPCODE_SALIDA , cabeza.lista_instrucciones[cabeza.index] / 100);
    printf("%15s : %02i\n\n\n", MSJ_OPERANDO_SALIDA , cabeza.lista_instrucciones[cabeza.index] % 100);

    printf("%s\n", MSJ_MEMORIA_SALIDA);

    printf("%10s"," ");
    for(i = 0; i < 10;i++){
        printf("%10lu", i);
        if(i == 9){
            printf("\n");
        }
    }

    for(i = 0; i < cant_memoria; i++){
        if(i % 10 == 0){
            printf("\n");
            printf("%10lu", i);
        }

        printf("%10i", cabeza.lista_instrucciones[i]);
    }

    printf("\n");
	return;
}

status_salida_t salida_archivo_texto(int cant_memoria , char * nombre_archivo){

    size_t i;
    FILE * puntero_archivo;

	if( !nombre_archivo ){
		return ST_PUNTERO_SALIDA_NULO;
	}
    puntero_archivo = fopen(nombre_archivo ,"wt");

    if(puntero_archivo == NULL){
        return ST_ERROR_ABRIR_ARCHIVO_SALIDA;
    }

    fprintf(puntero_archivo ,"\n%15s:\n",MSJ_REGISTO_SALIDA );
    fprintf(puntero_archivo,"%15s : %i\n", MSJ_ACUMULADOR_SALIDA , cabeza.acumulador);
    fprintf(puntero_archivo,"%15s : %02lu\n",MSJ_INDEX_SALIDA , cabeza.index);
    fprintf(puntero_archivo, "%15s : %+i\n",MSJ_INSTRUCCION_SALIDA , cabeza.lista_instrucciones[cabeza.index]);
    fprintf(puntero_archivo , "%15s : %i\n", MSJ_OPCODE_SALIDA , cabeza.lista_instrucciones[cabeza.index] / 100);
    fprintf(puntero_archivo , "%15s : %02i\n\n\n", MSJ_OPERANDO_SALIDA , cabeza.lista_instrucciones[cabeza.index] % 100);

    fprintf(puntero_archivo, "%s\n", MSJ_MEMORIA_SALIDA);

    fprintf(puntero_archivo , "%10s"," ");
    for(i = 0; i < 10;i++){
        fprintf(puntero_archivo,"%10lu", i);
        if(i == 9){
            fprintf(puntero_archivo,"\n");
        }
    }

    for(i = 0; i < cant_memoria; i++){
        if(i % 10 == 0){
            fprintf(puntero_archivo,"\n");
            fprintf(puntero_archivo,"%10lu", i);
        }

        fprintf(puntero_archivo,"%10i", cabeza.lista_instrucciones[i]);
    }
/*si no puede cerrar el archivo , lo informa*/
    if( fclose(puntero_archivo) == EOF ){
		return ST_ERROR_CERRAR_ARCHIVO_SALIDA;
    }
    return ST_SALIDA_OK;
}

status_salida_t salida_archivo_binario(int cant_memoria , char * nombre_archivo){

    FILE * puntero_archivo;
    size_t i;
   int informacion;

	if( !nombre_archivo ){
		return ST_PUNTERO_SALIDA_NULO;
	}
    puntero_archivo = fopen(nombre_archivo ,"wb");

    if(puntero_archivo == NULL){
        return ST_ERROR_ABRIR_ARCHIVO_SALIDA;
    }
/*como se sabe que va a cargar un valor al archivo , se valida que no sea cero (fwrite)*/
    if( !fwrite(&cabeza.acumulador , sizeof(cabeza.acumulador), 1 ,puntero_archivo) ){
		return ST_ERROR_CARGAR_ARCHIVO_SALIDA;
    }
    if( fwrite(&cabeza.index,sizeof(cabeza.index),1,puntero_archivo) ){
		return ST_ERROR_CARGAR_ARCHIVO_SALIDA;
    }
    if( !fwrite(&cabeza.lista_instrucciones[cabeza.index], sizeof(cabeza.lista_instrucciones[cabeza.index]),1, puntero_archivo) ){
		return ST_ERROR_CARGAR_ARCHIVO_SALIDA;
    }

    informacion = cabeza.lista_instrucciones[cabeza.index] / 100 ;
    if( fwrite(&informacion, sizeof(cabeza.lista_instrucciones[cabeza.index]),1,puntero_archivo) ){
		return ST_ERROR_CARGAR_ARCHIVO_SALIDA;
    }

    informacion = cabeza.lista_instrucciones[cabeza.index] % 100;
    if( fwrite( &informacion , sizeof(cabeza.lista_instrucciones[cabeza.index]), 1, puntero_archivo) ){
		return ST_ERROR_CARGAR_ARCHIVO_SALIDA;
    }

    for(i = 0; i < cant_memoria ; i++){
        if( fwrite(&cabeza.lista_instrucciones[i], sizeof(cabeza.lista_instrucciones[i]),1, puntero_archivo) ){
			return ST_ERROR_CARGAR_ARCHIVO_SALIDA;
        }
    }
/* si no puede cerrar el archivo correctamente lo informa*/
    if( fclose(puntero_archivo) == EOF ){
		return ST_ERROR_CERRAR_ARCHIVO_SALIDA;
    }
    return ST_SALIDA_OK;

}

void imprimir_error_salida( status_salida_t estado_salida ){
	switch( estado_salida ){
		case ST_ERROR_TIPO_SALIDA_INCORRECTO:
			fprintf( stderr,"%s: %s\n", MSJ_ERROR_PREFIJO_SALIDA ,MSJ_ERROR_TIPO_SALIDA_INCORRECTO );
			break;
		case ST_ERROR_ABRIR_ARCHIVO_SALIDA:
			fprintf( stderr,"%s: %s\n", MSJ_ERROR_PREFIJO_SALIDA,MSJ_ERROR_ABRIR_ARCHIVO_SALIDA );
			break;
		case ST_ERROR_CARGAR_ARCHIVO_SALIDA:
			fprintf( stderr,"%s: %s\n",MSJ_ERROR_PREFIJO_SALIDA, MSJ_ERROR_CARGAR_ARCHIVO_SALIDA );
			break;
		case ST_ERROR_CERRAR_ARCHIVO_SALIDA:
			fprintf( stderr,"%s: %s\n",MSJ_ERROR_PREFIJO_SALIDA,MSJ_ERROR_CERRAR_ARCHIVO_SALIDA);
		default:
			fprintf( stderr,"%s:%s\n",MSJ_ERROR_PREFIJO_SALIDA , MSJ_ERROR_SALIDA );
	}
	return;
}

