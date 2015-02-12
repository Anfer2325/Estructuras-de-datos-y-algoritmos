#include <iostream>
#include "Lista.h"
#include "Pila.h"
using namespace std;

typedef struct{
	char num;
	char palo;
	unsigned int cont;
}tCarta;


bool comprueba(int& montones, Lista<Pila<tCarta>>&mesa, tCarta carta, tCarta anterior, int pos, Lista<Pila<tCarta>>::Iterador ita, Lista<Pila<tCarta>>::Iterador itb){
	bool cambio = false;
	if(carta.num == anterior.num || carta.palo == anterior.palo){
		Pila<tCarta> pilaAuxApilar = mesa.elem(pos-2);
		pilaAuxApilar.apila(ita.elem().cima());
		Pila<tCarta> pilaAuxDesapilar  = mesa.elem(pos-1);
		pilaAuxDesapilar.desapila();

		if(!pilaAuxDesapilar.esVacia()){
			ita = mesa.borra(ita);
			mesa.insertar(pilaAuxDesapilar, ita);

		}else if(pilaAuxDesapilar.esVacia()){
			ita = mesa.borra(ita);
			montones--;
		}


		itb = mesa.borra(itb); /*borra la posicion a la que apunta el iterador 
							   y pasa a apuntar a la posicion en la que estaba el elemento borrado*/
		mesa.insertar(pilaAuxApilar, itb);//Se inserta justo antes de donde esta apuntado itb
		pilaAuxDesapilar.~Pila();
		pilaAuxApilar.~Pila();
		cambio = true;
	}   

	return cambio;
}


int main(){
	tCarta carta;
	tCarta anterior;
	bool cambio;
	int montones = 1; //Los montones de cartas que hay al principio

	cin >> carta.num;

	while(carta.num != '#'){
		Lista<Pila<tCarta>> mesa;
		Pila<tCarta> p;
		cin >> carta.palo;
		carta.cont = 1;
		p.apila(carta);
		mesa.ponDr(p);

		//Ponemos todas las cartas encima de la mesa
		while(carta.cont !=52){
			cin >> carta.num;
			cin >> carta.palo;
			Pila<tCarta> p;
			p.apila(carta);
			montones++;
			mesa.ponDr(p);
			carta.cont++;
		}
		
		Lista<Pila<tCarta>>::Iterador ita = mesa.principio();
		Lista<Pila<tCarta>>::Iterador itb = mesa.principio();
		cout << "BIEN" << endl;
		//El iterador A va una carta por delante
		do{
			int pos = 1;
			cambio  = false;
			Lista<Pila<tCarta>>::Iterador ita = mesa.principio();
			Lista<Pila<tCarta>>::Iterador itb = mesa.principio();
			anterior = itb.elem().cima();
			ita.avanza();
			pos++;
			while(ita != mesa.final() && !cambio ){
				carta = ita.elem().cima();
				cambio = comprueba(montones, mesa, carta, anterior, pos, ita, itb);
				anterior = carta;
				ita.avanza();
				itb.avanza();
				pos++;
			}
		}while(ita != mesa.final() && cambio);

		if(montones > 1){
			cout << montones<< " Piles remaining: ";
		}else cout << montones << " Pile remaining: ";

		Lista<Pila<tCarta>> :: Iterador itf = mesa.principio();
		while(itf != mesa.final()){
			cout << itf.elem().numElems() << " ";
			itf.avanza();
		}
	}
	return 0;
}