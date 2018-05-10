#ifndef CLASIFICACION_ESPECTRAL_H
#define CLASIFICACION_ESPECTRAL_H 1

#define MIN_TEMP_CLASES 1700
#define MAX_TEMP_CLASE_M 3200
#define MAX_TEMP_CLASE_K 4600
#define MAX_TEMP_CLASE_G 5700
#define MAX_TEMP_CLASE_F 7100
#define MAX_TEMP_CLASE_A 9600
#define MAX_TEMP_CLASE_B 28000
#define MAX_TEMP_CLASE_O 50000

#define COLOR_CLASE_M "Rojo"
#define COLOR_CLASE_K "Naranja"
#define COLOR_CLASE_G "Amarillo"
#define COLOR_CLASE_F "Blanco amarillento"
#define COLOR_CLASE_A "Blanco"
#define COLOR_CLASE_B "Blanco azulado"
#define COLOR_CLASE_O "Azul"

#define MSJ_INGRESO_TEMP "Ingrese la temperatura de la estrella"
#define MSJ_CLASE_NO_DEFINIDA "No hay clase definida para el valor ingresado"
#define MSJ_IMPRIMIR_COLOR_CLASE "El color de la clase ingresada es"

#define MSJ_ERROR_PREFIJO "Error"
#define MSJ_ERROR_TEMP_NEGATIVA "La temperatura ingresada no puede ser negativa"
#define MSJ_ERROR_INGRESO_TEMP "La temperatura ingresada no es correcta"

typedef enum{ ST_SALIR,
			  ST_OK,
			  ST_BUFFER_SUCIO} estado_t;

/*Debe seguir un orden crecinte para cada clase */
/*el valor asignado a cada clase debe coincidir con la posicion de su valor maximo*/
/*en el vector vtr_temp_limite_max_clases*/
typedef enum{ CLASE_M = 1,
			  CLASE_K = 2,
			  CLASE_G = 3,
			  CLASE_F = 4,
			  CLASE_A = 5,
			  CLASE_B = 6,
			  CLASE_O = 7} espectral_t;

estado_t limpiar_buffer(void);

#endif
