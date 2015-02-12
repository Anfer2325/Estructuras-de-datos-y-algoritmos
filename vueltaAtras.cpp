#include <iostream>
#include "TADS\Lista.h"
#include <string>
using namespace std;

const int M=5, N=8;
typedef struct{
int mejorSol[N];
	int cont;
}tSolucion;
char lab[M][N]={'M','D','A','A','E','E','D','A',
				'A','E','E','D','D','A','N','D',
				'D','B','D','X','E','D','A','E',
				'E','A','E','D','A','R','T','D',
				'E','D','M','P','L','E','D','A'};

void intro(tSolucion &sol, int pos, int i);
void damas(int solucion[40], int fila, int col, int &nivel, tSolucion &mejorSol, Lista<char> &lista);
void aux();
void avanza(int &fila, int &columna, int num);

int main(){
	Lista<char> lista;
	lista.ponDr('E');
	lista.ponDr('D');
	lista.ponDr('A');
	tSolucion mejorSol;
	mejorSol.cont = M*N;
	int solu[M*N];
	int zero = 0;
	damas(solu,4,0,zero,mejorSol,lista);
	for(int i=0; i<mejorSol.cont; i++){
		if(mejorSol.mejorSol[i]==0){
			cout << "R";
		}else if(mejorSol.mejorSol[i]==1){
			cout << "B";
		}else if(mejorSol.mejorSol[i]==2){
			cout << "D";
		}else if(mejorSol.mejorSol[i]==3){
			cout << "I";
		}
	}
	return 0;
}
void intro(tSolucion &sol, int pos, int i){
	sol.mejorSol[pos]=i;
	sol.cont++;
}
void damas(int solucion[M*N], int fila, int col, int &nivel, tSolucion &mejorSol, Lista<char> &lista){
	Lista<char>::Iterador it = lista.principio();
	lista.ponDr(it.elem());
	it = lista.borra(it);
	for(int i=0; i<4; i++){
		solucion[nivel]=i;
		int filaaux=fila, colaux=col;
		avanza(filaaux,colaux,i);
		if(lab[filaaux][colaux]==it.elem()){
			if(filaaux==0&&colaux==7){
				if(nivel<mejorSol.cont){
					mejorSol.cont=nivel;
					for(int j=0; j<nivel; j++){
						intro(mejorSol,j,solucion[j]);
					}
				}
			}else{
				int niv = nivel +1;
				damas(solucion, filaaux, colaux, niv, mejorSol, lista);
			}
		}
	}
}
void avanza(int &fila, int &columna, int num){
	switch(num){
		case 0: //ARRIBA
		fila--;
		break;
		case 1: //ABAJO
		fila++;
		break;
		case 2: //DERECHA
		columna++;
		break;
		case 3: //IZQUIERDA
		columna--;
		break;
		default: break;
	}
}