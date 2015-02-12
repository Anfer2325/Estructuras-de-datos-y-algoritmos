#include <iostream>
#include <string>
#include <fstream>
#include "Lista.h"
#include "Pila.h"
using namespace std;

string leeArchivo(string archivo);

void rotatingSentences(string cadena);
int cuentaPalabras(string cadena);


int main(){
	/*string c = "Rene Decartes once said,\n' I think, therefore I am.'";
	rotatingSentences(c);*/
	string t = leeArchivo("rotating.txt");
	rotatingSentences(t);
	return 0;
}

string leeArchivo(string archivo){
	string texto = "";
	string linea;
	ifstream a;
	a.open(archivo);
	if(!a.is_open()){
		cout << "ERROR AL LEER ARCHIVO" << endl;
	}else{
		while(!a.eof()){
			getline(a,linea);
			texto=texto+linea+'\n';
		}
	}
	a.close();
	return texto;
}

void rotatingSentences(string cadena){
	int tam = cadena.size();
	int fila=0, columna=0, i=0;
	char letras[50][50];
	for(int i=0; i<50; i++){ //Inicializo todo el array a espacios en blanco
		for(int j=0; j<50; j++){
			letras[i][j]=' ';
		}
	}
	int lineaMasLarga=0, lineaAct=0, numLineas=0;
	while(i<tam){ //Cálculo cual es a linea más larga y cuantas lineas tiene
		while(i<tam && cadena[i]!='\n'){
			lineaAct++;
			i++;
		}
		numLineas++;
		if(lineaAct>lineaMasLarga){
			lineaMasLarga=lineaAct;
		}
		lineaAct=0;
		i++;
	}
	i=0;
	while(i<tam){ // Introduzco el texto en el array, cada linea en una fila del array
		while(i<tam && cadena[i]!='\n'){
			letras[fila][columna]=cadena[i];
			columna++;
			i++;
		}
		fila++;
		columna=0;
		i++;
	}
	for(int col=0; col<lineaMasLarga; col++){ //Muestro por pantalla el resultado
		for(int fil=numLineas-1; fil>=0; fil--){
			cout << letras[fil][col];
		}
		cout << endl;
	}
	
		
}
int cuentaPalabras(string cadena){
	int tam=cadena.size();
	int i=0;
	int cont=0;
	bool nuevaPalabra = false;
	while(i<tam){
		nuevaPalabra=true;
		while(i<tam && cadena[i]>=65 && cadena[i]<=122){
			if(nuevaPalabra==true){
				cont++;
			}
			nuevaPalabra=false;
			i++;
		}
		i++;
	}
	return cont;
}

