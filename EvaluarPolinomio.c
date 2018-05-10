#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CANTIDAD_COEF 3 /* (cant.._coef - 1) sera el grado del polinomio*/
#define MSJ_PRESENTACION_PROGR "Evaluar x0 en el polinomio a2 * X^2 + a1 *X^1 + a0"
#define MSJ_INGRESO_COEF_POLINOMIO "Ingrese el valor de el coeficiente"
#define MSJ_INGRESO_EVALUAR_POLINOMIO "Ingrese el valor donde evaluara el polinomio"
#define MSJ_RESULTADO_POL_EVALUADO "El valor del polinomio es"

#define MSJ_ERROR_PREFIJO "ERROR"
#define MSJ_ERROR_INGRESO "Ingreso invalido"

typedef enum{ ST_OK,ST_ERROR_INGRESO,
			  ST_EXP_NEGATIVO ,
			  ST_BUFFER_SUCIO} status_t;

status_t limpiar_buffer(void);
status_t potencia_positiva(double,int,double []);

int main(void)
{
    int var_conteo;
    double valor_polinomio , pol_evaluado;
    double potencia[1];
    double coef[CANTIDAD_COEF];

	puts(MSJ_PRESENTACION_PROGR);

	for(var_conteo = 0 ; var_conteo < CANTIDAD_COEF ; var_conteo++){

		/*Ingreso de coeficientes del polinomio*/
		printf("%s a%i:",MSJ_INGRESO_COEF_POLINOMIO,var_conteo);
		if( scanf("%lf",&coef[var_conteo] ) != 1){
			fprintf(stderr,"%s: %s\n",MSJ_ERROR_PREFIJO,MSJ_ERROR_INGRESO);
			return EXIT_FAILURE;
		}
		if( limpiar_buffer() == ST_BUFFER_SUCIO ){
			fprintf(stderr,"%s: %s\n",MSJ_ERROR_PREFIJO,MSJ_ERROR_INGRESO);
			return EXIT_FAILURE;
		}
	}

	/*Ingreso de valor donde sera evaluado el polinomio*/
	printf("%s:",MSJ_INGRESO_EVALUAR_POLINOMIO);
	if( scanf("%lf",&valor_polinomio) != 1){
		fprintf(stderr,"%s: %s\n",MSJ_ERROR_PREFIJO,MSJ_ERROR_INGRESO);
		return EXIT_FAILURE;
	}
	if( limpiar_buffer() == ST_BUFFER_SUCIO ){
		fprintf(stderr,"%s: %s\n",MSJ_ERROR_PREFIJO,MSJ_ERROR_INGRESO);
		return EXIT_FAILURE;
	}


	for(var_conteo = 0 , pol_evaluado = 0; var_conteo < CANTIDAD_COEF
			; var_conteo++){
		if(potencia_positiva(valor_polinomio,var_conteo,potencia) == ST_OK){
		   pol_evaluado += ( coef[var_conteo] * potencia[0] );
		}
		else{
			fprintf(stderr,"%s:%s\n",MSJ_ERROR_PREFIJO,MSJ_ERROR_INGRESO);
			return EXIT_FAILURE;
		}
	}

	printf("%s :%.4f\n",MSJ_RESULTADO_POL_EVALUADO,pol_evaluado);
	return EXIT_SUCCESS;
}


status_t limpiar_buffer(void)
{
	int caracter_no_leido_scanf , var_aux = 0;

	while( (caracter_no_leido_scanf = getchar()) != '\n'
		   && caracter_no_leido_scanf != EOF ){
		var_aux++;
	}
	if( var_aux == 0){
		return ST_OK;
	}
	else
		return ST_BUFFER_SUCIO;
}


/*solo puede calcular la potencia positiva de un numero*/
status_t potencia_positiva(double base , int exponente , double potencia[])
{
	size_t var_conteo;

	if( exponente < 0){
		return ST_EXP_NEGATIVO;
	}

	for(var_conteo = 0 , potencia[0] = 1 ; var_conteo < exponente ; var_conteo++){
		potencia[0] *= base;
	}

	return ST_OK;
}
