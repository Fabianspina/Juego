#include <iostream>
using namespace std;
static int cont, turn;
int turno();

int main(){
turno();
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
