#include <stdio.h>
#include <stdlib.h>

/*x se inicializa en cero solo la primera vez que se llama a la funcion*/
void funcion(void) {
/*esta x solo es "visible" dentreo de esta funcion*/
	static int x = 0;
	x++;
	printf("%d\n", x);
/*cuando el programa sale de esta funcion x no se destruye*/
/*guarda el valor de x en este punto y tendra este mismo valor en el siguiente*/
/*llamado a la funcion*/
}

int main(void)
{
/*la primera vez que llame a la funcion x sera 0*/
/*por que asi se lo inicializo*/
	funcion();
/*las demas veces que se llame a la funcion , x guardara el valor que tenia*/
/*anteriormente , para este punto del programa x vale 1*/
	funcion();
	funcion();
	funcion();
	funcion();

	return EXIT_SUCCESS;
}
