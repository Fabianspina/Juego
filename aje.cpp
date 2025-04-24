#include <windows.h>
#include <iostream>
using namespace std;
/**** Abreviaturas para los muchos datos individuales ****
***** que se sacan por pantalla                       ****
***** A su vez marca sirve para establecer una línea  ****
***** en la que se quiere seguir una parte del código ****/
#define decir cout <<
#define borrar system("cls")
#define pausa system("pause >> null")
#define marca cout << "\n\t momento marcado en línea: \t" <<

static int cont, turn, i;
int turno();
void vt();

struct tc {
	short int columna; short int fila; short int pieza;	short int color;
	short int peon2; //marca que deja un peón para poder ser capturado al paso
	short int clavada; // verifica que una pieza pueda moverse sin exponer al rey a un jaque
	short int tocab; //amenaza de una pieza blanca a una casilla
	short int tocan; //amenaza de una pieza negra a una casilla
	short int amenaza; int cantidad; float valc; // variables para evaluación de fuerza de jugada
}t[] = {
	{ 0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,8,3,2,0,0,0,0,0,0,0 }/*a8*/,{ 2,8,5,2,0,0,0,1,0,0,0 },{ 3,8,4,2,0,0,0,1,0,0,0 },{ 4,8,2,2,0,0,0,1,0,0,0.0 }, { 5,8,1,2,0,0,0,1,0,0,0 },   { 6,8,4,2,0,0,0,1,0,0,0 },{ 7,8,5,2,0,0,0,1,0,0,0 },{ 8,8,3,2,0,0,0,0,0,0,0 },
	{ 1,7,6,2,0,0,0,1,0,0,0 }/*a7*/,{ 2,7,6,2,0,0,0,1,0,0,0 },{ 3,7,6,2,0,0,0,1,0,0,0 },{ 4,7,6,2,0,0,0,4,0,0,0.0 }, { 5,7,6,2,0,0,0,4,0,0,0 },  { 6,7,6,2,0,0,0,1,0,0,0 },{ 7,7,6,2,0,0,0,1,0,0,0 },{ 8,7,6,2,0,0,0,1,0,0,0 },
	{ 1,6,0,0,0,0,0,2,0,0,0 }/*a6*/,{ 2,6,0,0,0,0,0,2,0,0,0 },{ 3,6,0,0,0,0,0,3,0,0,0 },{ 4,6,0,0,0,0,0,2,0,0,0.4 }, { 5,6,0,0,0,0,0,2,0,0,0.4 },{ 6,6,0,0,0,0,0,3,0,0,0 },{ 7,6,0,0,0,0,0,2,0,0,0 },{ 8,6,0,0,0,0,0,2,0,0,0 },
	{ 1,5,0,0,0,0,0,0,0,0,0 }/*a5*/,{ 2,5,0,0,0,0,0,0,0,0,0 },{ 3,5,0,0,0,0,0,0,0,0,0 },{ 4,5,0,0,0,0,0,0,0,0,0.5 }, { 5,5,0,0,0,0,0,0,0,0,0.5 },{ 6,5,0,0,0,0,0,0,0,0,0 },{ 7,5,0,0,0,0,0,0,0,0,0 },{ 8,5,0,0,0,0,0,0,0,0,0 },
	{ 1,4,0,0,0,0,0,0,0,0,0 }/*a4*/,{ 2,4,0,0,0,0,0,0,0,0,0 },{ 3,4,0,0,0,0,0,0,0,0,0 },{ 4,4,0,0,0,0,0,0,0,0,0.5 }, { 5,4,0,0,0,0,0,0,0,0,0.5 },{ 6,4,0,0,0,0,0,0,0,0,0 },{ 7,4,0,0,0,0,0,0,0,0,0 },{ 8,4,0,0,0,0,0,0,0,0,0 },
	{ 1,3,0,0,0,0,2,0,0,0,0 }/*a3*/,{ 2,3,0,0,0,0,2,0,0,0,0 },{ 3,3,0,0,0,0,3,0,0,0,0 },{ 4,3,0,0,0,0,2,0,0,0,0.4 }, { 5,3,0,0,0,0,2,0,0,0,0.4 },{ 6,3,0,0,0,0,3,0,0,0,0 },{ 7,3,0,0,0,0,2,0,0,0,0 },{ 8,3,0,0,0,0,2,0,0,0,0 },
	{ 1,2,6,1,0,0,1,0,0,0,0 }/*a2*/,{ 2,2,6,1,0,0,1,0,0,0,0 },{ 3,2,6,1,0,0,1,0,0,0,0 },{ 4,2,6,1,0,0,4,0,0,0,0.0},  { 5,2,6,1,0,0,4,0,0,0,0 },  { 6,2,6,1,0,0,1,0,0,0,0 },{ 7,2,6,1,0,0,1,0,0,0,0 },{ 8,2,6,1,0,0,1,0,0,0,0 },
	{ 1,1,3,1,0,0,0,0,0,0,0 }/*a1*/,{ 2,1,5,1,0,0,1,0,0,0,0 },{ 3,1,4,1,0,0,1,0,0,0,0 },{ 4,1,2,1,0,0,1,0,0,0,0.0},  { 5,1,1,1,0,0,1,0,0,0,0 },  { 6,1,4,1,0,0,1,0,0,0,0 },{ 7,1,5,1,0,0,1,0,0,0,0 },{ 8,1,3,1,0,0,0,0,0,0,0 }
};
// tablero principal. Puede haber muchos. De hecho yo estoy experimentando con cuatro o cinco más

