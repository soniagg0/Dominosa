#include <stdio.h>
#include "fichero.h"
#include "jugada.h"
#include "colores.h"

void pedir_jugada(tdominosa *d)//Esta función pide el numero y letra de las casillas que serán conectadas/desconectadas.
{
	int aux=1, espai;
	char l1, l2;
	
	do{
		printf_color_negrita();
		printf("\nCasillas a conectar/desconectar (ej: [A0B0]):\n");
		scanf("%c%d%c%d%*c", &l1, &d->c1.num, &l2, &d->c2.num);
		//pasamos la letra de mayúscula a minúscula.
		if(l1>='a' && l1<='z') l1= l1-('a'-'A');
		if(l2>='a' && l2<='z') l2= l2-('a'-'A');
		//pasamos la letra mayúscula a número.
		if(l1>='A' && l1<='Z'){d->c1.letra= l1-'A';}
		if(l2>='A' && l2<='Z'){d->c2.letra= l2-'A';}
		//comprobamos que la conexión esta dentro del rago.
		if((d->c1.letra>=0 && d->c1.letra<(d->nf)) && (d->c1.num>=0 && d->c1.num<(d->nc))
		&& (d->c2.letra>=0 && d->c2.letra<(d->nf)) && (d->c2.num>=0 && d->c2.num<(d->nc)))
		{
			//verificamos que la conexion sea posible (distancia entre casillas ej.no diagonal). 
			if((d->c1.letra==d->c2.letra) && ((d->c1.num-d->c2.num)==1||(d->c2.num-d->c1.num)==1)||((d->c1.num==d->c2.num)&&((d->c1.letra-d->c2.letra)==1||((d->c2.letra-d->c1.letra)==1))))
				aux=0;
			else
				{printf("Conexion incorrecta, intentelo de nuevo."); aux=1;}
		}
		
		else
		{printf("Fuera del rango, intentelo de nuevo."); aux=1;}
		
	}while(aux);

}

void verificar_jugada(tdominosa *d)//Esta función hace la conexión entere las casillas correspondientes.
{
	int aux;
	
	//comprobamos si se trata de una conexión este y colocamos el orden correcto.
	if(d->c1.letra==d->c2.letra){
		if (d->c1.num>d->c2.num){
			aux=d->c1.num;
			d->c1.num=d->c2.num;
			d->c2.num=aux;
		
		}
		if (d->m[d->c1.letra][d->c1.num].est==1){
		//desconectar
			d->m[(d->c1.letra)][(d->c1.num)].est=0;
		}
		else{//conectar
			//primero desconectamos las casillas que interfieran con la nueva conexión.
			d->m[d->c1.letra][d->c1.num-1].est=0;
			d->m[d->c1.letra-1][d->c1.num].sud=0;
			d->m[d->c1.letra][d->c1.num].sud=0;
			d->m[d->c2.letra-1][d->c2.num].sud=0;
			d->m[d->c2.letra][d->c2.num].est=0;
			d->m[d->c2.letra][d->c2.num].sud=0;
			//conectamos las casillas correspondientes.
			d->m[d->c1.letra][d->c1.num].est=1;
		}
	}
	else{
		//comprobamos si se trata de una conexión sud y colocamos el orden correcto.
		if (d->c1.letra>d->c2.letra){
			aux=d->c1.letra;
			d->c1.letra=d->c2.letra;
			d->c2.letra=aux;
		}
		if (d->m[d->c1.letra][d->c1.num].sud==1){
		//desconectar
			d->m[(d->c1.letra)][(d->c1.num)].sud=0;
		}
		else{//conectar
				//primero desconectamos las casillas que interfieran con la nueva conexión.
			d->m[d->c1.letra][d->c1.num-1].est=0;
			d->m[d->c1.letra-1][d->c1.num].sud=0;
			d->m[d->c2.letra-1][d->c2.num].sud=0;
			d->m[d->c2.letra][d->c2.num-1].est=0;
			d->m[d->c2.letra][d->c2.num].est=0;
			d->m[d->c2.letra][d->c2.num].sud=0;
			d->m[d->c1.letra][d->c1.num].est=0;
			//conectamos las casillas correspondientes.
			d->m[(d->c1.letra)][(d->c1.num)].sud=1;
		}
	}
}

int verificar_final (tdominosa *d) //verificamos si ha ganado el juego.
{
	int i, j, f, c, final=0;
	int ok=0, suma=0, repetidos=0;
	tautomatic v[d->con_max];
	int elem=0;
	//miramos si las conexiones hechas son igual que las conexiones máximas (condición necesaria para ganar el juego).
	if(d->conok==(d->nf*d->nc)/2){
	for (f=0; f<d->nf; f++) //recorremos toda la matriz llenando un vector con structs de los numeros que estan conectados.
	{
		for (c=0; c<d->nc; c++){
			if(d->m[f][c].est==1 && c<(d->nc-1)){
				v[elem].num1= d->m[f][c].num;
				v[elem].num2= d->m[f][c+1].num;
				elem++;
			}
			else if(d->m[f][c].sud==1 && f<(d->nf-1)){
				v[elem].num1= d->m[f][c].num;
				v[elem].num2= d->m[f+1][c].num;
				elem++;
			}
		}
	}
	//recorremos el vector contando los numeros repetidos.
	for (i=0; i<elem;i++){
		for(j=i;j<elem;j++){
			if (((v[i].num1 == v[j].num1) && (v[i].num2 == v[j].num2)) || ((v[i].num2 == v[j].num1) && (v[i].num1 == v[j].num2))){
				repetidos++;
			}
		}
	}
		

				
		if(repetidos==d->con_max)//como cada vector se compara con todos (incluido él mismo), el número de repetidos debe ser igual al número de conexiones máximas y devolvemos la instrucción que permitirà mostrar que ha ganado el juego.
			final=1;
					}
							

	return final;
}


