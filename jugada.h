#ifndef JUGADA_H 
#define JUGADA_H
#define MAX 10
#include "tablero.h"

typedef struct{
	int num1, num2;
}tautomatic;

void pedir_jugada(tdominosa *d);
void verificar_jugada(tdominosa *d);
int verificar_final(tdominosa *d);

#endif