int main(){
    turno();
    vt();
	Beep(350,35); //sonido ficha aj
return 0;
}

int turno(){
   	cont++;
    (cont % 2)?	turn = 1 :	turn = 2 ;
	switch (turn) {
	case 0:	cout << "no es el turno nadie \n"; break;
	case 1: cout << "es el turno de las blancas \n"; break;
	case 2:	cout << "es el turno de las negras \n"; break;
	return 0;
}
}

/**************************  visualización del tablero   *************************/

int aux(int i) { //toma el valor de cada casilla en la estructura tablero (t[]) y la vuelca en vt
	switch (t[i].pieza) {
	case 0: decir "--"; break;
	case 1: decir "-R"; break;
	case 2: decir "-D"; break;
	case 3: decir "-T"; break;
	case 4: decir "-A"; break;
	case 5: decir "-C"; break;
	case 6: decir "-P"; break; // si le sumo tocab++ acá, le suma a todos los peones, pero anda
	}
	switch (t[i].color) {
	case 0: decir "-- " ; break;
	case 1: decir "b- " ; break;
	case 2: decir "n- " ; break;
	}
	return i;
}

void vt() {
	decir "\n\t\t< * > < * > < * > < * > < * > < * > < * > < * >\n\n\n\t\t";
	for (i = 1; i <= 8; i++)   { aux(i); }
	decir "\n\n\n\t\t";
	for (i = 9; i <= 16; i++)  { aux(i); }
	decir "\n\n\n\t\t";
	for (i = 17; i <= 24; i++) { aux(i); }
	decir "\n\n\n\t\t";
	for (i = 25; i <= 32; i++) { aux(i); }
	decir "\n\n\n\t\t";
	for (i = 33; i <= 40; i++) { aux(i); }
	decir "\n\n\n\t\t";
	for (i = 41; i <= 48; i++) { aux(i); }
	decir "\n\n\n\t\t";
	for (i = 49; i <= 56; i++) { aux(i); }
	decir "\n\n\n\t\t";
	for (i = 57; i <= 64; i++) { aux(i); }
	decir "\n\n\n\t\t< * > < * > < * > < * > < * > < * > < * > < * >\n\n\n";
}
