#include <iostream>
using namespace std;

void reorganiza1(int v[], int a, int b);
void reorganiza(int v[], int n);

// EJERCICIO 22
bool montana1(int v[], int a, int b);
bool montana(int v[], int n);
// EJERCICIO 23
bool coincide1(int v[], int a, int b);
bool coincide(int v[], int n);
//LAB6
bool escalera (int v[], int n);
bool escalera1(int v[],  int recorre, int izquierda, int derecha);

//   PROGRAMA PRINCIPAL
int main(){
	/*int v[11]={651,6165,3515,354,45,6,89,256,348,187,8};
	reorganiza(v, 11);
	int x[5]={0,2,3,5,6};
	if(montana(x,5)==true){cout << "SII";}else{cout << "NOO";}
	if(coincide(x,5)==true){cout << "SII";}else{cout << "NOO";}*/
	int v[10]={7,4,4,7,7,7,2,2,2,2};
	if(escalera(v,10)){
		cout << "SI" << endl;
	}else{
		cout << "NO" << endl;
	}
	/*int v[2]={2,2};
	if(escalera(v,2)){
		cout << "SI" << endl;
	}else{
		cout << "NO" << endl;
	}*/
	return 0;
}
/* EJERCICIO 21 */
void reorganiza1(int v[], int a, int b){
	if(a<b){
		int ind1, ind2;
		if(v[a]%2!=0){
			ind1 = a;
		}else{
			reorganiza1(v,a+1,b);
		}
		if(v[b]%2==0){
			ind2 = b;
			int aux = v[a];
			v[a]=v[b];
			v[b]=aux;
		}else{
			reorganiza1(v,a,b-1);
		}
		reorganiza1(v, a+1, b-1);
	}
}
void reorganiza(int v[], int n){
	reorganiza1(v, 0, n-1);
}

// EJERCICIO 22
bool montana1(int v[], int a, int b){
	if(a==b){
		return true;
	}else{
		if(v[a]<v[a+1]){
			return montana1(v,a+1,b);
		}else if(v[b]<v[b-1]){
			return montana1(v,a,b-1);
		}else{
			return false;
		}
	}
}
bool montana(int v[], int n){
	return montana1(v,0,n-1);
}
// EJERCICIO 23
bool coincide1(int v[], int a, int b){
	int mitad = (a+b)/2;
	if(a>b){
		return false;
	}else if(v[mitad]==mitad){
		return true;
	}else if(v[mitad]>mitad){
		return coincide1(v,a,mitad-1);
	}else{
		return coincide1(v,mitad+1,b);
	}
}
bool coincide(int v[], int n){
	return coincide1(v, 0, n-1);
}

// LAB 6
bool escalera (int v[], int n){
	return escalera1(v,n-1,1,n);
}
bool escalera1(int v[],  int recorre, int izquierda, int derecha){
	if(recorre==0){
		return true;
	}else if(izquierda>derecha){
		return false;
	}else if(v[recorre]==v[recorre-1]){
		return escalera1(v,recorre-1,izquierda+1,derecha);
	}else{
		return escalera1(v,recorre-1,1,izquierda);
	}
}

