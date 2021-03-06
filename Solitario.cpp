#include <iostream>
/*
  Definici�n de algunas excepciones de las distintas
  implementaciones de los TADs.

  Estructura de Datos y Algoritmos
  Facultad de Inform�tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G�mez Mart�n, 2012
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


// Macro para declarar las clases de tipo excepci�n
// que heredan de ExcepcionConMensaje, para ahorrar
// escribir muchas veces lo mismo...
#define DECLARA_EXCEPCION(Excepcion) \
class Excepcion : public ExcepcionTAD { \
public: \
Excepcion() {}; \
Excepcion(const std::string &msg) : ExcepcionTAD(msg) {} \
};

/**
 Excepci�n generada por algunas operaciones de las pilas.
 */
DECLARA_EXCEPCION(EPilaVacia);

/**
 Excepci�n generada por algunas de las operaciones de las colas.
 */
DECLARA_EXCEPCION(EColaVacia);

/**
 Excepci�n generada por algunas operaciones de las colas dobles.
 */
DECLARA_EXCEPCION(EDColaVacia);

/**
 Excepci�n generada por algunas operaciones de las listas.
 */
DECLARA_EXCEPCION(EListaVacia);

/**
 Excepci�n generada por accesos incorrectos a las listas
 (tanto a un n�mero de elemento incorrecto como por
 mal manejo de los iteradores).
 */
DECLARA_EXCEPCION(EAccesoInvalido);

/**
 Excepci�n generada por algunas operaciones de los
 �rboles binarios.
 */
DECLARA_EXCEPCION(EArbolVacio);

/**
 Excepci�n generada por algunas operaciones de los
 �rboles de b�squeda.
 */
DECLARA_EXCEPCION(EClaveErronea);


#endif // __EXCEPCIONES_H
/**
  @file Pila.h

  Implementaci�n del TAD Pila utilizando un
  vector din�mico cuyo tama�o va creciendo si
  es necesario.

  Estructura de Datos y Algoritmos
  Facultad de Inform�tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G�mez Mart�n, 2012
*/
#ifndef __PILA_H
#define __PILA_H


/**
 Implementaci�n del TAD Pila utilizando vectores din�micos.

 Las operaciones son:

 - PilaVacia: -> Pila. Generadora implementada en el
   constructor sin par�metros.
 - apila: Pila, Elem -> Pila. Generadora
 - desapila: Pila - -> Pila. Modificadora parcial.
 - cima: Pila - -> Elem. Observadora parcial.
 - esVacia: Pila -> Bool. Observadora.
 - numElems: Pila -> Entero. Observadora.

 @author Marco Antonio G�mez Mart�n
 */
template <class T>
class Pila {
public:

	/** Tama�o inicial del vector din�mico. */
	enum { TAM_INICIAL = 10 };

	/** Constructor; operaci�n PilaVacia */
	Pila() {
		inicia();
	}

	/** Destructor; elimina el vector. */
	~Pila() {
		libera();
	}

	/**
	 Apila un elemento. Operaci�n generadora.

	 @param elem Elemento a apilar.
	*/
	void apila(const T &elem) {
		if (_numElems == _tam)
			amplia();
		_v[_numElems] = elem;
		_numElems++;
	}
	
	/**
	 Desapila un elemento. Operaci�n modificadora parcial,
	 que falla si la pila est� vac�a.

	 desapila(Apila(elem, p)) = p
	 error: desapila(PilaVacia)
	*/
	void desapila() {
		if (esVacia())
			throw EPilaVacia();
		--_numElems;
	}

	/**
	 Devuelve el elemento en la cima de la pila. Operaci�n
	 observadora parcial, que falla si la pila est� vac�a.

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
	 Devuelve true si la pila no tiene ning�n elemento.

	 esVacia(PilaVacia) = true
	 esVacia(Apila(elem, p)) = false

	 @return true si la pila no tiene ning�n elemento.
	 */
	bool esVacia() const {
		return _numElems == 0;
	}

