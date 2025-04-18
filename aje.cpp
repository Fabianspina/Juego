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

static int cont, turn;
int turno();

int main(){
    turno();
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
