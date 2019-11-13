#pragma once
#pragma warning(disable:26495)
#include <cassert>

#ifdef __unix__
#include <cstddef>
#elif _WIN32

#endif // __linux__

template<class T>
struct NodoDoble
{
	T item;
	NodoDoble* primerNodo;
	NodoDoble* segundoNodo;
};
/*
	Lista template V2
	Guarda items segun la posicion que indicas (si la indicas, sino al final)
	Al solicitar un item de la lista devuelve el item acortando distancia y escogiendo el punto de pivote desde el nodo 0 o el ultimo nodo accedido

*/
template<class T>
class List
{
	private:
		NodoDoble<T>* primerNodo;
		size_t count;
		NodoDoble<T>* ultimoNodoAccedido;
		size_t posicionUltimoNodoAccedido;
		// Complejidad espacial y temporal peor O(n/2)
		// Complejidad espacial y temporal mejor O(1)
		// Complejidad espacial y temporal imprimir O(1)
		// Complejidad espacial y temporal media O(n/4) (No comprobado->aprox)
		NodoDoble<T>* getNodo(const size_t& posicion);
		NodoDoble<T>* getNodoLow(const size_t& posicion) const;
	public:
		#pragma region Constructores
		List();
		List(const List<T>& other);
		bool operator=(const List<T>& other);
		~List();
		#pragma endregion
		#pragma region Compares
		List<size_t> findListIgual(T& item) const;
		List<size_t> findListIgual(const T& item) const;
		bool estaEnLista(const T& item) const;
		bool igual(const List<T>& other) const;
		bool operator==(const List& other) const;
		bool operator!=(const List& other) const;
		#pragma endregion
		#pragma region Funciones lista
		void add(const T& item);
		void add(const List<T>& list);
		void add(List<T>& list);
		void insert(const T& item, const size_t& posicion);
		void remove(const size_t& posicion);
		void clear();
		size_t getCount() const;
		T& operator[](const size_t& posicion);
		void operator+=(const T& item);
		void operator+=(const List<T>& list);
		void operator+=(List<T>& list);
		#pragma endregion
};
#pragma region Private
template<class T>
inline NodoDoble<T>* List<T>::getNodo(const size_t& posicion)
{
	assert(&posicion != nullptr);
	assert(posicion < this->count);
	NodoDoble<T>* nodoActual = nullptr;
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
			nodoActual = this->primerNodo;
			for (size_t i = 0; i < posicion; i++)
				nodoActual = nodoActual->primerNodo;
		}
		else if (distanciaDesdeCeroInverso >= 0
			&& distanciaDesdeCeroInverso <= distanciaDesdeCero
			&& distanciaDesdeCeroInverso <= distanciaDesdeUltimoAccedido
			&& distanciaDesdeCeroInverso <= distanciaDesdeUltimoAccedidoInverso)
		{
			nodoActual = this->primerNodo;
			for (size_t i = 0; i < this->count - posicion; i++)
				nodoActual = nodoActual->segundoNodo;
		}
		else if (distanciaDesdeUltimoAccedido >= 0
			&& distanciaDesdeUltimoAccedido <= distanciaDesdeCero
			&& distanciaDesdeUltimoAccedido <= distanciaDesdeCeroInverso
			&& distanciaDesdeUltimoAccedido <= distanciaDesdeUltimoAccedidoInverso)
		{
			nodoActual = this->ultimoNodoAccedido;
			for (size_t i = this->posicionUltimoNodoAccedido; i < posicion; i++)
				nodoActual = nodoActual->primerNodo;
		}
		else if (distanciaDesdeUltimoAccedidoInverso >= 0
			&& distanciaDesdeUltimoAccedidoInverso <= distanciaDesdeCero
			&& distanciaDesdeUltimoAccedidoInverso <= distanciaDesdeCeroInverso
			&& distanciaDesdeUltimoAccedidoInverso <= distanciaDesdeUltimoAccedido)
		{
			nodoActual = this->ultimoNodoAccedido;
			for (size_t i = this->posicionUltimoNodoAccedido; i < this->posicionUltimoNodoAccedido - posicion; i++)
				nodoActual = nodoActual->segundoNodo;
		}
		else
		{
			/// NINGUN CASO??? -> REVISA
			assert(false);
		}
	}
	else
	{
		nodoActual = this->primerNodo;
		if (posicion < this->count / 2)
		{
			for (size_t i = 0; i < posicion; i++)
				nodoActual = nodoActual->primerNodo;
		}
		else
		{
			for (size_t i = 0; i < this->count - posicion; i++)
				nodoActual = nodoActual->segundoNodo;
		}
	}
	this->ultimoNodoAccedido = nodoActual;
	this->posicionUltimoNodoAccedido = posicion;
	return nodoActual;
}
template<class T>
inline NodoDoble<T>* List<T>::getNodoLow(const size_t& posicion) const
{
	assert(&posicion != nullptr);
	assert(posicion < this->count);
	NodoDoble<T>* nodoActual = this->primerNodo;
	if (posicion < this->count / 2)
	{
		for (size_t i = 0; i < posicion; i++)
			nodoActual = nodoActual->primerNodo;
	}
	else
	{
		for (size_t i = 0; i < this->count - posicion; i++)
			nodoActual = nodoActual->segundoNodo;
	}
	return nodoActual;
}
#pragma endregion
#pragma region Constructores
template<class T>
inline List<T>::List()
{
	this->count = 0;
	this->primerNodo = nullptr;
	this->posicionUltimoNodoAccedido = 0;
	this->ultimoNodoAccedido = nullptr;
}
template<class T>
inline List<T>::List(const List<T>& other) : List()
{
	assert(&other != nullptr);
	bool temp = List::operator=(other);
	assert(temp);
}
template<class T>
inline bool List<T>::operator=(const List<T>& other)
{
	bool temp = true;
	if (&other == nullptr) temp = false;
	else
	{
		List::clear();
		NodoDoble<T>* nodoActual = other.primerNodo;
		for (size_t i = 0; i < other.count; i++)
		{
			List::add(nodoActual->item);
			nodoActual = nodoActual->primerNodo;
		}
	}
	return temp;
}
template<class T>
inline List<T>::~List()
{
	List::clear();
}
#pragma endregion
#pragma region Compares
template<class T>
inline List<size_t> List<T>::findListIgual(T& item) const
{
	assert(&item != nullptr);
	List<size_t> coincidencias;
	for (size_t i = 0; i < this->count; i++)
		if (List::operator[](i) == item)
			coincidencias.add(i);
	return coincidencias;
}
template<class T>
inline List<size_t> List<T>::findListIgual(const T& item) const
{
	assert(&item != nullptr);
	List<size_t> coincidencias;
	NodoDoble<T>* nodoActual = this->primerNodo;
	for (size_t i = 0; i < this->count; i++)
	{
		if (nodoActual->item == item)
			coincidencias.add(i);
		nodoActual = nodoActual->primerNodo;
	}
	return coincidencias;
}
template<class T>
inline bool List<T>::estaEnLista(const T& item) const
{
	assert(&item != nullptr);
	bool temp = false;
	for (size_t i = 0; i < this->count && !temp; i++)
		if (List::getNodoLow(i)->item == item)
			temp = true;
	return temp;
}
template<class T>
inline bool List<T>::igual(const List<T>& other) const
{
	assert(&other != nullptr);
	bool temp = true;
	if (&other == nullptr && this == nullptr) temp = true;
	else if (&other != nullptr && this != nullptr)
		if (other.count == this->count)
			for (size_t i = 0; i < this->count && temp; i++)
				temp = List::estaEnLista(other.getNodoLow(i)->item);
		else temp = false;
	return temp;
}
template<class T>
inline bool List<T>::operator==(const List<T>& other) const
{
	assert(&other != nullptr);
	return List::igual(other);
}
template<class T>
inline bool List<T>::operator!=(const List<T>& other) const
{
	assert(&other != nullptr);
	return !List::igual(other);
}
#pragma endregion
#pragma region Funciones lista
template<class T>
inline void List<T>::add(const T& item)
{
	assert(&item != nullptr);
	// Creamos el nodo
	NodoDoble<T>* nuevoNodo = new NodoDoble<T>();
	nuevoNodo->item = item;
	// Caso especial de que la lista este vacia
	if (this->count == 0)
	{
		this->primerNodo = nuevoNodo;
		nuevoNodo->primerNodo = nuevoNodo;
		nuevoNodo->segundoNodo = nuevoNodo;
	}
	// Añadirmos al final
	else
	{
		// Guardamos los nodos que vamos a modificar
		NodoDoble<T>* anteriorNodo = List::getNodo(this->count - 1);
		NodoDoble<T>* siguienteNodo = anteriorNodo->primerNodo;

		// Apuntamos correctamente el nodo entre los otros nodos
		nuevoNodo->primerNodo = siguienteNodo;
		nuevoNodo->segundoNodo = anteriorNodo;
		// Hacemos que los otros nodos apunten al nuevo
		anteriorNodo->primerNodo = nuevoNodo;
		siguienteNodo->segundoNodo = nuevoNodo;
	}
	// Incrementamos el tamaño
	this->count++;
}
template<class T>
inline void List<T>::add(const List<T>& list)
{
	assert(&list != nullptr);
	for (size_t i = 0; i < list.count; i++)
		List::add(list.getNodoLow(i)->item);
}
template<class T>
inline void List<T>::add(List<T>& list)
{
	assert(&list != nullptr);
	for (size_t i = 0; i < list.count; i++)
		List::add(list[i]);
}
template<class T>
inline void List<T>::insert(const T& item, const size_t& posicion)
{
	assert(&item != nullptr);
	assert(&posicion != nullptr);
	assert(posicion < this->count);
	// Creamos el nodo
	NodoDoble<T>* nuevoNodo = new NodoDoble<T>();
	nuevoNodo->item = item;
	// Guardamos los nodos que vamos a modificar
	NodoDoble<T>* anteriorNodo = nullptr;
	NodoDoble<T>* siguienteNodo = nullptr;
	if (posicion == 0) anteriorNodo = List::getNodo(this->count - 1);
	else anteriorNodo = List::getNodo(posicion - 1);
	siguienteNodo = anteriorNodo->primerNodo;
	// Apuntamos correctamente el nodo entre los otros nodos
	nuevoNodo->primerNodo = siguienteNodo;
	nuevoNodo->segundoNodo = anteriorNodo;
	// Hacemos que los otros nodos apunten al nuevo
	anteriorNodo->primerNodo = nuevoNodo;
	siguienteNodo->segundoNodo = nuevoNodo;
	// Incrementamos el tamaño
	this->count++;
}
template<class T>
inline void List<T>::remove(const size_t& posicion)
{
	assert(&posicion != nullptr);
	assert(posicion < this->count);
	// Nodos a modificar
	NodoDoble<T>* nodoAEliminar = List::getNodo(posicion);
	NodoDoble<T>* nodoSiguiente = nodoAEliminar->primerNodo;
	NodoDoble<T>* nodoAnterior = nodoAEliminar->segundoNodo;
	// Modificamos los nodos
	nodoSiguiente->segundoNodo = nodoAnterior;
	nodoAnterior->primerNodo = nodoSiguiente;
	// Si es un caso especial
	if (posicion == 0) this->primerNodo = nodoSiguiente;

	// Recolocamos el punto intermedio
	this->ultimoNodoAccedido = nullptr;
	this->posicionUltimoNodoAccedido = 0;

	// Incrementamos el tamaño
	delete(nodoAEliminar);
	this->count--;
}
template<class T>
inline void List<T>::clear()
{
	while (this->count > 0) List::remove(0);
	this->count = 0;
	this->primerNodo = nullptr;
	this->posicionUltimoNodoAccedido = 0;
	this->ultimoNodoAccedido = nullptr;
}
template<class T>
inline size_t List<T>::getCount() const
{
	return this->count;
}
template<class T>
inline T& List<T>::operator[](const size_t& posicion)
{
	assert(&posicion != nullptr);
	assert(posicion < this->count);
	return List::getNodo(posicion)->item;
}
template<class T>
inline void List<T>::operator+=(const T& item)
{
	assert(&item != nullptr);
	List::add(item);
}
template<class T>
inline void List<T>::operator+=(const List<T>& list)
{
	assert(&list != nullptr);
	List::add(list);
}
template<class T>
inline void List<T>::operator+=(List<T>& list)
{
	assert(&list != nullptr);
	List::add(list);
}
#pragma endregion