	/**
	 Devuelve el n�mero de elementos que hay en la
	 pila.
	 numElems(PilaVacia) = 0
	 numElems(Apila(elem, p)) = 1 + numElems(p)

	 @return N�mero de elementos.
	 */
	int numElems() const {
		return _numElems;
	}

	// //
	// M�TODOS DE "FONTANER�A" DE C++ QUE HACEN VERS�TIL
	// A LA CLASE
	// //

	/** Constructor copia */
	Pila(const Pila<T> &other) {
		copia(other);
	}

	/** Operador de asignaci�n */
	Pila<T> &operator=(const Pila<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci�n. */
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

	/** Tama�o del vector _v. */
	unsigned int _tam;

	/** N�mero de elementos reales guardados. */
	unsigned int _numElems;
};

#endif // __PILA_H
/**
  @file Lista.h

  Implementaci�n del TAD lista, utilizando una 
  lista doblemente enlazada.

  Estructura de Datos y Algoritmos
  Facultad de Inform�tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G�mez Mart�n, 2012
*/
#ifndef __LISTA_H
#define __LISTA_H

#include <cassert>

/**
 Implementaci�n del TAD Pila utilizando vectores din�micos.

 Las operaciones son:

 - ListaVacia: -> Lista. Generadora implementada en el
   constructor sin par�metros.
 - Cons: Lista, Elem -> Lista. Generadora.
 - ponDr: Lista, Elem -> Lista. Modificadora.
 - primero: Lista - -> Elem. Observadora parcial
 - resto: Lista - -> Lista. Modificadora parcial
 - ultimo: Lista - -> Elem. Observadora parcial
 - inicio: Lista - -> Lista. Modificadora parcial
 - esVacia: Lista -> Bool. Observadora
 - numElems: Lista -> Elem. Obervadora.
 - elem: Lista, Entero - -> Elem. Observador parcial.

 @author Marco Antonio G�mez Mart�n
 */
template <class T>
class Lista {
private:
	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y dos punteros, uno al nodo anterior y otro al nodo siguiente.
	 Ambos punteros podr�an ser NULL si el nodo es el primero
	 y/o �ltimo de la lista enlazada.
	 */
	class Nodo {
	public:
		Nodo() : _sig(NULL), _ant(NULL) {}
		Nodo(const T &elem) : _elem(elem), _sig(NULL), _ant(NULL) {}
		Nodo(Nodo *ant, const T &elem, Nodo *sig) : 
		    _elem(elem), _sig(sig), _ant(ant) {}

		T _elem;
		Nodo *_sig;
		Nodo *_ant;
	};

public:

	/** Constructor; operaci�n ListaVacia. */
	Lista() : _prim(NULL), _ult(NULL), _numElems(0) {}

	/** Destructor; elimina la lista doblemente enlazada. */
	~Lista() {
		libera();
	}

	/**
	 A�ade un nuevo elemento en la cabeza de la lista.
	 Operaci�n generadora.

	 @param elem Elemento que se a�ade en la cabecera de
	 la lista.
	*/
	void Cons(const T &elem) {
		_numElems++;
		_prim = insertaElem(elem, NULL, _prim);
		if (_ult == NULL)
			_ult = _prim;
	}

	/**
	 A�ade un nuevo elemento al final de la lista (a la 
	 "derecha"). Operaci�n modificadora.

	 ponDr(e, ListaVacia) = Cons(e, ListaVacia)
	 ponDr(e, Cons(x, xs)) = Cons(x, ponDr(e, xs))
	*/
	void ponDr(const T &elem) {
		_numElems++;
		_ult = insertaElem(elem, _ult, NULL);
		if (_prim == NULL)
			_prim = _ult;
	}

	/**
	 Devuelve el valor almacenado en la cabecera de la
	 lista. Es un error preguntar por el primero de
	 una lista vac�a.

	 primero(Cons(x, xs)) = x
	 error primero(ListaVacia)

	 @return Elemento en la cabecera de la lista.
	 */
	const T &primero() const {
		if (esVacia())
			throw EListaVacia();
		return _prim->_elem;
	}

