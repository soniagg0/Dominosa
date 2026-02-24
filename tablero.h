#ifndef TABLERO_H
#define TABLERO_H
#include "fichero.h"
#define MAX 10
#define SIZE_NOMBRE_FICHERO 80

typedef struct
{
	int sud,est;
	int num;
}tcasilla; 

typedef struct{
	int num;
	int letra;
}tconexion;

typedef struct
{
	tcasilla m[MAX+2][MAX+3];
	tconexion c1, c2;
	int n,nf,nc;
	int conok,con_max; 
	
} tdominosa;

void mostrar_dominosa (tdominosa *d);
int leer_dominosa (tdominosa *d);

#endif

