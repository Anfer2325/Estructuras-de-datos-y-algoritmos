#include <iostream>
#include <string>
using namespace std;

string digitos[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

void soluciona(string palabras[], unsigned int numPalabras, string regla, string trozos[], unsigned int indice){
	if(indice == regla.size()){
		for(unsigned int i=0; i< regla.size(); i++){
			cout << trozos[i];
		}
		cout << endl;
	}else{
		if(regla[indice] == '#'){ //Introduzco palabras
			for(unsigned int i=0; i<numPalabras; i++){
				trozos[indice] = palabras[i];
				soluciona(palabras, numPalabras, regla, trozos, indice+1);
			}
		}else{ //Introduzco digitos
			for(unsigned int i=0; i<10; i++){
				trozos[indice] = digitos[i];
				soluciona(palabras, numPalabras, regla, trozos, indice+1);
			}
		}
	}	
	
 }
int main() {
	string palabras[100];
	int numPalabras, numReglas;
	string palabra, regla;
	while(cin >> numPalabras){
		cout << "--" << endl;
		for(int i=0; i<numPalabras; i++){
			cin >> palabra;
			palabras[i] = palabra;
		}
		cin >> numReglas;
		for(int i=0; i<numReglas; i++){
			cin>>regla;
			string *trozos = new string[regla.size()];
			soluciona(palabras, numPalabras, regla, trozos, 0);
			delete[] trozos;
		}
	}
    return 0;
}
