#include <stdio.h>
#include <stdlib.h>

int * busqueda_binaria(const int v[] , size_t n, int , size_t , size_t );
/*agrege el main para probar la funcion*/
int main(void)
{
	int vtr[] = { 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 , 12 , 13 ,14 ,15 };
	size_t izq = 0;
	size_t der = 14;
	int objetivo = 25;
	size_t n = 14;
	int * ptr_posicion_objetivo;

	ptr_posicion_objetivo = busqueda_binaria(vtr , n , objetivo , izq , der);
	if( ptr_posicion_objetivo == NULL){
		puts("EL valor no se encuentra en el arreglo");
		return EXIT_FAILURE;
	}
	printf("%s: %i\n","El objetivo buscado fue",*ptr_posicion_objetivo);

	return EXIT_SUCCESS;
}

/*esta es la funcion que pide el ejercicio*/
int * busqueda_binaria(const int v[] , size_t n , int objetivo , size_t izq , size_t der){
	size_t posicion_medio;
	int * ptr_objetivo;

	if( objetivo == v[ posicion_medio = ( izq + der )/2 ] ){
		ptr_objetivo = (int *)( v + posicion_medio );
	}
	else if( objetivo < v[posicion_medio]  && objetivo >  v[izq] ){
		ptr_objetivo = busqueda_binaria(v,n,objetivo,izq ,posicion_medio - 1);
	}
	else if( objetivo > v[posicion_medio]  && objetivo < v[der] ){
		ptr_objetivo = busqueda_binaria(v,n,objetivo,izq + 1,posicion_medio);
	}
	else{
		ptr_objetivo = NULL;
	}
	return ptr_objetivo;
}
