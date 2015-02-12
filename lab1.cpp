//Jaime Delgado Linares
#include <iostream>
using namespace std;

int algoritmo(int v[], int num){
	// P = Tiene que ser un vector con elementos>=0 que tenga espacio para n elementos
	int r=0;
	int suma=0;
	for(int i=num-1; i>0; i--){
		if(v[i]==suma){
			r++;
		}
		suma= suma + v[i];
	}
	// Q = Cuenta todas las veces que un numero es la suma de todos sus posteriores
	return r;
}

int main(){
	//ejemplo1
	int v[5]={4,2,1,1,0}; // tiene 3 posiciones(0,1,4) que cumplen el algoritmo
	int r=algoritmo(v,5);  // r=3
	//ejemplo2
	int a[6]={0,0,0,11,4,7}; // tiene 1 posicion(3) que coinciden con su valor
	int j=algoritmo(a,6); // j=1
	//ejemplo3
	int c[7]={0,0,20,10,4,6,0}; // tiene 3 posiciones(2,3,6) que coinciden con su valor
	int t=algoritmo(c,7); // t=1
	return 0;
}

/*COMPLEJIDAD
  El tiempo del if son 5t(2 del vector , una comparacion, y 2 del r++)
  suma=suma+v[i]; son 4t(1 suma, 1 asignacion, 2 del vector)
  Como el bucle se repite num veces, el tiempo del bucle son:
  2t(num-1 y asignacion a i)+ (1t(comparacion) + 9t dentro del bucle + 1t(i--))= 2 + 11t;
  Como se repite num-1 veces = 2+11*(n);
  A esto hay que sumarte las dos inicializaciones (2t) anteriores al bucle.
  Total 11(n)+4
  Por lo que la complejidad es O(n).
  */