	/**
	 Devuelve el valor almacenado en la �ltima posici�n
	 de la lista (a la derecha).
	 Es un error preguntar por el primero de una lista vac�a.

	 ultimo(Cons(x, xs)) = x           SI esVacia(xs)
	 ultimo(Cons(x, xs)) = ultimo(xs)  SI !esVacia(xs)
	 error ultimo(ListaVacia)

	 @return Elemento en la cola de la lista.
	 */
	const T &ultimo() const {
		if (esVacia())
			throw EListaVacia();

		return _ult->_elem;
	}

	/**
	 Elimina el primer elemento de la lista.
	 Es un error intentar obtener el resto de una lista vac�a.

	 resto(Cons(x, xs)) = xs
	 error resto(ListaVacia)
	*/
	void resto() {
		if (esVacia())
			throw EListaVacia();

		Nodo *aBorrar = _prim;
		_prim = _prim->_sig;
		borraElem(aBorrar);
		if (_prim == NULL)
			_ult = NULL;
		--_numElems;
	}

	/**
	 Elimina el �ltimo elemento de la lista.
	 Es un error intentar obtener el inicio de una lista vac�a.

	 inicio(Cons(x, ListaVacia)) = ListaVacia
	 inicio(Cons(x, xs)) = Cons(x, inicio(xs)) SI !esVacia(xs)
	 error inicio(ListaVacia)
	*/
	void inicio() {
		if (esVacia())
			throw EListaVacia();

		Nodo *aBorrar = _ult;
		_ult = _ult->_ant;
		borraElem(aBorrar);
		if (_ult == NULL)
			_prim = NULL;
		--_numElems;
	}

	/**
	 Operaci�n observadora para saber si una lista
	 tiene o no elementos.

	 esVacia(ListaVacia) = true
	 esVacia(Cons(x, xs)) = false

	 @return true si la lista no tiene elementos.
	 */
	bool esVacia() const {
		return _prim == NULL;
	}

	/**
	 Devuelve el n�mero de elementos que hay en la
	 lista.
	 numElems(ListaVacia) = 0
	 numElems(Cons(x, xs)) = 1 + numElems(xs)

	 @return N�mero de elementos.
	 */
	unsigned int numElems() const {
		return _numElems;
	}

	/**
	 Devuelve el elemento i-�simo de la lista, teniendo
	 en cuenta que el primer elemento (primero())
	 es el elemento 0 y el �ltimo es numElems()-1,
	 es decir idx est� en [0..numElems()-1].
	 Operaci�n observadora parcial que puede fallar
	 si se da un �ndice incorrecto. El �ndice es
	 entero sin signo, para evitar que se puedan
	 pedir elementos negativos.

	 elem(0, Cons(x, xs)) = x
	 elem(n, Cons(x, xs)) = elem(n-1, xs) si n > 0
	 error elem(n, xs) si !( 0 <= n < numElems(xs) )
	*/
	const T &elem(unsigned int idx) const {
		if (idx >= _numElems)
			throw EAccesoInvalido();

		Nodo *aux = _prim;
		for (int i = 0; i < idx; ++i)
			aux = aux->_sig;

		return aux->_elem;
	}

	/**
	 Clase interna que implementa un iterador sobre
	 la lista que permite recorrer la lista e incluso
	 alterar el valor de sus elementos.
	 */
	class Iterador {
	public:
		void avanza() {
			if (_act == NULL) throw EAccesoInvalido();
			_act = _act->_sig;
		}

		const T &elem() const {
			if (_act == NULL) throw EAccesoInvalido();
			return _act->_elem;
		}

		void pon(const T &elem) {
			if (_act == NULL) throw EAccesoInvalido();
			_act->_elem = elem;
		}

		bool operator==(const Iterador &other) const {
			return _act == other._act;
		}

		bool operator!=(const Iterador &other) const {
			return !(this->operator==(other));
		}
	protected:
		// Para que pueda construir objetos del
		// tipo iterador
		friend class Lista;

