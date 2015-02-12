//Jaime Delgado Linares 
#include <iostream>
using namespace std;

int binario(int n){ //P={n>=0}
   /*Tengo que ir dividiendo al numero n entre 2, coger el resto (digito), y hacer la recursion 
   para el numero que me ha dado en el cociente.
   El caso base tendra que devolver 0 si n=0 y 1 si n=1
   La recursion se hará para n/2, y la recombinacion será el digito+10*binario(n/2)
   */
   int digito = n%2;
   if(n==0){ //Caso directo 1 -d1(n)=(n==0)  -g1(n)=0
      return 0;
   }else if(n==1){ //Caso directo 2 -d2(n)=(n==1) -g2(n)=1
      return 1;
   }else{ //Caso recursivo nodx(n) = (n>1)
      return digito + 10*binario(n/2);  //Funcion sucesor s(n)=n/2;
                                        //Funcion de combinacion c(n)= n%2 + 10*(binario(s(n)))
   }
   /*FUNCION DE COTA
   El tamaño del problema viene dado por el valor de n, que ha de disminuir en las
   sucesivas llamadas recursivas hasta llegar a 1 o 0:
   t(n) = n
   t(s(n)) < t(n) , n / 2 < n
   P0(n)^nod(n))->P0(s(n))
   n>=0^n>1 -> n>0->n/2>=0 */
} //Q={binario(n)}

int main(){
   int result = binario(9);
   cout << "el resultado de 9 es: " << result << endl;
   result = binario(25);
   cout << "el resultado de 25 es: " << result << endl;
   result = binario(109);
   cout << "el resultado de 109 es: " << result << endl;
   result = binario(43);
   cout << "el resultado de 43 es: " << result << endl;
   return 0;
}