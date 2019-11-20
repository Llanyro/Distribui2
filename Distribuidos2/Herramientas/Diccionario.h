#pragma once
#include "LineaDiccionario.h"

template <class T, class T1>
class Diccionario
{
	private:
		LineaDiccionario<T, T1>* raiz;
		size_t count;
		LineaDiccionario<T, T1>* ultimoNodoAccedido;
		size_t posicionUltimoNodoAccedido;
		// Complejidad espacial y temporal peor O(n/2)
		// Complejidad espacial y temporal mejor O(1)
		// Complejidad espacial y temporal imprimir O(1)
		// Complejidad espacial y temporal media O(n/4) (No comprobado->aprox)
		LineaDiccionario<T, T1>* getNodo(const size_t& posicion);
		// Complejidad espacial y temporal media O(n/2)
		LineaDiccionario<T, T1>* getNodoLow(const size_t& posicion) const;
	public:
		#pragma region Constructores
		Diccionario();
		Diccionario(const Diccionario<T, T1>& other);
		bool operator=(const Diccionario<T, T1>& other);
		~Diccionario();
		#pragma endregion
		#pragma region Compares
		Diccionario<size_t, void*> findListIgual(const T& item1);
		Diccionario<size_t, void*> findListIgual2(const T1& item2);
		Diccionario<size_t, void*> findListIgual(const T& item1, const T1& item2);
		bool estaEnLista(const T& item1) const;
		bool estaEnLista2(const T1& item2) const;
		bool estaEnLista(const T& item1, const T1& item2) const;
		bool igual(const Diccionario<T, T1>& other) const;
		bool operator==(const Diccionario<T, T1>& other) const;
		bool operator!=(const Diccionario<T, T1>& other) const;
		#pragma endregion
		#pragma region Funciones lista
		void add(const T& item1, const T1& item2);
		void insert(const T& item1, const T1& item2, const size_t& posicion);
		void remove(const size_t& posicion);
		void clear();
		size_t getCount() const;
		T& getItem1(const size_t& posicion);
		T1& getItem2(const size_t& posicion);
		void operator+=(const Diccionario<T, T1>& other);
		#pragma endregion
};
#pragma region Private
template <class T, class T1>
inline LineaDiccionario<T, T1>* Diccionario<T, T1>::getNodo(const size_t& posicion)
{
	assert(&posicion != nullptr);
	assert(posicion < this->count);
	LineaDiccionario<T, T1>* nodoActual = nullptr;
	if (this->ultimoNodoAccedido != nullptr)
	{
		size_t distanciaDesdeCero = posicion;
		size_t distanciaDesdeUltimoAccedido = posicion - this->posicionUltimoNodoAccedido;
		size_t distanciaDesdeCeroInverso = this->count - posicion;
		size_t distanciaDesdeUltimoAccedidoInverso = this->posicionUltimoNodoAccedido - posicion;

		if (distanciaDesdeCero >= 0
			&& distanciaDesdeCero <= distanciaDesdeCeroInverso
			&& distanciaDesdeCero <= distanciaDesdeUltimoAccedido
			&& distanciaDesdeCero <= distanciaDesdeUltimoAccedidoInverso)
		{
			nodoActual = this->raiz;
			for (size_t i = 0; i < posicion; i++)
				nodoActual = nodoActual->getSiguienteLinea();
		}
		else if (distanciaDesdeCeroInverso >= 0
			&& distanciaDesdeCeroInverso <= distanciaDesdeCero
			&& distanciaDesdeCeroInverso <= distanciaDesdeUltimoAccedido
			&& distanciaDesdeCeroInverso <= distanciaDesdeUltimoAccedidoInverso)
		{
			nodoActual = this->raiz;
			for (size_t i = 0; i < this->count - posicion; i++)
				nodoActual = nodoActual->getAnteriorLinea();
		}
		else if (distanciaDesdeUltimoAccedido >= 0
			&& distanciaDesdeUltimoAccedido <= distanciaDesdeCero
			&& distanciaDesdeUltimoAccedido <= distanciaDesdeCeroInverso
			&& distanciaDesdeUltimoAccedido <= distanciaDesdeUltimoAccedidoInverso)
		{
			nodoActual = this->ultimoNodoAccedido;
			for (size_t i = this->posicionUltimoNodoAccedido; i < posicion; i++)
				nodoActual = nodoActual->getSiguienteLinea();
		}
		else if (distanciaDesdeUltimoAccedidoInverso >= 0
			&& distanciaDesdeUltimoAccedidoInverso <= distanciaDesdeCero
			&& distanciaDesdeUltimoAccedidoInverso <= distanciaDesdeCeroInverso
			&& distanciaDesdeUltimoAccedidoInverso <= distanciaDesdeUltimoAccedido)
		{
			nodoActual = this->ultimoNodoAccedido;
			for (size_t i = this->posicionUltimoNodoAccedido; i < this->posicionUltimoNodoAccedido - posicion; i++)
				nodoActual = nodoActual->getAnteriorLinea();
		}
		else
		{
			/// NINGUN CASO??? -> REVISA
			assert(false);
		}
	}
	else
	{
		nodoActual = this->raiz;
		if (posicion < this->count / 2)
		{
			for (size_t i = 0; i < posicion; i++)
				nodoActual = nodoActual->getSiguienteLinea();
		}
		else
		{
			for (size_t i = 0; i < this->count - posicion; i++)
				nodoActual = nodoActual->getAnteriorLinea();
		}
	}
	this->ultimoNodoAccedido = nodoActual;
	this->posicionUltimoNodoAccedido = posicion;
	return nodoActual;
}
template <class T, class T1>
inline LineaDiccionario<T, T1>* Diccionario<T, T1>::getNodoLow(const size_t& posicion) const
{
	assert(&posicion != nullptr);
	assert(posicion < this->count);
	LineaDiccionario<T, T1>* nodoActual = this->raiz;
	if (posicion < this->count / 2)
	{
		for (size_t i = 0; i < posicion; i++)
			nodoActual = nodoActual->getSiguienteLinea();
	}
	else
	{
		for (size_t i = 0; i < this->count - posicion; i++)
			nodoActual = nodoActual->getAnteriorLinea();
	}
	return nodoActual;
}
#pragma endregion
#pragma region Constructores
template <class T, class T1>
inline Diccionario<T, T1>::Diccionario()
{
	this->count = 0;
	this->raiz = nullptr;
	this->posicionUltimoNodoAccedido = 0;
	this->ultimoNodoAccedido = nullptr;
}
template <class T, class T1>
inline Diccionario<T, T1>::Diccionario(const Diccionario<T, T1>& other) : Diccionario()
{
	assert(&other != nullptr);
	bool temp = Diccionario::operator=(other);
	assert(temp);
}
template <class T, class T1>
inline bool Diccionario<T, T1>::operator=(const Diccionario<T, T1>& other)
{
	bool temp = true;
	if (&other == nullptr) temp = false;
	else
	{
		Diccionario::clear();
		LineaDiccionario<T, T1>* nodoActual = other.raiz;
		for (size_t i = 0; i < other.count; i++)
		{
			Diccionario::add(nodoActual->getItem1(), nodoActual->getItem2());
			nodoActual = nodoActual->getSiguienteLinea();
		}
	}
	return temp;
}
template <class T, class T1>
inline Diccionario<T, T1>::~Diccionario()
{
	Diccionario::clear();
}
#pragma endregion
#pragma region Compares
template <class T, class T1>
inline Diccionario<size_t, void*> Diccionario<T, T1>::findListIgual(const T& item1)
{
	assert(&item1 != nullptr);
	Diccionario<size_t, void*> coincidencias;
	for (size_t i = 0; i < this->count; i++)
		if (Diccionario::getItem1(i) == item1)
			coincidencias.add(i, nullptr);
	return coincidencias;
}
template<class T, class T1>
inline Diccionario<size_t, void*> Diccionario<T, T1>::findListIgual2(const T1& item2)
{
	assert(&item2 != nullptr);
	Diccionario<size_t, void*> coincidencias;
	for (size_t i = 0; i < this->count; i++)
		if (Diccionario::getItem2(i) == item2)
			coincidencias.add(i, nullptr);
	return coincidencias;
}
template<class T, class T1>
inline Diccionario<size_t, void*> Diccionario<T, T1>::findListIgual(const T& item1, const T1& item2)
{
	assert(&item1 != nullptr);
	Diccionario<size_t, void*> coincidencias;
	for (size_t i = 0; i < this->count; i++)
	{
		LineaDiccionario<T, T1>* nodo = Diccionario::getNodo(i);
		if (nodo->getItem1() == item1)
			if (nodo->getItem2() == item2)
				coincidencias.add(i, nullptr);
	}
	return coincidencias;
}
template <class T, class T1>
inline bool Diccionario<T, T1>::estaEnLista(const T& item1) const
{
	assert(&item1 != nullptr);
	bool temp = false;
	for (size_t i = 0; i < this->count && !temp; i++)
		if (Diccionario::getNodoLow(i)->getItem1() == item1)
			temp = true;
	return temp;
}
template<class T, class T1>
inline bool Diccionario<T, T1>::estaEnLista2(const T1& item2) const
{
	assert(&item2 != nullptr);
	bool temp = false;
	for (size_t i = 0; i < this->count && !temp; i++)
		if (Diccionario::getNodoLow(i)->getItem2() == item2)
			temp = true;
	return temp;
}
template<class T, class T1>
inline bool Diccionario<T, T1>::estaEnLista(const T& item1, const T1& item2) const
{
	assert(&item1 != nullptr);
	bool temp = false;
	for (size_t i = 0; i < this->count && !temp; i++)
	{
		LineaDiccionario<T, T1>* nodo = Diccionario::getNodoLow(i);
		if (nodo->getItem1() == item1)
			if (nodo->getItem2() == item2)
				temp = true;
	}
	return temp;
}
template <class T, class T1>
inline bool Diccionario<T, T1>::igual(const Diccionario<T, T1>& other) const
{
	assert(&other != nullptr);
	bool temp = true;
	if (&other == nullptr && this == nullptr) temp = true;
	else if (&other != nullptr && this != nullptr)
		if (other.count == this->count)
			for (size_t i = 0; i < this->count && temp; i++)
			{
				LineaDiccionario<T, T1>* nodo = Diccionario::getNodoLow(i);
				temp = Diccionario::estaEnLista(nodo->getItem1(), nodo->getItem2());
			}
		else temp = false;
	return temp;
}
template <class T, class T1>
inline bool Diccionario<T, T1>::operator==(const Diccionario<T, T1>& other) const
{
	assert(&other != nullptr);
	return Diccionario::igual(other);
}
template <class T, class T1>
inline bool Diccionario<T, T1>::operator!=(const Diccionario<T, T1>& other) const
{
	assert(&other != nullptr);
	return !Diccionario::igual(other);
}
#pragma endregion
#pragma region Funciones lista
template <class T, class T1>
inline void Diccionario<T, T1>::add(const T& item1, const T1& item2)
{
	assert(&item1 != nullptr);
	assert(&item2 != nullptr);
	// Creamos el nodo
	LineaDiccionario<T, T1>* nuevoNodo = new LineaDiccionario<T, T1>(item1, item2);
	// Caso especial de que la lista este vacia
	if (this->count == 0)
	{
		this->raiz = nuevoNodo;
		nuevoNodo->setSiguienteLinea(nuevoNodo);
		nuevoNodo->setAnteriorLinea(nuevoNodo);
	}
	// Añadirmos al final
	else
	{
		// Guardamos los nodos que vamos a modificar
		LineaDiccionario<T, T1>* anteriorNodo = Diccionario::getNodo(this->count - 1);
		LineaDiccionario<T, T1>* siguienteNodo = anteriorNodo->getSiguienteLinea();

		// Apuntamos correctamente el nodo entre los otros nodos
		nuevoNodo->setSiguienteLinea(siguienteNodo);
		nuevoNodo->setAnteriorLinea(anteriorNodo);
		// Hacemos que los otros nodos apunten al nuevo
		anteriorNodo->setSiguienteLinea(nuevoNodo);
		siguienteNodo->setAnteriorLinea(nuevoNodo);
	}
	// Incrementamos el tamaño
	this->count++;
}
template <class T, class T1>
inline void Diccionario<T, T1>::insert(const T& item1, const T1& item2, const size_t& posicion)
{
	assert(&item1 != nullptr);
	assert(&item2 != nullptr);
	assert(&posicion != nullptr);
	assert(posicion < this->count);
	// Creamos el nodo
	LineaDiccionario<T, T1>* nuevoNodo = new LineaDiccionario<T, T1>(item1, item2);
	// Guardamos los nodos que vamos a modificar
	LineaDiccionario<T, T1>* anteriorNodo = nullptr;
	LineaDiccionario<T, T1>* siguienteNodo = nullptr;
	if (posicion == 0) anteriorNodo = Diccionario::getNodo(this->count - 1);
	else anteriorNodo = Diccionario::getNodo(posicion - 1);
	siguienteNodo = anteriorNodo->getSiguienteLinea();
	// Apuntamos correctamente el nodo entre los otros nodos
	nuevoNodo->setSiguienteLinea(siguienteNodo);
	nuevoNodo->setAnteriorLinea(anteriorNodo);
	// Hacemos que los otros nodos apunten al nuevo
	anteriorNodo->setSiguienteLinea(nuevoNodo);
	siguienteNodo->setAnteriorLinea(nuevoNodo);
	// Incrementamos el tamaño
	this->count++;
}
template <class T, class T1>
inline void Diccionario<T, T1>::remove(const size_t& posicion)
{
	assert(&posicion != nullptr);
	assert(posicion < this->count);
	// Nodos a modificar
	LineaDiccionario<T, T1>* nodoAEliminar = Diccionario::getNodo(posicion);
	LineaDiccionario<T, T1>* nodoSiguiente = nodoAEliminar->getSiguienteLinea();
	LineaDiccionario<T, T1>* nodoAnterior = nodoAEliminar->getAnteriorLinea();
	// Modificamos los nodos
	nodoSiguiente->setAnteriorLinea(nodoAnterior);
	nodoAnterior->setSiguienteLinea(nodoSiguiente);
	// Si es un caso especial
	if (posicion == 0) this->raiz = nodoSiguiente;

	// Recolocamos el punto intermedio
	this->ultimoNodoAccedido = nullptr;
	this->posicionUltimoNodoAccedido = 0;

	// Incrementamos el tamaño
	delete(nodoAEliminar);
	this->count--;
}
template <class T, class T1>
inline void Diccionario<T, T1>::clear()
{
	while (this->count > 0) Diccionario::remove(0);
	this->count = 0;
	this->raiz = nullptr;
	this->posicionUltimoNodoAccedido = 0;
	this->ultimoNodoAccedido = nullptr;
}
template <class T, class T1>
inline size_t Diccionario<T, T1>::getCount() const
{
	return this->count;
}
template<class T, class T1>
inline T& Diccionario<T, T1>::getItem1(const size_t& posicion)
{
	assert(&posicion != nullptr);
	assert(posicion < this->count);
	return Diccionario::getNodo(posicion)->getItem1();
}
template<class T, class T1>
inline T1& Diccionario<T, T1>::getItem2(const size_t& posicion)
{
	assert(&posicion != nullptr);
	assert(posicion < this->count);
	return Diccionario::getNodo(posicion)->getItem2();
}
template<class T, class T1>
inline void Diccionario<T, T1>::operator+=(const Diccionario<T, T1>& other)
{
	assert(&other != nullptr);
	LineaDiccionario<T, T1>* lineaActual = other.raiz;
	for (size_t i = 0; i < other.count; i++)
	{
		Diccionario::add(lineaActual->getItem1(), lineaActual->getItem2());
		lineaActual = lineaActual->getSiguienteLinea();
	}
}
#pragma endregion
