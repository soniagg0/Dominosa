#include <stdio.h>
#include "fichero.h"
#include "colores.h"
#include "tablero.h"
#include "jugada.h"

int main() //Programa principal que finaliza si el número de fichero es incorrecto o al ganar el juego.
{
	int final = 0,i;
	tdominosa d;
		
	final=leer_dominosa(&d);
	if (final==0){
	mostrar_dominosa(&d);
        while(final==0){
		pedir_jugada(&d);
		verificar_jugada(&d);
		mostrar_dominosa(&d);
		final=verificar_final(&d);
       }
    
    printf("\nFELICIDADES! HAS RESUELTO ESTE DOMINOSA! B-)\n");
    }
}