		Iterador() : _act(NULL) {}
		Iterador(Nodo *act) : _act(act) {}

		// Puntero al nodo actual del recorrido
		Nodo *_act;
	};
	
	/**
	 Devuelve el iterador al principio de la lista.
	 @return iterador al principio de la lista;
	 coincidir� con final() si la lista est� vac�a.
	 */
	Iterador principio() {
		return Iterador(_prim);
	}

	/**
	 @return Devuelve un iterador al final del recorrido
	 (fuera de �ste).
	 */
	Iterador final() const {
		return Iterador(NULL);
	}

	/**
	 Permite eliminar de la lista el elemento
	 apuntado por el iterador que se pasa como par�metro.
	 El iterador recibido DEJA DE SER V�LIDO. En su
	 lugar, deber� utilizarse el iterador devuelto, que
	 apuntar� al siguiente elemento al borrado.
	 @param it Iterador colocado en el elemento que se
	 quiere borrar.
	 @return Nuevo iterador colocado en el elemento siguiente
	 al borrado (podr�a coincidir con final() si el
	 elemento que se borr� era el �ltimo de la lista).
	 */
	Iterador borra(const Iterador &it) {
		if (it._act == NULL)
			throw EAccesoInvalido();

		// Cubrimos los casos especiales donde
		// borramos alguno de los extremos
		if (it._act == _prim) {
			resto();
			return Iterador(_prim);
		} else if (it._act == _ult) {
			inicio();
			return Iterador(NULL);
		} else {
			// El elemento a borrar es interno a la lista.
			--_numElems;
			Nodo *sig = it._act->_sig;
			borraElem(it._act);
			return Iterador(sig);
		}
	}

	/**
	 M�todo para insertar un elemento en la lista
	 en el punto marcado por el iterador. En concreto,
	 se a�ade _justo antes_ que el elemento actual. Es
	 decir, si it==l.primero(), el elemento insertado se
	 convierte en el primer elemento (y el iterador
	 apuntar� al segundo). Si it==l.final(), el elemento
	 insertado ser� el �ltimo (e it seguir� apuntando
	 fuera del recorrido).
	 @param elem Valor del elemento a insertar.
	 @param it Punto en el que insertar el elemento.
	 */
	void insertar(const T &elem, const Iterador &it) {

		// Caso especial: �a�adir al principio?
		if (_prim == it._act) {
			Cons(elem);
		} else
		// Caso especial: �a�adir al final?
		if (it._act == NULL) {
			ponDr(elem);
		}
		// Caso normal
		else {
			insertaElem(elem, it._act->_ant, it._act);
		}
	}

	// //
	// M�TODOS DE "FONTANER�A" DE C++ QUE HACEN VERS�TIL
	// A LA CLASE
	// //

	/** Constructor copia */
	Lista(const Lista<T> &other) : _prim(NULL), _ult(NULL) {
		copia(other);
	}

