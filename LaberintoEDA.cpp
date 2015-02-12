//Jaime Delgado Linares
#include <iostream>
#include "Lista.h"
using namespace std;

const int filas=5, columnas=8;
char tablero[filas][columnas]= {'M','D','A','A','E','E','D','A',
								'A','E','E','D','D','A','N','D',
								'D','B','D','X','E','D','A','E',
								'E','A','E','D','A','R','T','D',
								'E','D','M','P','L','E','D','A'};
Lista<char> palabra;

struct Tablero{
	int filaIni, colIni, filaFin, colFin;
	bool visitados[filas+2][columnas+2];
	int mejorSol[filas*columnas];
	int movimientosSol;

	//Metodos

	//Inicializa el array de visitados (Tiene un borde de visitados que sirve para no irte de rango en el array)
	void inicializa(){
		for(int i=0; i<filas+2; i++){
			for(int j=0; j<columnas+2; j++){
				visitados[i][j] = false;
				if(i==0||j==0||i==filas+1||j==columnas+1){
					visitados[i][j] = true;
				}
			}
		}
	}

	//Comprueba si esta visitado
	bool estaVisitado(int fila, int columna){
		return visitados[fila+1][columna+1];
	}

	//comprueba si coincide la letra
	bool coincide(int fila, int col, char letra){
		return tablero[fila][col]==letra;
	}
};



void lab();
void laberinto(int solucion[], int nivel, int fila, int columna, Tablero &tablero, Lista<char>::Iterador it);

int main(){
	palabra.ponDr('E');
	palabra.ponDr('D');
	palabra.ponDr('A');
	lab();
	return 0;
}

void lab(){
	//Inicializo los datos de comienzo y final del tablero, y el array de visitados
	Tablero t;
	t.filaFin=0;
	t.filaIni=4;
	t.colFin=7;
	t.colIni=0;
	t.movimientosSol=filas*columnas;
	t.inicializa();

	//Llamo a la funcion que lo resuelve
	int solucion[filas*columnas];
	Lista<char>::  Iterador it = palabra.principio();
	it.avanza();
	laberinto(solucion, 0, t.filaIni, t.colIni, t, it);

	//Imprimo solucion
	for(int i=0; i<t.movimientosSol; i++){
		if(t.mejorSol[i]==0){
			cout << "N";
		}else if(t.mejorSol[i]==1){
			cout << "S";
		}else if(t.mejorSol[i]==2){
			cout << "0";
		}else if(t.mejorSol[i]==3){
			cout << "E";
		}
	}
}
void laberinto(int solucion[], int nivel, int fila, int columna, Tablero &tablero, Lista<char>::Iterador it){
	for(int i=0; i<4; i++){
		//Me muevo
		if(i==0){ //Arriba
			fila--;
		}else if(i==1){ //Abajo
			fila++;
		}else if(i==2){ //Izquierda
			columna--;
		}else if(i==3){ //Derecha
			columna++;
		}
		//Compruebo si se puede mover ahi mirando si no esta visitado y si coincide la letra
		if(!tablero.estaVisitado(fila, columna) && tablero.coincide(fila, columna, it.elem())){

			//Compruebo si ha llegado al punto (0,7)
			if(fila==tablero.filaFin && columna==tablero.colFin){

				//Compruebo si la solucion es mejor que la que tenia antes
				if(nivel+1<=tablero.movimientosSol){ //Compruebo si la solucion es mejor que la anterior
					tablero.movimientosSol = nivel+1;
					for(int j=0; j<nivel+1; j++){
						tablero.mejorSol[j] = solucion[j];
					}
				}

			}else{
				tablero.visitados[fila+1][columna+1] = true; //Marco

				solucion[nivel]=i;  //Meto el movimiento en la solucion

				it.avanza();//Paso a la siguiente letra
				if(it==palabra.final()){ 
					it=palabra.principio();
				}

				laberinto(solucion, nivel+1, fila, columna, tablero, it); //Paso al siguiente nivel

				tablero.visitados[fila+1][columna+1] = false; //Desmarco

				for(int j=0; j<2; j++){ // Dejo la letra donde estaba (iterando dos veces)
					it.avanza();//Paso a la siguiente letra
					if(it==palabra.final()){
						it=palabra.principio();
					}
				}
			}
		}

		//Restauro lo que habia antes
		if(i==0){ //Arriba
			fila++;
		}else if(i==1){ //Abajo
			fila--;
		}else if(i==2){ //Izquierda
			columna++;
		}else if(i==3){ //Derecha
			columna--;
		}

	}
}