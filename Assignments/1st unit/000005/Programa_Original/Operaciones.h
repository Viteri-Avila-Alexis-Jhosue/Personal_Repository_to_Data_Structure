#pragma once
#include "Matriz.h"
class Operaciones{
	public:
		Operaciones();
		Operaciones(Matriz);
		void segmentar1();
		void segmentar2();
		void segmentarR();
		void generar1();
		void generar2();
		int **generarMatriz();
		void encerar1();
		void encerar2();
		void encerarR();
		void procesarPot(int);
		void procesarMulti();
		void imprimir1();
		void imprimir2();
		void imprimirR();
		void multiplicarEscalar(int **);
		void imprimirEscalar(int **);
	private:
		Matriz _matriz;
};