	/** Operador de asignaci�n */
	Lista<T> &operator=(const Lista<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci�n. */
	bool operator==(const Lista<T> &rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		Nodo *p1 = _prim;
		Nodo *p2 = rhs._prim;
		while ((p1 != NULL) && (p2 != NULL)) {
			if (p1->_elem != p2->_elem)
				return false;
			p1 = p1->_sig;
			p2 = p2->_sig;
		}

		return (p1 == NULL) && (p2 == NULL);
	}

	bool operator!=(const Lista<T> &rhs) const {
		return !(*this == rhs);
	}


protected:

	void libera() {
		libera(_prim);
		_prim = NULL;
		_ult = NULL;
	}

	void copia(const Lista<T> &other) {
		// En vez de trabajar con punteros en la inserci�n,
		// usamos ponDr
		_prim = 0;
		_numElems = 0;

		Nodo *act = other._prim;
		while (act != NULL) {
			ponDr(act->_elem);
			act = act->_sig;
		}
	}

private:


	/**
	 Inserta un elemento entre el nodo1 y el nodo2.
	 Devuelve el puntero al nodo creado.
	 Caso general: los dos nodos existen.
	    nodo1->_sig == nodo2
	    nodo2->_ant == nodo1
	 Casos especiales: alguno de los nodos no existe
	    nodo1 == NULL y/o nodo2 == NULL
	*/
	static Nodo *insertaElem(const T &e, Nodo *nodo1, Nodo *nodo2) {
		Nodo *nuevo = new Nodo(nodo1, e, nodo2);
		if (nodo1 != NULL)
			nodo1->_sig = nuevo;
		if (nodo2 != NULL)
			nodo2->_ant = nuevo;
		return nuevo;
	}

	/**
	 Elimina el nodo n. Si el nodo tiene nodos antes
	 o despu�s, actualiza sus punteros anterior y siguiente.
	 Caso general: hay nodos anterior y siguiente.
	 Casos especiales: algunos de los nodos (anterior o siguiente
	 a n) no existen.
	*/
	static void borraElem(Nodo *n) {
		assert(n != NULL);
		Nodo *ant = n->_ant;
		Nodo *sig = n->_sig;
		if (ant != NULL)
			ant->_sig = sig;
		if (sig != NULL)
			sig->_ant = ant;
		delete n;
	}

	/**
	 Elimina todos los nodos de la lista enlazada cuyo
	 primer nodo se pasa como par�metro.
	 Se admite que el nodo sea NULL (no habr� nada que
	 liberar). En caso de pasarse un nodo v�lido,
	 su puntero al nodo anterior debe ser NULL (si no,
	 no ser�a el primero de la lista!).
	 */
	static void libera(Nodo *prim) {
		assert(!prim || !prim->_ant);

		while (prim != NULL) {
			Nodo *aux = prim;
			prim = prim->_sig;
			delete aux;
		}
	}

	// Puntero al primer y �ltimo elemento
	Nodo *_prim, *_ult;

	// N�mero de elementos (n�mero de nodos entre _prim y _ult)
	unsigned int _numElems;
};

#endif // __LISTA_ENLAZADA_H
/**
  @file Cola.h

  Implementaci�n del TAD Cola utilizando una
  lista enlazada de nodos.

  Estructura de Datos y Algoritmos
  Facultad de Inform�tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G�mez Mart�n, 2012
*/
#ifndef __COLA_LISTA_ENLAZADA_H
#define __COLA_LISTA_ENLAZADA_H


/**
 Implementaci�n del TAD Cola utilizando una lista enlazada.

 Las operaciones son:

 - ColaVacia: -> Cola. Generadora implementada en el
   constructor sin par�metros.
 - PonDetras: Cola, Elem -> Cola. Generadora
 - quitaPrim: Cola - -> Cola. Modificadora parcial.
 - primero: Cola - -> Elem. Observadora parcial.
 - esVacia: Cola -> Bool. Observadora.
 - numElems: Cola -> Entero. Observadora.

 @author Marco Antonio G�mez Mart�n
 */
template <class T>
class Cola {
public:

	/** Constructor; operacion ColaVacia */
	Cola() : _prim(NULL), _ult(NULL), _numElems(0) {
	}

	/** Destructor; elimina la lista enlazada. */
	~Cola() {
		libera();
		_prim = _ult = NULL;
	}

	/**
	 A�ade un elemento en la parte trasera de la cola.
	 Operaci�n generadora.

	 @param elem Elemento a a�adir.
	*/
	void ponDetras(const T &elem) {
		Nodo *nuevo = new Nodo(elem, NULL);

		if (_ult != NULL)
			_ult->_sig = nuevo;
		_ult = nuevo;
		// Si la cola estaba vac�a, el primer elemento
		// es el que acabamos de a�adir
		if (_prim == NULL)
			_prim = nuevo;
		_numElems++;
	}

