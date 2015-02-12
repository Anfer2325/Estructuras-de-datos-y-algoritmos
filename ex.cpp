#include <iostream>
#include <string>
#include "Pila.h"
#include "Cola.h"
#include "Excepciones.h"
#include "Lista.h"
#include "Arbin.h"
#include "Arbus.h"
using namespace std;

/*1. Implementa, con ayuda de una pila, un procedimiento no recursivo que reciba como
//parámetro un número entero n  0 y escriba por pantalla sus dígitos en orden
//lexicográco y su suma. Por ejemplo, ante n = 64323 escribirá:
//6 + 4 + 3 + 2 + 3 = 18*/
void ejercicio1();
/*3. Implementa una función que reciba una secuencia de caracteres en una lista que
contiene, entre otros símbolos, paréntesis, llaves y corchetes abiertos y cerrados y
decida si está equilibrada. Entendemos por secuencia equilibrada respecto a los tres
tipos de símbolos si cada uno de ellos tiene el tantos abiertos como cerrados y si cada
vez que aparece uno cerrado, el último que apareció fue su correspondiente abierto.*/
void ejercicio3();
//4. PALINDROMAS
void ejercicio4();
//12. SELECCIONA CADA M EN N ALUMNOS
void ejercicio12();
/*17. Dada una secuencia de enteros, contar cuántas posiciones hay en ella tales que el
entero que aparece en esa posición es igual a la suma de todos los precedentes.*/
void ejercicio17();
////////////////ARBOLES/////////////////
//Construye un arbol binario
template <class C>
Arbin<C> construye(Arbin<C> &arbol);
//4. ESCRIBE ARBOL
template <class C>
void escribeArbol(Arbin<C> &a);
//6.FIBONACCI
int fib(int n);
Arbin<int> fibo (int n);
//7. HOMOGENEO
template < class C>
bool homogeneo(Arbin<C> &a);
//9.NODOS SUMEN UN VALOR DADO POR LA RAIZ
bool sumanodos(Arbin<int> a, int n);

int main(){
	Arbin<int> arbol, b;
	construye(arbol);
	Arbus<int, int> c;
	c.
	/*escribeArbol(arbol);*/
	/*int n;
	cin >> n;*/
	/*if(homogeneo(arbol)){
		cout << "SIIIIIIIIII" << endl;
	}else{
		cout << "NOOOOOOOOOOO" << endl;
	}*/
	/*int n=0;
	if(sumanodos(arbol, n)==true){
		cout << "SIIIII";
	}else{
		cout << "NOOOOO";
	}*/
	/*int n=0;
	if(alturamin(arbol, n)){
		cout << "SIIIII";
	}else{
		cout << "NOOOOO";
	}*/
	return 0;
}

