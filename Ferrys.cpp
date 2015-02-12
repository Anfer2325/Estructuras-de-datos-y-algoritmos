//Jaime Delgado Linares

#include <iostream>
#include "TADS\Cola.h"
using namespace std;

const int capacidad = 5;

struct Ferry{
	double babor;
	double estribor;
	int solucion[2*capacidad]; // 0 BABOR, 1 ESTRIBOR
	int numCoches;
	bool baborOcupado;
	bool estriborOcupado;

	//Metodos
	void inicializa(){
		babor=0.0;
		estribor=0.0;
		baborOcupado=false;
		estriborOcupado=false;
		numCoches=0;
	}

	void inicializa(Ferry f){
		babor = f.babor;
		estribor = f.estribor;
		numCoches = f.numCoches;
		baborOcupado = f.baborOcupado;
		estriborOcupado = f.estriborOcupado;
		for(int i=0; i<numCoches; i++){
			solucion[i] = f.solucion[i];
		}
	}

	bool esMejor(Ferry f){
		return babor+estribor > f.babor+f.estribor;
	}



};

void f(double capacidad, double pesos[]);
void ferrys(double capacidad, double pesos[], int numPesos, Ferry ferry, Ferry &ferryOptimo, int k);

int main(){
	double pesos[7] = { 2.5, 3, 1, 1, 1.5, 0.7, 0.8};
	f(5, pesos);
	return 0;
}
void f(double capacidad, double pesos[]){
	Ferry ferry;
	ferry.inicializa();
	ferrys(capacidad, pesos, 7, ferry, ferry, 0);
	cout << "[ ";
	for(int i=0; i<ferry.numCoches; i++){
		if(ferry.solucion[i]==0){
			cout << "BABOR " ; 
		}else{
			cout << "ESTRIBOR " ;
		}
	}
	cout << "]" << endl <<  "BABOR=" << ferry.babor << " , ESTRIBOR=" << ferry.estribor << endl;
}
void ferrys(double capacidad, double pesos[], int numPesos, Ferry ferry, Ferry &ferryOptimo, int k){
	
	for(int i=0; i<2; i++){
		ferry.solucion[k] = i;
		ferry.numCoches++;
		if(i==0){
			ferry.babor += pesos[k];
		}else{
			ferry.estribor += pesos[k];
		}
		if(i==0 && ferry.babor <= capacidad){
			if(k == numPesos-1){
				if(ferry.esMejor(ferryOptimo)){
					ferryOptimo.inicializa(ferry);
				}
			}else{
				ferrys(capacidad, pesos, numPesos, ferry, ferryOptimo, k+1);
			}
		}else if(i==1 && ferry.estribor <= capacidad){
			if(k == numPesos-1){
				if(ferry.esMejor(ferryOptimo)){
					ferryOptimo.inicializa(ferry);
				}
			}else{
				ferrys(capacidad, pesos, numPesos, ferry, ferryOptimo, k+1);
			}
		}

		ferry.numCoches--;
		if(i==0){
			ferry.babor -= pesos[k];
		}else{
			ferry.estribor -= pesos[k];
		}

		if(k == numPesos-1){
			if(ferry.esMejor(ferryOptimo)){
				ferryOptimo.inicializa(ferry);
			}
		}
	}

	
	
}