	/**
	 Elimina el primer elemento de la cola.
	 Operaci�n modificadora parcial, que falla si 
	 la cola est� vac�a.

	 quitaPrim(PonDetras(elem, ColaVacia)) = ColaVacia
	 quitaPrim(PonDetras(elem, xs)) = PonDetras(elem, quitaPrim(xs)) si !esVacia(xs)
	 error: quitaPrim(ColaVacia)
	*/
	void quitaPrim() {
		if (esVacia())
			throw EColaVacia();
		Nodo *aBorrar = _prim;
		_prim = _prim->_sig;
		delete aBorrar;
		--_numElems;
		// Si la cola se qued� vac�a, no hay
		// �ltimo
		if (_prim == NULL)
			_ult = NULL;
	}

	/**
	 Devuelve el primer elemento de la cola. Operaci�n
	 observadora parcial, que falla si la cola est� vac�a.

	 primero(PonDetras(elem, ColaVacia)) = elem
	 primero(PonDetras(elem, xs)) = primero(xs) si !esVacia(xs)
	 error: primero(ColaVacia)

	 @return El primer elemento de la cola.
	 */
	const T &primero() const {
		if (esVacia())
			throw EColaVacia();
		return _prim->_elem;
	}

	/**
	 Devuelve true si la cola no tiene ning�n elemento.

	 esVacia(Cola) = true
	 esVacia(PonDetras(elem, p)) = false

	 @return true si la cola no tiene ning�n elemento.
	 */
	bool esVacia() const {
		return _prim == NULL;
	}

	/**
	 Devuelve el n�mero de elementos que hay en la
	 cola.
	 numElems(ColaVacia) = 0
	 numElems(PonDetras(elem, p)) = 1 + numElems(p)

	 @return N�mero de elementos.
	 */
	int numElems() const {
		return _numElems;
	}

	// //
	// M�TODOS DE "FONTANER�A" DE C++ QUE HACEN VERS�TIL
	// A LA CLASE
	// //

	/** Constructor copia */
	Cola(const Cola<T> &other) : _prim(NULL), _ult(NULL) {
		copia(other);
	}

	/** Operador de asignaci�n */
	Cola<T> &operator=(const Cola<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci�n. */
	bool operator==(const Cola<T> &rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		Nodo *p1 = _prim;
		Nodo *p2 = rhs._prim;
		while ((p1 != NULL) && (p2 != NULL)) {
			if (p1->_elem != p2->_elem)
				return false;
			p1 = p1->_sig;
			p2 = p2->_sig;
		}

		return (p1 == NULL) && (p2 == NULL);
	}

	bool operator!=(const Cola<T> &rhs) const {
		return !(*this == rhs);
	}

protected:

	void libera() {
		libera(_prim);
	}

	void copia(const Cola &other) {

		if (other.esVacia()) {
			_prim = _ult = NULL;
			_numElems = 0;
		} else {
			Nodo *act = other._prim;
			Nodo *ant;
			_prim = new Nodo(act->_elem);
			ant = _prim;
			while (act->_sig != NULL) {
				act = act->_sig;
				ant->_sig = new Nodo(act->_elem);
				ant = ant->_sig;
			}
			_ult = ant;
			_numElems = other._numElems;
		}
	}

private:

	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y un puntero al nodo siguiente, que podr�a ser NULL si
	 el nodo es el �ltimo de la lista enlazada.
	 */
	class Nodo {
	public:
		Nodo() : _sig(NULL) {}
		Nodo(const T &elem) : _elem(elem), _sig(NULL) {}
		Nodo(const T &elem, Nodo *sig) : 
		    _elem(elem), _sig(sig) {}

		T _elem;
		Nodo *_sig;
	};

	/**
	 Elimina todos los nodos de la lista enlazada cuyo
	 primer nodo se pasa como par�metro.
	 Se admite que el nodo sea NULL (no habr� nada que
	 liberar).
	 */
	static void libera(Nodo *prim) {
		while (prim != NULL) {
			Nodo *aux = prim;
			prim = prim->_sig;
			delete aux;
		}
	}

	/** Puntero al primer elemento. */
	Nodo *_prim;

	/** Puntero al �ltimo elemento. */
	Nodo *_ult;

	/** N�mero de elementos */
	int _numElems;
};

#endif // __PILA_LISTA_ENLAZADA_H
using namespace std;

struct Solitario{
	Lista<Pila<string>> mesa; // mesa
	int ultimoMazo;  // posicion del ultimo mazo que llevamos puesto en la mesa