void ejercicio1(){
	int n=1, resultado=0;
	while(n!=0){
		cout << "Introduzca un numero entero:"; cin >> n;
		if(n!=0){
			Pila<int> pila;
			//Apilamos todos los numeros en orden inverso en pila
			while(n!=0){
				int digito = n%10;
				pila.apila(digito);
				resultado=resultado+digito;
				n=n/10;
			}
			//Vamos sacando los digitos para esribir por pantalla la suma
			while(!pila.esVacia()){
				cout << pila.cima();
				pila.desapila();
				if(!pila.esVacia()){
					cout << " + ";
				}else{
					cout << " = ";
				}
			}
			cout << resultado << endl;
			resultado=0;
			n=1;
		}
	}
}
void ejercicio3(){
	string cadena="1";
	while(cadena!=""){
		cout << "Introduzca una cadena de caracteres:" << endl;
		getline(cin, cadena);
		bool ok=true;
		if(cadena!=""){
			Pila<int> pila;
			int l = cadena.size();
			int i=0;
			while(i<l && ok){
				char c=cadena.at(i);
				if(c=='(' || c=='[' || c=='{'){
					pila.apila(c);
				}else if(c==')'){
					if(pila.cima()=='('){
						pila.desapila();
					}else{
						ok=false;
					}
				}else if(c==']'){
					if(pila.cima()=='['){
						pila.desapila();
					}else{
						ok=false;
					}
				}else if(c=='}'){
					if(pila.cima()=='{'){
						pila.desapila();
					}else{
						ok=false;
					}
				}
				i++;
			}
			if(ok && pila.esVacia()){
				cout << "ESTA EQUILIBRADA!!" << endl;
			}else{
				cout << "NO ESTA EQUILIBRADA!!" << endl;
			}
		}
		cin.sync();
	}
}
void ejercicio4(){
	string cadena="0";
	while(cadena!=""){
		cout << "Introduzca una frase:" << endl;
		getline(cin, cadena);
		int n = cadena.size();
		Pila<int> pila;
		Cola<int> cola;
		//Apilo todos los caracteres en una pila y una cola
		for(int i=0; i<n; i++){
			char c=cadena.at(i);
			if(c!=' '){
				pila.apila(c);
				cola.ponDetras(c);
			}
		}
		//Compruebo
		bool ok=true;
		while(ok && !pila.esVacia()){
			char cpila = pila.cima();
			char ccola = cola.primero();
			if(cpila!=ccola){
				ok=false;
			}else{
				pila.desapila();
				cola.quitaPrim();
			}
		}
		//Muestro el resultado
		if(ok){
			cout << "ES PALINDROMA" << endl;
		}else{
			cout << "NO ES PALINDROMA" << endl;
		}
	}
}
void ejercicio12(){
	int n=1, pon=0, m;
	while(n!=0){
		cout << "Introduzca el numero de alumnos: "; cin >> n;
		cout << "Cada cuantos quieres salvar?: "; cin >> m;
		Lista<int> lista;
		for(int i=1; i<=n; i++){
			lista.ponDr(i);
		}
		Lista<int>::Iterador it = lista.principio();
		int cont = 1;
		while(lista.numElems()!=1){
			if(cont%m==0){
				it=lista.borra(it);
			}else if(lista.numElems()!=1){
				pon=it.elem();
				it=lista.borra(it);
				lista.ponDr(pon);
			}
			cont++;
		}
		cout << it.elem() << endl;
	}
}
void ejercicio17(){
	string cadena="a";
	char n;
	int cont=0,suma=0,num;
	Lista<int>lista;
	n = cin.peek();
	while(n!='\n'){
		cin >> num;
		lista.ponDr(num);
		cin.sync();
		n = cin.peek();
	}
	Lista<int>::Iterador it = lista.principio();
	while(it!=lista.final()){
		suma=suma+it.elem();
		if(it.elem()==suma){
			cont++;
		}
		it.avanza();
	}
	cout << "Hay " << cont << " posiciones" << endl;

}
template <class C>
Arbin<C> construye(Arbin<C> &arbol){
	Arbin<C> iz, dr;
	char c;
	int num;
	c = cin.peek();
	if(isdigit(c)){
		cin>>num;
		cin.sync();
		iz = construye(iz);
		dr = construye(dr);
		arbol = Arbin<C>(iz, num, dr);
	}else{
		cin.get(c);
		cin.sync();
		arbol = Arbin<C>();
	}
	return arbol;
}
template <class C>
void escribeArbol(Arbin<C> &a){
	if(a.esVacio()){
		cout << "<Vacio>" << endl;
	}else if(a.hijoIz().esVacio() && a.hijoDr().esVacio()){
		cout << a.raiz() << endl;
	}else{
		cout << a.raiz() << endl;a.
		escribeArbol(a.hijoIz());
		escribeArbol(a.hijoDr());
	}
}
int fib(int n){
	if(n==0){
		return 0;
	}else if(n == 1){
		return 1;
	}else{
		return fib(n-2) + fib(n-1);
	}
}
Arbin<int> fibo (int n){
	if(n==0){
		return Arbin<int> (Arbin<int>(), n, Arbin<int>());
	}else if(n==1){
		return Arbin<int> (Arbin<int>(), n, Arbin<int>());
	}else{
		return Arbin<int> (fibo(n-2), fib(n), fibo(n-1));
	}
}
template < class C>
bool homogeneo(Arbin<C> &a){
	if(a.talla() == 1){
		return true;
	}else if(a.hijoIz().esVacio() || a.hijoDr().esVacio()){
		return false;
	}else{
		return homogeneo(a.hijoIz())&&homogeneo(a.hijoDr());
	}
}
bool sumanodos(Arbin<int> a, int n){
	if((n == 0) && a.esVacio()){
		return true;
	}else if(a.esVacio()){
		return false;
	}else if(n==a.raiz()){
		return true;
	}else{
		return sumanodos(a.hijoIz(), n+a.raiz()) || sumanodos(a.hijoDr(), n+a.raiz());
	}
}

