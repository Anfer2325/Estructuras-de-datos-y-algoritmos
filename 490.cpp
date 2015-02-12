/*
	Resultado de concatenar
	Excepciones.h Cola.h DCola.h Lista.h PilaE.h Pila.h PilaLE.h 
	a un unico fichero, para su uso en las practicas de EDA
	
	Los ifndef/defines e includes tambien han sido movidos o 
	substituidos, para evitar redundancias.
	
	Este fichero compila limpiamente usando
	g++ -Wall (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2
	(el modo de compilacion usado en concursos)
	
	Autor: manuel.freire@fdi.ucm.es
	marzo de 2013
*/

#ifndef __LINEALES_H
#define __LINEALES_H
#include <iostream>
#include <string>
#include <iosfwd>
#include <cassert>
using namespace std;
/*
  Definición de algunas excepciones de las distintas
  implementaciones de los TADs.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Marco Antonio Gómez Martín, 2012
*/

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
 Excepción generada por algunas operaciones de las pilas.
 */
DECLARA_EXCEPCION(EPilaLlena);

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
 mal manejo de los 
 es).
 */
DECLARA_EXCEPCION(EAccesoInvalido);
/**
  @file Cola.h

  Implementación del TAD Cola utilizando una
  lista enlazada de nodos.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Marco Antonio Gómez Martín, 2012
*/
/**
 Implementación del TAD Cola utilizando una lista enlazada.

 Las operaciones son:

 - ColaVacia: -> Cola. Generadora implementada en el
   constructor sin parámetros.
 - PonDetras: Cola, Elem -> Cola. Generadora
 - quitaPrim: Cola - -> Cola. Modificadora parcial.
 - primero: Cola - -> Elem. Observadora parcial.
 - esVacia: Cola -> Bool. Observadora.
 - numElems: Cola -> Entero. Observadora.

 @author Marco Antonio Gómez Martín
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
	 Añade un elemento en la parte trasera de la cola.
	 Operación generadora.

	 @param elem Elemento a añadir.
	*/
	void ponDetras(const T &elem) {
		Nodo *nuevo = new Nodo(elem, NULL);

		if (_ult != NULL)
			_ult->_sig = nuevo;
		_ult = nuevo;
		// Si la cola estaba vacía, el primer elemento
		// es el que acabamos de añadir
		if (_prim == NULL)
			_prim = nuevo;
		_numElems++;
	}

	/**
	 Elimina el primer elemento de la cola.
	 Operación modificadora parcial, que falla si 
	 la cola está vacía.

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
		// Si la cola se quedó vacía, no hay
		// último
		if (_prim == NULL)
			_ult = NULL;
	}

	/**
	 Devuelve el primer elemento de la cola. Operación
	 observadora parcial, que falla si la cola está vacía.

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
	 Devuelve true si la cola no tiene ningún elemento.

	 esVacia(Cola) = true
	 esVacia(PonDetras(elem, p)) = false

	 @return true si la cola no tiene ningún elemento.
	 */
	bool esVacia() const {
		return _prim == NULL;
	}

	/**
	 Devuelve el número de elementos que hay en la
	 cola.
	 numElems(ColaVacia) = 0
	 numElems(PonDetras(elem, p)) = 1 + numElems(p)

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
	Cola(const Cola<T> &other) : _prim(NULL), _ult(NULL) {
		copia(other);
	}

	/** Operador de asignación */
	Cola<T> &operator=(const Cola<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparación. */
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
	 y un puntero al nodo siguiente, que podría ser NULL si
	 el nodo es el último de la lista enlazada.
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
	 primer nodo se pasa como parámetro.
	 Se admite que el nodo sea NULL (no habrá nada que
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

	/** Puntero al último elemento. */
	Nodo *_ult;

	/** Número de elementos */
	int _numElems;
};


/**
  @file DCola.h

  Implementación del TAD doble cola, utilizando una
  lista doblemente enlazada con nodo fantasma o
  cabecera.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Marco Antonio Gómez Martín, 2012
*/
/**
 Implementación del TAD Doble Cola utilizando una lista doblemente
 enlazada circular y con nodo fantasma.

 Las operaciones son:

 - DColaVacia: -> DCola. Generadora implementada en el
   constructor sin parámetros.
 - PonDetras: DCola, Elem -> DCola. Generadora
 - ponDelante: DCola, Elem -> DCola. Modificadora.
 - quitaPrim: DCola - -> DCola. Modificadora parcial
 - primero: DCola - -> Elem. Observadora parcial
 - quitaUlt: DCola - -> DCola. Modificadora parcial
 - ultimo: DCola - -> Elem. Observadora parcial
 - esVacia: DCola -> Bool. Observadora

 @author Marco Antonio Gómez Martín
 */
template <class T>
class DCola {
public:

	/** Constructor; operación DColaVacia. */
	DCola() {
		_fantasma = new Nodo();
		_fantasma->_sig = _fantasma;
		_fantasma->_ant = _fantasma;
		_numElems = 0;
	}

	/** Destructor; elimina la lista doblemente enlazada. */
	~DCola() {
		libera();
	}

	/**
	 Añade un elemento por la parte de atrás de la cola.
	 Es una operación generadora.
	*/
	void ponDetras(const T &e) {
		insertaElem(e, _fantasma->_ant, _fantasma);
		_numElems++;
	}

	/**
	 Devuelve el primer elemento de la cola; es una operación
	 observadora parcial, pues es un error preguntar por
	 el primer elemento de una doble cola vacía.

	 primero(PonDetras(elem, DColaVacia)) = elem
	 primero(PonDetras(elem, xs)) = primero(xs) si !esVacia(xs)
	 error: primero(DColaVacia)
	 */
	const T &primero() const {
		if (esVacia())
			throw EDColaVacia();
		return _fantasma->_sig->_elem;
	}


	/**
	 Elimina el primer elemento de la doble cola.
	 Operación modificadora parcial, que falla si 
	 está vacía.

	 quitaPrim(PonDetras(elem, DColaVacia)) = DColaVacia
	 quitaPrim(PonDetras(elem, xs)) = PonDetras(elem, quitaPrim(xs)) si !esVacia(xs)
	 error: quitaPrim(DColaVacia)
	*/
	void quitaPrim() {
		if (esVacia())
			throw EDColaVacia();

		borraElem(_fantasma->_sig);
		--_numElems;
	}

	/**
	 Añade un elemento a la parte delantera de una doble cola.
	 Operación modificadora.

	 ponDelante(elem, DColaVacia) = ponDetras(elem, DColaVacia)
	 ponDelante(elem, ponDetras(x, xs)) = 
		ponDetras(x, ponDelante(elem, xs))

	 @param e Elemento que se añade
	 */
	void ponDelante(const T &e) {
		insertaElem(e, _fantasma, _fantasma->_sig);
		++_numElems;
	}

	/**
	 Devuelve el último elemento de la doble cola. Es
	 un error preguntar por el último de una doble cola vacía.

	 ultimo(PonDetras(x, xs)) = x
	 error: ultimo(DColaVacia)

	 @return Último elemento de la cola.
	 */
	const T &ultimo() const {
		if (esVacia())
			throw EDColaVacia();
		return _fantasma->_ant->_elem;
	}

	/**
	 Elimina el último elemento de la doble cola. Es
	 un error quitar el último de una doble cola vacía.

	 quitaUlt(PonDetras(x, xs)) = xs
	 error: quitaUlt(DColaVacia)
	 */
	void quitaUlt() {
		if (esVacia())
			throw EDColaVacia();

		borraElem(_fantasma->_ant);
		--_numElems;
	}

	/**
	 Operación observadora para saber si una doble cola
	 tiene o no elementos.

	 esVacia(DColaVacia) = true
	 esVacia(ponDetras(x, xs)) = false

	 @return true si la doble cola no tiene elementos.
	 */
	bool esVacia() const {
		return _fantasma->_sig == _fantasma;
		/* return _numElems == 0; */
	}

	/**
	 Devuelve el número de elementos que hay en la
	 doble cola.
	 numElems(DColaVacia) = 0
	 numElems(PonDetras(elem, p)) = 1 + numElems(p)

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
	DCola(const DCola<T> &other) : _fantasma(NULL) {
		copia(other);
	}

	/** Operador de asignación */
	DCola<T> &operator=(const DCola<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparación. */
	bool operator==(const DCola<T> &rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		Nodo *p1 = _fantasma->_sig;
		Nodo *p2 = rhs._fantasma->_sig;
		while ((p1 != _fantasma) && (p2 != rhs._fantasma)) {
			if (p1->_elem != p2->_elem)
				return false;
			p1 = p1->_sig;
			p2 = p2->_sig;
		}

		return (p1 == _fantasma) && (p2 == rhs._fantasma);
	}

	bool operator!=(const DCola<T> &rhs) const {
		return !(*this == rhs);
	}

protected:

	void libera() {
		// Usamos libera(nodo), pero antes quitamos
		// la circularidad para evitar bucle
		// infinito...
		_fantasma->_ant->_sig = NULL;
		_fantasma->_ant = NULL;
		libera(_fantasma);
		_fantasma = NULL;
	}

	void copia(const DCola<T> &other) {
		// En vez de trabajar con punteros en la inserción,
		// usamos ponDetras.
		_fantasma = new Nodo();
		_fantasma->_sig = _fantasma;
		_fantasma->_ant = _fantasma;
		_numElems = 0;

		Nodo *act = other._fantasma->_sig;
		while (act != other._fantasma) {
			ponDetras(act->_elem);
			act = act->_sig;
		}
	}

private:

	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y dos punteros, uno al nodo anterior y otro al nodo siguiente.
	 Ambos punteros podrían ser NULL si el nodo es el primero
	 y/o último de la lista enlazada.
	 */
	class Nodo {
	public:
		Nodo() : _sig(NULL) {}
		Nodo(const T &elem) : _elem(elem), _sig(NULL), _ant(NULL) {}
		Nodo(Nodo *ant, const T &elem, Nodo *sig) : 
		    _elem(elem), _sig(sig), _ant(ant) {}

		T _elem;
		Nodo *_sig;
		Nodo *_ant;
	};

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
	 o después, actualiza sus punteros anterior y siguiente.
	 Caso general: hay nodos anterior y siguiente.
	 Casos especiales: algunos de los nodos (anterior o siguiente
	 a n) no existen.
	*/
	static void borraElem(Nodo *n) {
		if (n == NULL)
			return;

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
	 primer nodo se pasa como parámetro.
	 Se admite que el nodo sea NULL (no habrá nada que
	 liberar). En caso de pasarse un nodo válido,
	 su puntero al nodo anterior debe ser NULL (si no,
	 no sería el primero de la lista!).
	 */
	static void libera(Nodo *prim) {
		if (prim == NULL)
			return;

		assert(!prim || !prim->_ant);

		while (prim != NULL) {
			Nodo *aux = prim;
			prim = prim->_sig;
			delete aux;
		}
	}

	// Puntero al nodo fantasma
	Nodo *_fantasma;

	// Número de elementos
	unsigned int _numElems;
};

/**
  @file Lista.h

  Implementación del TAD lista, utilizando una 
  lista doblemente enlazada.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Marco Antonio Gómez Martín, 2012
*/

/**
 Implementación del TAD Lista utilizando una lista doblemente enlazada.

 Las operaciones son:

 - ListaVacia: -> Lista. Generadora implementada en el
   constructor sin parámetros.
 - Cons: Lista, Elem -> Lista. Generadora.
 - ponDr: Lista, Elem -> Lista. Modificadora.
 - primero: Lista - -> Elem. Observadora parcial
 - resto: Lista - -> Lista. Modificadora parcial
 - ultimo: Lista - -> Elem. Observadora parcial
 - inicio: Lista - -> Lista. Modificadora parcial
 - esVacia: Lista -> Bool. Observadora
 - numElems: Lista -> Elem. Obervadora.
 - elem: Lista, Entero - -> Elem. Observador parcial.

 @author Marco Antonio Gómez Martín
 */
template <class T>
class Lista {
private:
	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y dos punteros, uno al nodo anterior y otro al nodo siguiente.
	 Ambos punteros podrían ser NULL si el nodo es el primero
	 y/o último de la lista enlazada.
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

	/** Constructor; operación ListaVacia. */
	Lista() : _prim(NULL), _ult(NULL), _numElems(0) {}

	/** Destructor; elimina la lista doblemente enlazada. */
	~Lista() {
		libera();
	}

	/**
	 Añade un nuevo elemento en la cabeza de la lista.
	 Operación generadora.

	 @param elem Elemento que se añade en la cabecera de
	 la lista.
	*/
	void Cons(const T &elem) {
		_numElems++;
		_prim = insertaElem(elem, NULL, _prim);
		if (_ult == NULL)
			_ult = _prim;
	}

	/**
	 Añade un nuevo elemento al final de la lista (a la 
	 "derecha"). Operación modificadora.

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
	 una lista vacía.

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
	 Devuelve el valor almacenado en la última posición
	 de la lista (a la derecha).
	 Es un error preguntar por el primero de una lista vacía.

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
	 Es un error intentar obtener el resto de una lista vacía.

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
	 Elimina el último elemento de la lista.
	 Es un error intentar obtener el inicio de una lista vacía.

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
	 Operación observadora para saber si una lista
	 tiene o no elementos.

	 esVacia(ListaVacia) = true
	 esVacia(Cons(x, xs)) = false

	 @return true si la lista no tiene elementos.
	 */
	bool esVacia() const {
		return _prim == NULL;
	}

	/**
	 Devuelve el número de elementos que hay en la
	 lista.
	 numElems(ListaVacia) = 0
	 numElems(Cons(x, xs)) = 1 + numElems(xs)

	 @return Número de elementos.
	 */
	unsigned int numElems() const {
		return _numElems;
	}

	/**
	 Devuelve el elemento i-ésimo de la lista, teniendo
	 en cuenta que el primer elemento (primero())
	 es el elemento 0 y el último es numElems()-1,
	 es decir idx está en [0..numElems()-1].
	 Operación observadora parcial que puede fallar
	 si se da un índice incorrecto. El índice es
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
	 coincidirá con final() si la lista está vacía.
	 */
	Iterador principio() {
		return Iterador(_prim);
	}

	/**
	 @return Devuelve un iterador al final del recorrido
	 (fuera de éste).
	 */
	Iterador final() const {
		return Iterador(NULL);
	}

	/**
	 Permite eliminar de la lista el elemento
	 apuntado por el iterador que se pasa como parámetro.
	 El iterador recibido DEJA DE SER VÁLIDO. En su
	 lugar, deberá utilizarse el iterador devuelto, que
	 apuntará al siguiente elemento al borrado.
	 @param it Iterador colocado en el elemento que se
	 quiere borrar.
	 @return Nuevo iterador colocado en el elemento siguiente
	 al borrado (podría coincidir con final() si el
	 elemento que se borró era el último de la lista).
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
	 Método para insertar un elemento en la lista
	 en el punto marcado por el iterador. En concreto,
	 se añade _justo antes_ que el elemento actual. Es
	 decir, si it==l.primero(), el elemento insertado se
	 convierte en el primer elemento (y el iterador
	 apuntará al segundo). Si it==l.final(), el elemento
	 insertado será el último (e it seguirá apuntando
	 fuera del recorrido).
	 @param elem Valor del elemento a insertar.
	 @param it Punto en el que insertar el elemento.
	 */
	void insertar(const T &elem, const Iterador &it) {

		// Caso especial: ¿añadir al principio?
		if (_prim == it._act) {
			Cons(elem);
		} else
		// Caso especial: ¿añadir al final?
		if (it._act == NULL) {
			ponDr(elem);
		}
		// Caso normal
		else {
			insertaElem(elem, it._act->_ant, it._act);
		}
	}

	// //
	// MÉTODOS DE "FONTANERÍA" DE C++ QUE HACEN VERSÁTIL
	// A LA CLASE
	// //

	/** Constructor copia */
	Lista(const Lista<T> &other) : _prim(NULL), _ult(NULL) {
		copia(other);
	}

	/** Operador de asignación */
	Lista<T> &operator=(const Lista<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparación. */
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
		// En vez de trabajar con punteros en la inserción,
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
	 o después, actualiza sus punteros anterior y siguiente.
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
	 primer nodo se pasa como parámetro.
	 Se admite que el nodo sea NULL (no habrá nada que
	 liberar). En caso de pasarse un nodo válido,
	 su puntero al nodo anterior debe ser NULL (si no,
	 no sería el primero de la lista!).
	 */
	static void libera(Nodo *prim) {
		assert(!prim || !prim->_ant);

		while (prim != NULL) {
			Nodo *aux = prim;
			prim = prim->_sig;
			delete aux;
		}
	}

	// Puntero al primer y último elemento
	Nodo *_prim, *_ult;

	// Número de elementos (número de nodos entre _prim y _ult)
	unsigned int _numElems;
};

/**
  @file Pila.h

  Implementación del TAD Pila utilizando un
  array estático.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Antonio Sánchez Ruiz-Granados, 2013
*/

/**
 Implementación del TAD Pila utilizando un array estático.

 Las operaciones son:

 - PilaVacia: -> Pila. Generadora implementada en el
   constructor sin parámetros.
 - apila: Pila, Elem -> Pila. Generadora parcial.
 - desapila: Pila - -> Pila. Modificadora parcial.
 - cima: Pila - -> Elem. Observadora parcial.
 - esVacia: Pila -> Bool. Observadora.
 - numElems: Pila -> Entero. Observadora.

 @author Antonio Sánchez Ruiz-Granados
 */
template <class T>
class PilaE {
public:
	/** Número máximo de elementos. */
	static const unsigned int TAM_MAX = 100;

	/** Constructor; operación PilaVacia */
	PilaE() : _numElems(0) {	}

	/** Destructor. */
	~PilaE() { }

	/**
	 Apila un elemento. Operación generadora parcial.

	 @param elem Elemento a apilar.
	 error: apila(p) cuando numElems(p) == TAM_MAX
	*/
	void apila(const T &elem) {
		if (_numElems == TAM_MAX)
			throw EPilaLlena();
		
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
		_numElems--;
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
		return _v[_numElems-1];
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
	PilaE(const PilaE<T> &other) {
		copia(other);
	}

	/** Operador de asignación */
	PilaE<T> &operator=(const PilaE<T> &other) {
		if (this != &other) 
			copia(other);
		
		return *this;
	}

	/** Operador de comparación. */
	bool operator==(const PilaE<T> &rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		
		for (unsigned int i = 0; i < _numElems; ++i)
			if (_v[i] != rhs._v[i])
				return false;
		
		return true;
	}

	bool operator!=(const PilaE<T> &rhs) const {
		return !(*this == rhs);
	}

protected:

	void copia(const PilaE<T> &other) {
		_numElems = other._numElems;
		for (unsigned int i = 0; i < _numElems; ++i)
			_v[i] = other._v[i];
	}

private:

	/** Array de elementos. */
	T _v[TAM_MAX];

	/** Número de elementos almacenados en la pila. */
	unsigned int _numElems;
};

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

/**
  @file PilaLE.h

  Implementación del TAD Pila utilizando una
  lista enlazada de nodos.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Marco Antonio Gómez Martín, 2012
*/

/**
 Implementación del TAD Pila utilizando una lista enlazada de nodos.

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
class PilaLE {
public:

	/** Constructor; operación PilaVacia */
	PilaLE() : _cima(NULL), _numElems(0) {
	}

	/** Destructor; elimina la lista enlazada. */
	~PilaLE() {
		libera();
		_cima = NULL;
	}

	/**
	 Apila un elemento. Operación generadora.

	 @param elem Elemento a apilar.
	*/
	void apila(const T &elem) {
		_cima = new Nodo(elem, _cima);
		_numElems++;
	}
	
	/**
	 Desapila un elemento. Operación modificadora parcial,
	 que falla si la pila está vacía.

	 desapila(Apila(elem, p) = p
	 error: desapila(PilaVacia)
	*/
	void desapila() {
		if (esVacia())
			throw EPilaVacia();
		Nodo *aBorrar = _cima;
		_cima = _cima->_sig;
		delete aBorrar;
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
		return _cima->_elem;
	}

	/**
	 Devuelve true si la pila no tiene ningún elemento.

	 esVacia(PilaVacia) = true
	 esVacia(Apila(elem, p)) = false

	 @return true si la pila no tiene ningún elemento.
	 */
	bool esVacia() const {
		return _cima == NULL;
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
	PilaLE(const PilaLE<T> &other) : _cima(NULL) {
		copia(other);
	}

	/** Operador de asignación */
	PilaLE<T> &operator=(const PilaLE<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparación. */
	bool operator==(const PilaLE<T> &rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		Nodo *cima1 = _cima;
		Nodo *cima2 = rhs._cima;
		while ((cima1 != NULL) && (cima2 != NULL)) {
			if (cima1->_elem != cima2->_elem)
				return false;
			cima1 = cima1->_sig;
			cima2 = cima2->_sig;
		}

		return (cima1 == NULL) && (cima2 == NULL);
	}

	bool operator!=(const PilaLE<T> &rhs) const {
		return !(*this == rhs);
	}

protected:

	void libera() {
		libera(_cima);
	}

	void copia(const PilaLE &other) {

		if (other.esVacia()) {
			_cima = NULL;
			_numElems = 0;
		} else {
			Nodo *act = other._cima;
			Nodo *ant;
			_cima = new Nodo(act->_elem);
			ant = _cima;
			while (act->_sig != NULL) {
				act = act->_sig;
				ant->_sig = new Nodo(act->_elem);
				ant = ant->_sig;
			}
			_numElems = other._numElems;
		}
	}

private:

	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y un puntero al nodo siguiente, que podría ser NULL si
	 el nodo es el último de la lista enlazada.
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
	 primer nodo se pasa como parámetro.
	 Se admite que el nodo sea NULL (no habrá nada que
	 liberar).
	 */
	static void libera(Nodo *prim) {
		while (prim != NULL) {
			Nodo *aux = prim;
			prim = prim->_sig;
			delete aux;
		}
	}

	/** Puntero al primer elemento */
	Nodo *_cima;

	/** Número de elementos */
	int _numElems;
};

#endif // lineales.h
//PROTOTIPOS
Pila<string> inicializaPila();
void revisa(Lista<Pila<string>> list);
Lista<Pila<string>> insertaPila (Lista<Pila<string>> l, Pila<string> p, int pos);
Lista<Pila<string>> borraPila (Lista<Pila<string>> l, int pos);
void compacta (Lista<Pila<string>> l);
//IMPLEMENTACION

int main(){
	string m;
	Pila<string> pilaA;
	Pila<string> pilaB;
	Pila<string> mazo;
	const int MAX=100;
	Lista<Pila<string>> list;
	Lista <Pila<string>> ::Iterador it = list.principio();
	
	int n;
	string aux;
	int i=0;
	//cin>> n;
	mazo = inicializaPila();	
	if(!mazo.esVacia()){
		while(!mazo.esVacia()){
			Pila<string> pilaA;
			aux=mazo.cima();
			mazo.desapila();
			//1 caso base(hay 0 cartas sobre la mesa)
			if(list.esVacia()){
				pilaA.apila(aux);
				list.ponDr(pilaA);
			}
			//2 caso base hay 1 pila sobre la mesa
			else if(list.numElems()==1 || list.numElems()==2){
				pilaA=list.elem(i);
				//cout<<"list.elem(0)"<<list.elem(i).cima()[0] <<"y list.elem(1) "<<list.elem(i).cima()[1]<<endl;
				if((pilaA.cima()[0]==aux[0]) || (pilaA.cima()[1]==aux[1])){
					pilaA=list.elem(i);
					pilaA.apila(aux);
					list=borraPila(list, i);
					list=insertaPila(list, pilaA,i);
					cout << list.elem(i).cima();
					compacta(list);
					revisa(list);
				}
				else{
					i++;
					pilaA.apila(aux);
					list.ponDr(pilaA);					
				}
			}
			else{							
				 if((list.elem(i-2).cima()[0]==aux[0]) || (list.elem(i-2).cima()[1]==aux[1])) {
					pilaA=list.elem(i-2);
					pilaA.apila(aux);
					list=borraPila(list, i-2);
					list=insertaPila(list, pilaA,i-2);
					compacta(list);
					revisa(list);
				}
				else if((list.elem(i).cima()[0]==aux[0]) || (list.elem(i).cima()[1]==aux[1])) {
					pilaA=list.elem(i);
					pilaA.apila(aux);
					list=borraPila(list, i);
					list=insertaPila(list, pilaA,i);
					compacta(list);
					revisa(list);
				}
				else{
					i++;
					pilaA=list.elem(i);
					pilaA.apila(aux);
				}
			}
		}
		cout<<"la lista es:" << endl;
		/*for (int j=0; j<list.numElems();j++){
			cout<<"pos "<<i<<" " <<list.elem(j).cima()<<endl;
		}*/
		Lista<Pila<string>>::Iterador iter = list.principio();
		while(iter!=list.final()){
			cout << iter.elem().numElems() << endl;
			iter.avanza();
		}
	}

	return 0;
}


Pila<string> inicializaPila(){
	int cont = 52;
	Pila<string>  aux;
	string leido;
//	cout << "comienzo de mazo, longitud " << n << "\n";
	
	while(cont!=0){
		cin>>leido;
		aux.apila(leido);
		
		cont--;
	}
	/*for (int i=0; i<n; i++) {
		cin >> leido;
		aux.apila(leido);
	}*/
	//cout << aux.numElems();
	return aux;
}


Lista<Pila<string>> insertaPila (Lista<Pila<string>> l, Pila<string> p, int pos){
	Lista<Pila<string>>::Iterador it = l.principio();
	while(pos!=0){
		it.avanza();
	}
	l.insertar(p, it);
	return l;
}

Lista<Pila<string>> borraPila (Lista<Pila<string>> l, int pos){
	Lista<Pila<string>>::Iterador it = l.principio();
	while(pos!=0){
		it.avanza();
	}
	it=l.borra(it);
	return l;
}

void revisa(Lista<Pila<string>> list){
	string aux;
	unsigned int i=0;
	unsigned int ant=i-1;
	unsigned int ant3=i-3;
	Pila<string> pilaA, pilaB;
	while(i<list.numElems()){
		if(ant3>=0){
			if((list.elem(i).cima()[0]==list.elem(ant3).cima()[0]) || (list.elem(i).cima()[1]==list.elem(ant3).cima()[1])){
				pilaA=list.elem(ant3);
				pilaA.apila(list.elem(i).cima());
				pilaB=list.elem(i);
				pilaB.desapila();
				insertaPila(list, pilaA,ant3);
				borraPila(list, ant3+1);
				insertaPila(list, pilaB, i);
				borraPila(list, i+1);
				compacta(list);
				i=0;

			}
			else if(ant>=0){
				if((list.elem(i).cima()[0]==list.elem(ant).cima()[0]) || (list.elem(i).cima()[1]==list.elem(ant).cima()[1])){
					pilaA=list.elem(ant);
					pilaA.apila(list.elem(i).cima());
					pilaB=list.elem(i);
					pilaB.desapila();
					insertaPila(list, pilaA,ant);
					borraPila(list, ant+1);
					insertaPila(list, pilaB, i);
					borraPila(list, i+1);
					compacta(list);
					i=0;
				}
			}
			else{
				i++;
			}
		
		}else if(ant>=0){
			if((list.elem(i).cima()[0]==list.elem(ant).cima()[0]) || (list.elem(i).cima()[1]==list.elem(ant).cima()[1])){
				pilaA=list.elem(ant);
				pilaA.apila(list.elem(i).cima());
				pilaB=list.elem(i);
				pilaB.desapila();
				insertaPila(list, pilaA,ant);
				borraPila(list, ant+1);
				insertaPila(list, pilaB, i);
				borraPila(list, i+1);
				compacta(list);
				i=0;
			}

		}
		else{
			i++;
		}
		 ant=i-1;
		 ant3=i-3;
	}

}

void compacta (Lista<Pila<string>> l){
	Lista<Pila<string>>::Iterador it = l.principio();
	while(it!=l.final()){
		Pila<string> aux;
		aux = it.elem();
		if(aux.esVacia()){
			it = l.borra(it);
		}else{
			it.avanza();
		}
	}
}