	//Termina el juego y pone todo a cero
	void fin(/*Cola<string> &c*/){
		//cout << "FIN!!!!!!!!!!!" << endl;
		Lista<Pila<string>>::Iterador it = mesa.principio();
		cout << ultimoMazo;
		if(ultimoMazo==1){
			cout << " pile remaining:" ;
		}else{
			cout << " piles remaining:";
		}
		while(it!=mesa.final()){
			Pila<string> aux = it.elem();
			cout << " " << aux.numElems();
			it = mesa.borra(it);
		}
		/*while(!c.esVacia()){
			c.quitaPrim();
		}*/
		cout << endl << endl;
	}

	//Elimina la primera carta del mazo que quieras
	void eliminaCarta(int pos){
		//cout << "LOOOO HACEEEE ";
		Lista<Pila<string>>::Iterador it = mesa.principio();
		while(pos!=0){
			it.avanza();
			pos--;
		}
		Pila<string> aux = it.elem();
		aux.desapila();
		mesa.insertar(aux,it);
		it = mesa.borra(it);
		encajaPaquete();
		//cout << "BIEEEEEEN" << endl;
	}

	//Devuelve la primera carta del monton que tu quieras
	string primeraCarta(int pos){
		//cout << "LOOOO HACEEEE ";
		Lista<Pila<string>>::Iterador it = mesa.principio();
		while(pos!=0){
			it.avanza();
			pos--;
		}
		Pila<string> aux = it.elem();
		//cout << "BIEEEEEEN" << endl;
		return aux.cima();
	}

	//Quita espacios libres entre las pilas
	void encajaPaquete(){
		//cout << "LOOOO HACEEEE ";
		Lista<Pila<string>>::Iterador it =mesa.principio();
		while(it!=mesa.final()){
			Pila<string> aux = it.elem();
			if(aux.esVacia()){
				it = mesa.borra(it);
				ultimoMazo--;
				//cout <<"BORRAMOS PARA ENCAJAR UN HUECO LIBRE" << endl; 
			}else{
				it.avanza();
			}
		}
		//cout << "BIEEEEEEN" << endl;
	}

	//Apila en la posicion que quieras una carta
	void apilaEn (int pos, string carta){
		if(ultimoMazo==pos){
			Pila<string> nuevaPila;
			nuevaPila.apila(carta);
			mesa.ponDr(nuevaPila);
			encajaPaquete();
		}else{
			Lista<Pila<string>>::Iterador it = mesa.principio();
			while(pos!=0){
				it.avanza();
				pos--;
			}
			Pila<string> nuevaPila = it.elem();
			nuevaPila.apila(carta);
			it = mesa.borra(it);
			mesa.insertar(nuevaPila,it);
			encajaPaquete();
		}
		
		//cout << "Apilamiento correcto" << endl;
	}

	//Busca en que mazo puede ir desde una posicion dada. Devuelve su posicion (-1 si no se puede mover)
	int buscaCarta(string carta, int posicion){
		//cout << "LOOOO HACEEEE ";
		int posDevolver=-1;
		int anterior = posicion-1;
		int terceraAnterior = posicion-3;
		//cout << "anterior: " << anterior << " , terceraAnterior: " << terceraAnterior << endl;
	
		if(anterior>=0){  //Comprobamos si se puede mover a la anterior
			int anteriorAux = anterior;
			Lista<Pila<string>>::Iterador it = mesa.principio();
			while(anteriorAux!=0){
				it.avanza();
				anteriorAux--;
			}
			Pila<string> posibleMazo = it.elem();
			if(posibleMazo.cima()[0] == carta[0]){  //Coincide numero
				posDevolver = anterior;
			}else if(posibleMazo.cima()[1] == carta[1]){ //Coincide palo
				posDevolver = anterior;
			}
		}

		if(terceraAnterior>=0){ //Comprobamos si se puede mover a la tercera anterior
			int terceraAnteriorAux = terceraAnterior;
			Lista<Pila<string>>::Iterador it = mesa.principio();
			while(terceraAnteriorAux!=0){
				it.avanza();
				terceraAnteriorAux--;
			}
			Pila<string> posibleMazo = it.elem();
			if(posibleMazo.cima()[0] == carta[0]){  //Coincide numero
				posDevolver = terceraAnterior;
			}else if(posibleMazo.cima()[1] == carta[1]){ //Coincide palo
				posDevolver = terceraAnterior;
			}
		}
		//cout << "BIEEEEEEN" << endl;
		return posDevolver;
	}

