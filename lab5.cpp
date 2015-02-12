//Jaime Delgado Linares

#include <iostream>
using namespace std;

int apariciones(int u[], int numu, int v[], int numv);
int apariciones1(int u[], int i, int v[], int j);
int main(){
   int u[5]={1,3,8,20,51};
   int v[6]={8,15,19,20,30,41};
   int r = apariciones(u,5,v,6);
   cout << "Tienen " << r << " numero repetidos" << endl;
   int x[5]={1,3,8,20,30};
   int z[8]={1,3,5,8,30,41,51,60};
   r = apariciones(x,5,z,8);
   cout << "Tienen " << r << " numero repetidos" << endl;
   return 0;
}
//Pre = numn>0, numv>0, u[numu]<u[numu+1], v[numv]<v[numv+1]
// No se pueden meter arrays vacios y tienen que estar en orden estrictamente creciente
int apariciones(int u[], int numu, int v[], int numv){
   return apariciones1(u,numu-1,v,numv-1);
}
int apariciones1(int u[], int i, int v[], int j){
   if(i==-1||j==-1){  //d1=>i==-1||j==-1      Caso base (He terminado de recorrer uno de los vectores por lo menos)
      return 0;       //g(i==-1||j==-1) = 0   Solucion caso directo
   }else if(u[i]==v[j]){ // nod1=>u[i]==v[j] 
      return 1 + apariciones1(u,i-1,v,j-1);  //Descomposicion recursiva apariciones1(u,i,v,j)=(u,i-1,v,j-1)
                                             //Funcion de combinacion 1 + apariciones1(u,i-1,v,j-1)
   }else if(u[i]<v[j]){ // nod1=>u[i]<v[j] 
      return apariciones1(u, i, v, j-1);    //Descomposicion recursiva apariciones1(u,i,v,j)=(u,i,v,j-1)
                                             //Funcion de combinacion apariciones1(u,i,v,j-1)
   }else{ // nod1=>u[i]>v[j] 
      return apariciones1(u, i-1, v, j);   //Descomposicion recursiva apariciones1(u,i,v,j)=(u,i-1,v,j)
                                              //Funcion de combinacion apariciones1(u,i-1,v,j)
   }
}
/* Funcion de acotacion:
Al avanzar la recursion, i o j se van acercando a 0 i se cumple que numu-1<numu && numv-1<numv
Ecuaciones de recurrencia:
T(n){ si n=-1 0
     { T(n-1) + 4(evaluar condiciones)
  T(n)= T(n-1)+4
      = T(n-2)+4+4
      = T(n-3)+4+4+4
      = T(n-k)+4k
      =4n <= Esta en O(n)

*/