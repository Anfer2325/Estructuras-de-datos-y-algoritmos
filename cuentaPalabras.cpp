//Jaime Delgado Linares

#include <iostream>

/*
  Definición de algunas excepciones de las distintas
  implementaciones de los TADs.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Marco Antonio Gómez Martín, 2012
*/
#ifndef __EXCEPCIONES_H
#define __EXCEPCIONES_H

#include <string>
#include <iosfwd>
/**
 Clase de la que heredan todas las excepciones, y
 que proporciona el atributo que almacena el
 mensaje de error.
 */
class ExcepcionTAD {
public:
	ExcepcionTAD() {}
	ExcepcionTAD(const std::string &msg) : _msg(msg) {}

	const std::string msg() const { return _msg; }

	friend std::ostream &operator<<(std::ostream &out, const ExcepcionTAD &e);

protected:
	std::string _msg;
};

inline std::ostream &operator<<(std::ostream &out, const ExcepcionTAD &e) {
	out << e._msg;
	return out;
}


// Macro para declarar las clases de tipo excepción
// que heredan de ExcepcionConMensaje, para ahorrar
// escribir muchas veces lo mismo...
#define DECLARA_EXCEPCION(Excepcion) \
class Excepcion : public ExcepcionTAD { \
public: \
Excepcion() {}; \
Excepcion(const std::string &msg) : ExcepcionTAD(msg) {} \
};

/**
 Excepción generada por algunas operaciones de las pilas.
 */
DECLARA_EXCEPCION(EPilaVacia);

/**
 Excepción generada por algunas de las operaciones de las colas.
 */
DECLARA_EXCEPCION(EColaVacia);

/**
 Excepción generada por algunas operaciones de las colas dobles.
 */
DECLARA_EXCEPCION(EDColaVacia);

/**
 Excepción generada por algunas operaciones de las listas.
 */
DECLARA_EXCEPCION(EListaVacia);

/**
 Excepción generada por accesos incorrectos a las listas
 (tanto a un número de elemento incorrecto como por
 mal manejo de los iteradores).
 */
DECLARA_EXCEPCION(EAccesoInvalido);

/**
 Excepción generada por algunas operaciones de los
 árboles binarios.
 */
DECLARA_EXCEPCION(EArbolVacio);

/**
 Excepción generada al intentar acceder a un contenedor 
 asociativo con una clave incorrecta. 
 */
DECLARA_EXCEPCION(EClaveErronea);


#endif // __EXCEPCIONES_H



/**
  @file Pila.h

  Implementación del TAD Pila utilizando un
  vector dinámico cuyo tamaño va creciendo si
  es necesario.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Marco Antonio Gómez Martín, 2012
*/
#ifndef __PILA_H
#define __PILA_H


/**
 Implementación del TAD Pila utilizando vectores dinámicos.

 Las operaciones son:

 - PilaVacia: -> Pila. Generadora implementada en el
   constructor sin parámetros.
 - apila: Pila, Elem -> Pila. Generadora
 - desapila: Pila - -> Pila. Modificadora parcial.
 - cima: Pila - -> Elem. Observadora parcial.
 - esVacia: Pila -> Bool. Observadora.
 - numElems: Pila -> Entero. Observadora.

 @author Marco Antonio Gómez Martín
 */
template <class T>
class Pila {
public:

	/** Tamaño inicial del vector dinámico. */
	enum { TAM_INICIAL = 10 };

	/** Constructor; operación PilaVacia */
	Pila() {
		inicia();
	}

	/** Destructor; elimina el vector. */
	~Pila() {
		libera();
	}

	/**
	 Apila un elemento. Operación generadora.

	 @param elem Elemento a apilar.
	*/
	void apila(const T &elem) {
		if (_numElems == _tam)
			amplia();
		_v[_numElems] = elem;
		_numElems++;
	}
	
	/**
	 Desapila un elemento. Operación modificadora parcial,
	 que falla si la pila está vacía.

	 desapila(Apila(elem, p)) = p
	 error: desapila(PilaVacia)
	*/
	void desapila() {
		if (esVacia())
			throw EPilaVacia();
		--_numElems;
	}

	/**
	 Devuelve el elemento en la cima de la pila. Operación
	 observadora parcial, que falla si la pila está vacía.

	 cima(Apila(elem, p) = elem
	 error: cima(PilaVacia)

	 @return Elemento en la cima de la pila.
	 */
	const T &cima() const {
		if (esVacia())
			throw EPilaVacia();
		return _v[_numElems - 1];
	}

	/**
	 Devuelve true si la pila no tiene ningún elemento.

	 esVacia(PilaVacia) = true
	 esVacia(Apila(elem, p)) = false

	 @return true si la pila no tiene ningún elemento.
	 */
	bool esVacia() const {
		return _numElems == 0;
	}

	/**
	 Devuelve el número de elementos que hay en la
	 pila.
	 numElems(PilaVacia) = 0
	 numElems(Apila(elem, p)) = 1 + numElems(p)

	 @return Número de elementos.
	 */
	int numElems() const {
		return _numElems;
	}

	// //
	// MÉTODOS DE "FONTANERÍA" DE C++ QUE HACEN VERSÁTIL
	// A LA CLASE
	// //

	/** Constructor copia */
	Pila(const Pila<T> &other) {
		copia(other);
	}

	/** Operador de asignación */
	Pila<T> &operator=(const Pila<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparación. */
	bool operator==(const Pila<T> &rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		for (unsigned int i = 0; i < _numElems; ++i)
			if (_v[i] != rhs._v[i])
				return false;
		return true;
	}

	bool operator!=(const Pila<T> &rhs) const {
		return !(*this == rhs);
	}

protected:

	void inicia() {
		_v = new T[TAM_INICIAL];
		_tam = TAM_INICIAL;
		_numElems = 0;
	}

	void libera() {
		delete []_v;
		_v = NULL;
	}

	void copia(const Pila &other) {
		_tam = other._numElems + TAM_INICIAL;
		_numElems = other._numElems;
		_v = new T[_tam];
		for (unsigned int i = 0; i < _numElems; ++i)
			_v[i] = other._v[i];
	}

	void amplia() {
		T *viejo = _v;
		_tam *= 2;
		_v = new T[_tam];

		for (unsigned int i = 0; i < _numElems; ++i)
			_v[i] = viejo[i];

		delete []viejo;
	}

private:

	/** Puntero al array que contiene los datos. */
	T *_v;

	/** Tamaño del vector _v. */
	unsigned int _tam;

	/** Número de elementos reales guardados. */
	unsigned int _numElems;
};

#endif // __PILA_H


using namespace std;


void cuentaPalabras(){	
	unsigned int cont=0, i=0;
	bool nuevaPalabra=false;
	string cadena;
	Pila<string> p;
	do{
		getline(cin, cadena);
		p.apila(cadena);
	}while(!cin.eof());
	
	while(!p.esVacia()){
		string act = "";
		act = p.cima();
		while(i<act.size()){
			nuevaPalabra=true;
			while(i<act.size() && act[i]>='A' && act[i]<='z'){
				if(nuevaPalabra==true){
					cont++;
				}
				nuevaPalabra=false;
				i++;
			}
			i++;
		}
		if(cont!=0){
			cout << cont << endl;
		}
		
		cont=0;
		i=0;
		p.desapila();
	}
}

int main(){
	cuentaPalabras();
	return 0;
}