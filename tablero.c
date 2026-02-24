#include <stdio.h>
#include "fichero.h"
#include "colores.h"
#include "tablero.h"

int leer_dominosa (tdominosa *d) //Esta función inicializa el tablero creando la matriz, solamente si el fichero es correcto.
{
	int err, f, c, n,final=0;
	char nombre_fichero[SIZE_NOMBRE_FICHERO],esp;


	printf("Introduce el nombre del fichero: ");
	scanf("%s%*c", nombre_fichero);
	printf("\n");
	
	err = abrir_fichero(nombre_fichero);
	if (err != ABRIR_FICHERO_OK) {
		printf("ERROR: FICHERO NO ENCONTRADO.\n");
		printf("PUEDE QUE EL NOMBRE NO SEA EL CORRECTO O QUE ESTE EN OTRO DIRECTORIO.\n");
		final=1;
	} 
	else {
		d->n = leer_int_fichero();//doblemax
		d->nf = leer_int_fichero(); //Numero de filas
		d->nc = leer_int_fichero(); //Numero de columnas
		
		for (f=0; f<d->nf; f++) 
		{
			for (c=0; c<d->nc; c++){
				d->m[f][c].num= leer_int_fichero();
				d->m[f][c].sud=0;
				d->m[f][c].est=0;
			}
		}
	}

	
	d->con_max =(d->nf*d->nc)/2;//maximo número de conexiones posibles.
	d->conok = 0;//conexiones hechas.
	return final;
}


void mostrar_dominosa (tdominosa *d) //Esta función muestra el dominosa con las conexiones correspondientes.
{
		
	int f, c, i, conectado;
	char nombre_fichero[SIZE_NOMBRE_FICHERO],letra;
	for(f=0; f<=d->nf; f++)
			printf("   %d",f);
		printf("\n +");
		for(f=0; f<=d->nf; f++)
			printf("---+");
		printf("\n");
		
		letra='A';
		for (f=0; f<(d->nf); f++) {
			printf("%c| ",letra+f);
			for (c=0; c<d->nc; c++) {
				if(d->m[f][c].num==0){
					printf_color_num(-1);
				}
				else{
					printf_color_num(d->m[f][c].num);
				}
				
				if (d->m[f][c].est==1){
					printf("%d", d->m[f][c].num);
					printf_color_num(-1);
					printf("███");
				}
				else{
					printf("%d   ", d->m[f][c].num);
					printf_color_num(-1);
				}
				
				
			}
			printf("\n ");
			for(i=0;i<=d->nc;i++){
				if (d->m[f][i].sud==1&&i<d->nc){
					printf("+ ");
					printf("█ ");
				}
				else{
					printf("+   ");
				}
			}
			printf("\n");
		}
        
        conectado=0;
	for (f=0;f<d->nf;f++){
		for (c=0;c<d->nc;c++){
			if (d->m[f][c].sud!=0 || d->m[f][c].est!=0){
				conectado++; //aquí contamos las conexiones que se han hecho.
			}
		}
	}
	printf_color_negrita();
	printf("Conexiones: %d de %d\n",conectado,(d->nf*d->nc)/2);
	printf_color_num(-1);
	
	d->conok=conectado;
	
}
