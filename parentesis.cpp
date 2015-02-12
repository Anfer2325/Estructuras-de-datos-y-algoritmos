//Jaime Delgado Linares

#include <iostream>
#include "lineales.h"

using namespace std;


void parentesis(){
	string cadena;
	Cola<string> cola;
	Pila<char> pila;
	getline(cin, cadena); // quito numero, no lo uso
	getline(cin, cadena);
	while(!cin.eof()){
		cola.ponDetras(cadena);
		getline(cin, cadena);	
	}



	/*cola.ponDetras("( esto es [ una ] prueba correcta )");
	cola.ponDetras("( cierro ([(un parentesis)]) de) mas)");
	cola.ponDetras("([()[]()])() todo correcto");
	cola.ponDetras("(abro pero no cierro nada");
	cola.ponDetras("(cierro lo que no debo] )");
	cola.ponDetras("cierro ( parentesis antes de abrirlos ]");
	cola.ponDetras("cierro [ corchetes antes de abrirlos ");*/
	
	while(!cola.esVacia()){
		unsigned int i = 0;
		bool ok = true;
		if(cola.esVacia()){
		}else{
			cadena = cola.primero();
			while(ok && i<cadena.size()){
				char c = cadena[i];
				if((c==')'||c=='}'||c==']')&&pila.esVacia()){
					ok = false;
				}else if(c=='('||c=='{'||c=='['){
					pila.apila(c);
				}else if(c==')'){
					if(pila.cima()=='('){
						pila.desapila();
					}else{
						ok = false;
					}
				}else if(c==']'){
					if(pila.cima()=='['){
						pila.desapila();
					}else{
						ok = false;
					}
				}else if(c=='}'){
					if(pila.cima()=='{'){
						pila.desapila();
					}else{
						ok = false;
					}
				}
				i++;
			}
			if(ok&&pila.esVacia()){
				cout << "Yes" << endl ;
			}else{
				cout << "No" << endl;
			}
			
			while(!pila.esVacia()){
				pila.desapila();
			}
		
			cola.quitaPrim();
			
		}
		
	}

}

int main(){
	parentesis();
	return 0;
}