	//Hace la simulacion del solitario recibiendo un mazo (cola de string)
	void jugar(Cola<string> &c){
		int posAMover=0;
		//cout << "A JUGAR!! " << c.numElems() << " cartas en el mazo" << endl;
		ultimoMazo=0;
		string carta;
		while(!c.esVacia()){
			carta = c.primero();
			//cout << carta << " <---- SIGUIENTE CARTA!! " << endl;
			//cout << "Apila la carta " << carta << " en la posicion " << ultimoMazo << endl;
			//apilaEn(ultimoMazo+1,carta);

			posAMover = buscaCarta(carta, ultimoMazo);
			
			//cout << posAMover << "<----- posAMover" << endl;
			if(posAMover!=-1){  // Se ha encontrado alguna posicion a la que mover la carta asi que apilamos
				//cout << "Mueve la carta "<< carta << " a la posicion " << posAMover << endl;
				apilaEn(posAMover, carta);
				//Mostramos lo que llevamos hasta el momento
				/*Lista<Pila<string>>::Iterador it = mesa.principio();
				while(it!=mesa.final()){
					Pila<string> aux = it.elem();
					cout << aux.cima() << " ";
					it.avanza();
				}
				cout << endl;
				*/

				int numMazos = 0;
				carta = primeraCarta(0);
				while(numMazos!=ultimoMazo){
					posAMover = buscaCarta(carta, numMazos);
					//cout << "Mueve la carta "<<carta<<" a la posicion " << posAMover << endl;
					if(posAMover==-1){
						numMazos++;
						if(numMazos!=ultimoMazo){
							carta = primeraCarta(numMazos);
						}
					}else{
						//cout << "APILA" << endl;
						apilaEn(posAMover, carta);
						//cout << "ELIMINA" << endl;
						eliminaCarta(numMazos);
						numMazos=0;
						carta=primeraCarta(0);
						//Mostramos lo que llevamos hasta el momento
						/*Lista<Pila<string>>::Iterador it = mesa.principio();
						while(it!=mesa.final()){
							Pila<string> aux = it.elem();
							cout << aux.cima() << " ";
							it.avanza();
						}
						cout << endl;
						*/
					}
					
				}
				
			}else{
				//cout << "Mueve la carta "<< carta << " a la posicion " << ultimoMazo << endl;
				ultimoMazo++;
				apilaEn(ultimoMazo,carta);
				//Mostramos lo que llevamos hasta el momento
				/*Lista<Pila<string>>::Iterador it = mesa.principio();
				while(it!=mesa.final()){
					Pila<string> aux = it.elem();
					cout << aux.cima() << " ";
					it.avanza();
				}
				cout << endl;
				*/
				
			}
			
			if(!c.esVacia()){
				c.quitaPrim();
			}
		}
		//cout << "Dejamos de jugar!" << endl;
		fin();
	}
	
};



int main(){
	Solitario solitario;
	Cola<string> mazo;
	int contadorCartas=1;
	string carta;
	cin >> carta;
	while(carta!="#"){
		mazo.ponDetras(carta);
		contadorCartas=1;
		while(contadorCartas!=52){
			cin >> carta;
			mazo.ponDetras(carta);
			contadorCartas++;
		}
		solitario.jugar(mazo);		
		//solitario.fin(/*mazo*/);
		cin >> carta;
	}
	
	return 0;
}