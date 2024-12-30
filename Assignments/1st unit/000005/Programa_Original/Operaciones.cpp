#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include "Operaciones.h"
Operaciones::Operaciones(){
}
Operaciones::Operaciones(Matriz m1){
	this->_matriz=m1;
}
void Operaciones::segmentar1(){
	int **matriz,j;
	matriz=(int**)malloc(_matriz.getDim()*sizeof(int*));
	for(j=0;j<_matriz.getDim();j++){
		*(matriz+j)=(int*)malloc(_matriz.getDim()*sizeof(int*));
	}
	_matriz.setMatriz1(matriz);
}
void Operaciones::segmentar2(){
	int **matriz,j;
	matriz=(int**)malloc(_matriz.getDim()*sizeof(int*));
	for(j=0;j<_matriz.getDim();j++){
		*(matriz+j)=(int*)malloc(_matriz.getDim()*sizeof(int*));
	}
	_matriz.setMatriz2(matriz);
}
void Operaciones::segmentarR(){
	int **matriz,j;
	matriz=(int**)malloc(_matriz.getDim()*sizeof(int*));
	for(j=0;j<_matriz.getDim();j++){
		*(matriz+j)=(int*)malloc(_matriz.getDim()*sizeof(int*));
	}
	_matriz.setMatrizR(matriz);
}
void Operaciones::encerar1(){
	for(int i=0;i<_matriz.getDim();i++){
		for(int j=0;j<_matriz.getDim();j++){
			*(*(_matriz.getMatriz1()+i)+j)=0;
		}		
	}
}
void Operaciones::encerar2(){
	for(int i=0;i<_matriz.getDim();i++){
		for(int j=0;j<_matriz.getDim();j++){
			*(*(_matriz.getMatriz2()+i)+j)=0;
		}		
	}
}
void Operaciones::encerarR(){
	for(int i=0;i<_matriz.getDim();i++){
		for(int j=0;j<_matriz.getDim();j++){
			*(*(_matriz.getMatrizR()+i)+j)=0;
		}		
	}
}
void Operaciones::procesarPot(int exp){
	for(int e=1;e<=exp;e++){
		for(int i=0;i<_matriz.getDim();i++){
			for(int j=0;j<_matriz.getDim();j++){
				for(int k=0;k<_matriz.getDim();k++){
					*(*(_matriz.getMatrizR()+i)+j)=*(*(_matriz.getMatrizR()+i)+j)+ 
					(*(*(_matriz.getMatriz2()+i)+k) * (*(*(_matriz.getMatriz2()+k)+j)));                				}
			}
		}
	}
}
void Operaciones::procesarMulti(){
	for(int i=0;i<_matriz.getDim();i++){
		for(int j=0;j<_matriz.getDim();j++){
			for(int k=0;k<_matriz.getDim();k++){
				*(*(_matriz.getMatrizR()+i)+j)=	*(*(_matriz.getMatrizR()+i)+j)+ (*(*(_matriz.getMatriz1()+i)+k)*(*(*(_matriz.getMatriz2()+k)+j)));
			}
		}
	}
}
void Operaciones::imprimir1(){
	printf("La matriz 1 es:\n");
	for(int i=0;i<_matriz.getDim();i++){
		for(int j=0;j<_matriz.getDim();j++){
			printf("%d",*(*(_matriz.getMatriz1()+i)+j));
			printf("%*s",j+5,"");
		}
		printf("\n");
	}
}
void Operaciones::imprimir2(){
	printf("\nLa matriz 2 es:\n");
	for(int i=0;i<_matriz.getDim();i++){
		for(int j=0;j<_matriz.getDim();j++){
			printf("%d",*(*(_matriz.getMatriz2()+i)+j));
			printf("%*s",j+5,"");
		}
		printf("\n");
	}
}
void Operaciones::imprimirR(){
	printf("\nLa matriz R es:\n");
	for(int i=0;i<_matriz.getDim();i++){
		for(int j=0;j<_matriz.getDim();j++){
			printf("%d",*(*(_matriz.getMatrizR()+i)+j));
			printf("%*s",j+5,"");
		}
		printf("\n");
	}
}
void Operaciones::generar1(){
	srand(time(NULL));
	int val;
	for(int i=0;i<_matriz.getDim();i++){
		for(int j=0;j<_matriz.getDim();j++)	{
			*(*(_matriz.getMatriz1()+i)+j)=rand()%3;
		}
	}
}

void Operaciones::generar2(){
	srand(time(NULL));
	for(int i=0;i<_matriz.getDim();i++){
		for(int j=0;j<_matriz.getDim();j++)	{
			*(*(_matriz.getMatriz2()+i)+j)=rand()%3;
		}
	}
}


int** Operaciones::generarMatriz(){
	srand(time(NULL));
	int val, **matriz;
	for(int i=0;i<_matriz.getDim();i++){
		for(int j=0;j<_matriz.getDim();j++)	{
			*(*(matriz+i)+j)=rand()%3;
		}
	}
	return matriz;
}

void Operaciones::imprimirEscalar(int **matriz){
	printf("\nLa matriz Parametrizada: \n");
	for(int i=0;i<_matriz.getDim();i++){
		for(int j=0;j<_matriz.getDim();j++){
			printf("%d",*(*(matriz+i)+j));
			printf("%*s",j+5,"");
		}
		printf("\n");
	}
}

void Operaciones::multiplicarEscalar(int **matriz){
	int dim =3;
	printf("\nLa matriz de 7:\n");
	//dim=_matriz.getDim();
	for(int i=0;i<dim;i++){
		for(int j=0;j<dim;j++){
				*(*(matriz+i)+j) = 7;
				printf("%d",*(*(matriz+i)+j));
				printf("%*s",j+5,"");
		}
		printf("\n");
	}
}
