
#define MAX_CANT_ARGUMENTOS 6
#define MAX_CANT_PALABRAS 50
#define MAX_CANT_FRMT 3

typedef enum{
	ST_OK ,
	ST_PUNTERO_NULO ,
	ST_ARGUMENTO_INVALIDO ,
	ST_FRMT_INCORRECTO,
	ST_ERROR_CANT_N,
	ST_ERROR_N_INGRESADO
}status_t;

typedef enum{
	FALSO ,
	VERDADERO
 }bool_t;

typedef enum{
	FRMT_BIN = 0 ,
	FRMT_TXT = 1,
	FRMT_INCORRECTO = 2
}frmt_if_of_t;

typedef enum{
	ARCHIVO = 0,
	STDIO = 1
}frmt_lectura_volcado_t;

typedef enum{
	ARG_H = 0 ,
	ARG_M = 1 ,
	ARG_I = 2,
	ARG_IF = 3 ,
	ARG_O = 4 ,
	ARG_OF = 5,
	ARG_INVALIDO = 6
}argumentos_t;

typedef struct diccionario_t{
	char * vtr_argumentos[MAX_CANT_ARGUMENTOS] ;
	char * vtr_parametro_if_of[MAX_CANT_FRMT] ;
}diccionario_t;

typedef struct parametro_argumentos_t{
	bool_t imprimir_ayuda ;
	size_t N ;
	frmt_lectura_volcado_t frmt_lectura ;
	frmt_lectura_volcado_t frmt_volcado ;
	frmt_if_of_t frmt_entrada ;
	frmt_if_of_t frmt_salida ;
}parametro_argumentos_t;


status_t validar_argumento( char *, argumentos_t *, diccionario_t * );
status_t validar_frmt_if_of( char * , frmt_if_of_t * , diccionario_t *);
void imprimir_error(status_t);
status_t cargar_frmt_if_of( frmt_if_of_t, parametro_argumentos_t *, argumentos_t );
void imprimir_ayuda(void);
status_t validar_cant_palabras( char * , long * );
