#include <iostream>
#include "TADS\Arbus.h"
using namespace std;

void pruebaEjercicio1();

int main(){
	pruebaEjercicio1();
}

void pruebaEjercicio1(){
	Arbus<int, string> a;
	for(int i=0; i<9; i++){
		a.inserta(i,"Hola");
	}
	int siguiente = a.siguienteClave(3);
	Arbus<int, string>::Iterador it = a.principio();
	
}