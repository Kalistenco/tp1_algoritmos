#ifndef FUNCIONES_MATRIZ__H
#define FUNCIONES_MATRIZ__H 1
#ifndef CANT_MAX_COLUMS
#define CANT_MAX_COLUMS 5
#endif
#ifndef CANT_MAX_FILAS
#define CANT_MAX_FILAS 5
#endif
#ifndef MSJ_INGRESO_ELEMENTOS_MATRIZ
#define MSJ_INGRESO_ELEMENTOS_MATRIZ "Ingrese los elementos de la matriz en"
#endif

typedef enum{ST_OK ,
			 ST_PUNTERO_NULL ,
			 ST_BUFFER_SUCIO ,
			 ST_ERROR_INGRESO_ELEMENTOS ,
			 ST_RANGO_MATRIZ_INCALCULABLE ,
			 ST_RANGO_MATRIZ_INVALIDO} status_t;

status_t cargar_matriz( int (*ptr_matriz)[][CANT_MAX_COLUMS] , size_t cant_filas ,
						size_t cant_colums );

status_t determinante_matriz( int matriz[][CANT_MAX_FILAS] ,
							  int * determinante ,
							  size_t rango_matriz );

status_t calcular_traza_matriz( int matriz[][CANT_MAX_FILAS] ,
								int * ptr_traza , const size_t rango_matriz);

status_t limpiar_buffer(void);

#endif
