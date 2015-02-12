#include <iostream>
#include <string>
using namespace std;

struct Map{
	int **nums; //Mapa con los numeros
	bool **v; //Marcaje de visitados (true=visitado, false=NO visitado)
	int filas;
	int columnas;
	bool esValida(const int fila, const int col, const int filaA, const int colA) const{
		return noSeSale(fila, col) && !v[fila-1][col-1] && nums[fila-1][col-1]<nums[filaA][colA];
	}
	bool esValida(const int fila, const int col, int dir) const{
		if(dir==0){ //Compruebo con fila-1
			return noSeSale(fila, col) && !v[fila-1][col-1] && nums[fila-1][col-1]<nums[fila-2][col-1];
		}else if(dir==1){ //Compruebo con fila+1
			return noSeSale(fila, col) && !v[fila-1][col-1] && nums[fila-1][col-1]<nums[fila][col-1];
		}else if(dir==2){ //Compruebo con columna-1
			return noSeSale(fila, col) && !v[fila-1][col-1] && nums[fila-1][col-1]<nums[fila-1][col-2];
		}else if(dir==3){ //Compruebo con columna+1
			return noSeSale(fila, col) && !v[fila-1][col-1] && nums[fila-1][col-1]<nums[fila-1][col];
		}
		return false;
	}
	bool esSol(const int fila,const int col) const{
		int act = nums[fila-1][col-1];
		return !(noSeSale(fila+1, col)&&act>=nums[fila][col-1]) && !(noSeSale(fila-1, col)&&act>=nums[fila-2][col-1])
			&& !(noSeSale(fila, col+1)&&act>=nums[fila-1][col]) && !(noSeSale(fila, col-1)&&act>=nums[fila-1][col-2]);
	}
	bool noSeSale(const int fila, const int col) const{
		return fila-1>=0 && fila-1<filas && col-1>=0 && col-1<columnas;
	}
	
};

struct Persona{
	string nombre;
	int filaInicial;
	int colInicial;
};

void soluciona(int nivel, Map &mapa, int fila, int col, int &mejorSol){
	for(int i=0; i<4; i++){
		if(i==0){ //fila+1
			fila++;
		}else if(i==1){//fila-1
			fila--;
		}else if(i==2){//columna+1
			col++;
		}else{//columna-1
			col--;
		}
		if(mapa.esValida(fila, col, i)){
			if(mapa.esSol(fila, col)){
				if(nivel>mejorSol){
					mejorSol=nivel;
				}
			}
			mapa.v[fila-1][col-1]=true; //Marco
			soluciona(nivel+1, mapa, fila, col, mejorSol);
			mapa.v[fila-1][col-1]=false; //Desmarco
		}
		//Vuelvo al estado anterior
		if(i==0){ //fila+1
			fila--;
		}else if(i==1){//fila-1
			fila++;
		}else if(i==2){//columna+1
			col--;
		}else{//columna-1
			col++;
		}
		
	}
}

int main(){
	int casos;
	cin >> casos;
	for(int i=0; i<casos; i++){
		Map mapa; 
		Persona persona;
		cin >> persona.nombre >> mapa.filas >> mapa.columnas >> persona.filaInicial >> persona.colInicial;

		mapa.nums = new int *[mapa.filas];
		mapa.v = new bool *[mapa.filas];
		for(int j=0; j<mapa.filas; j++){
			mapa.nums[j] = new int [mapa.columnas];
			mapa.v[j] = new bool [mapa.columnas];
		}
		for(int f=0; f<mapa.filas; f++){
			for(int c=0; c<mapa.columnas; c++){
				int num;
				cin >> num;
				mapa.nums[f][c] = num; 
				mapa.v[f][c] = false;
			}
		}
		mapa.v[persona.filaInicial-1][persona.colInicial-1] =true;
		int sol=0;
		soluciona(2, mapa, persona.filaInicial, persona.colInicial, sol);
		cout << sol << endl;
		delete[] mapa.nums;
		delete[] mapa.v;

	}
	return 0;
}