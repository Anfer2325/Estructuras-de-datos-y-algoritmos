#include <iostream> 
using namespace std;

void soluciona(int mapa[20][20], int fila, int columna, int beepersRestantes, int maxFila, int maxCol, int &sol, int movimientos){
	//Compruebo si he terminado
	if(beepersRestantes == 0){
		//return 0;
		if(movimientos<sol){
			sol=movimientos;
		}
	}else{
		
		//Dejo visitado el lugar en el que estoy
		mapa[fila][columna] = 1;

		//Busco si tengo algun beeper al lado
		if(fila+1<=maxFila && mapa[fila+1][columna]==2){
			//return 1 + 
				soluciona(mapa, fila+1, columna, beepersRestantes-1, maxFila, maxCol, sol, movimientos+1);
		}
		if(fila-1>=0 && mapa[fila-1][columna]==2){
			//return 1 + 
			soluciona(mapa, fila-1, columna, beepersRestantes-1, maxFila, maxCol, sol, movimientos+1);
		}
		if(columna+1<=maxCol && mapa[fila][columna+1]==2){
			//return 1 + 
			soluciona(mapa, fila, columna+1, beepersRestantes-1, maxFila, maxCol, sol, movimientos+1);
		}
		if(columna-1>=0 && mapa[fila][columna-1]==2){
			//return 1 + 
			soluciona(mapa, fila, columna-1, beepersRestantes-1, maxFila, maxCol, sol, movimientos+1);
		}

		//Busco espacios no visitados
		if(fila+1<=maxFila && mapa[fila+1][columna]==0){
			//return 1 + 
			soluciona(mapa, fila+1, columna, beepersRestantes, maxFila, maxCol, sol, movimientos+1);
		}
		if(fila-1>=0 && mapa[fila-1][columna]==0){
			//return 1 + 
			soluciona(mapa, fila-1, columna, beepersRestantes, maxFila, maxCol, sol, movimientos+1);
		}
		if(columna+1<=maxCol && mapa[fila][columna+1]==0){
			//return 1 + 
			soluciona(mapa, fila, columna+1, beepersRestantes, maxFila, maxCol, sol, movimientos+1);
		}
		if(columna-1>=0 && mapa[fila][columna-1]==0){
			//return 1 + 
			soluciona(mapa, fila, columna-1, beepersRestantes, maxFila, maxCol, sol, movimientos+1);
		}
		
	}
	//return 0;
}

int solucionaGuiado(int mapa[20][20], int fila, int col, int beepers, int maxFila, int maxCol, int filaIni, int colIni){
	if(beepers==0){
		return col-colIni+fila-filaIni;
	}else{
		//busco aver si hay beeper en la fila
		bool encontrado = false;
		int i=0;
		for(i; i<=maxFila&&!encontrado; i++){
			if(mapa[i][col]==2){
				encontrado = true;
			}
		}
		i = i-1;
		if(encontrado){
			if(i<fila){
				for(int j=i; j<=fila; j++){
					if(mapa[j][col]==2){
						beepers = beepers-1;
					}
					mapa[j][col] = 1;
				}
				return fila-i + solucionaGuiado(mapa, i, col, beepers, maxFila, maxCol, filaIni, colIni);
			}else{
				for(int j=fila; j<=i; j++){
					if(mapa[j][col]==2){
						beepers = beepers-1;
					}
					mapa[j][col] = 1;
				}
				return i-fila + solucionaGuiado(mapa, i, col, beepers, maxFila, maxCol, filaIni, colIni);
			}
		}else{
			if(col+1>maxCol){
				return 0;
			}else{
				return 1 + solucionaGuiado(mapa, fila, col+1, beepers, maxFila, maxCol, filaIni, colIni);
			}
		}
	}
}

int main(){
	/* Voy a crear una matriz bidimensional de enteros en la cual los valores significaran lo siguiente:
	    *** 0 : no visitado
		*** 1 : visitado
		*** 2 : hay un beeper */

	int numEscenarios;
	cin >> numEscenarios;
	for(int i=0; i<numEscenarios; i++){
		int filas, columnas;
		cin >> filas >> columnas;
		int posFilaIni, posColIni;
		cin >> posFilaIni >> posColIni;

		/*int **mapa = new int*[filas];
		for(int i=0; i<filas; i++){ 
			mapa[i] = new int[columnas];
		}*/

		int mapa[20][20];
		//Inicializo array a 0
		for(int i=0; i<filas; i++){
			for(int j=0; j<columnas; j++){
				mapa[i][j] = 0;
			}
		}
		


		//mapa[posFilaIni][posColIni] = 1; //Visito lugas inicial

		int numBeepers;
		cin >> numBeepers;
		for(int i=0; i<numBeepers; i++){
			int posF, posC;
			cin >> posF >> posC;
			mapa[posF-1][posC-1] = 2;
		}

		//cout << "The shortest path has length " << soluciona(mapa, posFilaIni-1, posColIni-1, numBeepers, filas-1, columnas-1) << endl;
		//int sol = filas*columnas;
		//soluciona(mapa, posFilaIni-1, posColIni-1, numBeepers, filas-1, columnas-1, sol, 0);
		//cout << "The shortest path has length " << sol << endl; 
		cout << "The shortest path has length " << solucionaGuiado(mapa, posFilaIni-1, posColIni-1, numBeepers, filas-1, columnas-1, posFilaIni-1, posColIni-1) << endl; 
	}
	return 0;
}