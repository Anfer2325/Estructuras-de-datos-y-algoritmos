#include <iostream>
using namespace std;

struct Fraccion{
	int num;
	int den;
	//Crea la fraccion con esos parametros
	void creaFraccion(int n, int d){
		num = n;
		den = d;
	}
	// Devuelve el valor double de la fraccion
	double valor(){
		return (double)num / den;
	}
	// Resta numerador con numerador y denominador con denominador
	Fraccion resta(Fraccion f){
		Fraccion res;
		res.num = num - f.num;
		res.den = den - f.den;
		return res;
	}
	// Suma numerador con numerador y denominador con denominador
	Fraccion suma(Fraccion f){
		Fraccion res;
		res.num = num + f.num;
		res.den = den + f.den;
		return res;
	}
};



//Solucion sin tads
string solucion(int num, int den, Fraccion f1, Fraccion f2){
	int nuevoNum = f1.num + f2.num;
	int nuevoDen = f1.den + f2.den;
	Fraccion fnueva, f3;
	fnueva.creaFraccion(nuevoNum, nuevoDen);

	if((double)num/den>fnueva.valor()){
		return "R" + solucion(num, den, fnueva, f2);
	}else if((double)num/den<fnueva.valor()){
		return "L" + solucion(num, den, f1, fnueva);
	}else{
		return "";
	}
	
}

int main(){
	
	int numerador, denominador;
	cin >> numerador;
	cin >> denominador;
	
	while(numerador!=1 || numerador!=1){
		Fraccion ceroUno, unoCero;
		ceroUno.creaFraccion(0,1);
		unoCero.creaFraccion(1,0);

		cout << solucion(numerador, denominador, ceroUno, unoCero) << endl;

		//arbol = crea(numerador, denominador, ceroUno, unoCero);

		//cout << soluciona(arbol, numerador, denominador) << endl;

		cin >>numerador;
		cin >>denominador;
	}

	return 0;
}