#pragma once
#include <cassert>

template <class T, class T1>
class LineaDiccionario
{
	private:
		T item1;
		T1 item2;
		LineaDiccionario<T, T1>* siguienteLinea;
		LineaDiccionario<T, T1>* anteriorLinea;
	public:
		LineaDiccionario();
		LineaDiccionario(const T& item1, const T1& item2);
		LineaDiccionario(const LineaDiccionario& other);
		bool operator=(const LineaDiccionario& other);
		~LineaDiccionario();
		T& getItem1();
		T1& getItem2();
		LineaDiccionario<T, T1>* getSiguienteLinea() const;
		LineaDiccionario<T, T1>* getAnteriorLinea() const;
		void setItem1(const T& item1);
		void setItem2(const T1& item2);
		void setSiguienteLinea(const LineaDiccionario<T, T1>* siguienteLinea);
		void setAnteriorLinea(const LineaDiccionario<T, T1>* anteriorLinea);
		bool igual(const LineaDiccionario<T, T1>& other) const;
		bool operator==(const LineaDiccionario<T, T1>& other) const;
		bool operator!=(const LineaDiccionario<T, T1>& other) const;
};
#pragma region Constructores
template<class T, class T1>
inline LineaDiccionario<T, T1>::LineaDiccionario()
{
	this->item1 = T();
	this->item2 = T1();
	this->siguienteLinea = nullptr;
	this->anteriorLinea = nullptr;
}
template<class T, class T1>
inline LineaDiccionario<T, T1>::LineaDiccionario(const T& item1, const T1& item2) : LineaDiccionario()
{
	assert(&item1 != nullptr);
	assert(&item2 != nullptr);
	this->item1 = item1;
	this->item2 = item2;
}
template<class T, class T1>
inline LineaDiccionario<T, T1>::LineaDiccionario(const LineaDiccionario& other) : LineaDiccionario()
{
	assert(&other != nullptr);
	bool temp = LineaDiccionario::operator=(other);
	assert(temp);
}
template<class T, class T1>
inline bool LineaDiccionario<T, T1>::operator=(const LineaDiccionario& other)
{
	bool temp = true;
	if (&other == nullptr) temp = false;
	else
	{
		this->item1 = other.item1;
		this->item2 = other.item2;
		this->siguienteLinea = other.siguienteLinea;
		this->anteriorLinea = other.anteriorLinea;
	}
	return temp;
}
template<class T, class T1>
inline LineaDiccionario<T, T1>::~LineaDiccionario()
{
	this->siguienteLinea = nullptr;
	this->anteriorLinea = nullptr;
}
#pragma endregion
#pragma region Getters
template<class T, class T1>
inline T& LineaDiccionario<T, T1>::getItem1()
{
	return this->item1;
}
template<class T, class T1>
inline T1& LineaDiccionario<T, T1>::getItem2()
{
	return this->item2;
}
template<class T, class T1>
inline LineaDiccionario<T, T1>* LineaDiccionario<T, T1>::getSiguienteLinea() const
{
	return this->siguienteLinea;
}
template<class T, class T1>
inline LineaDiccionario<T, T1>* LineaDiccionario<T, T1>::getAnteriorLinea() const
{
	return this->anteriorLinea;
}
#pragma endregion
#pragma region Setters
template<class T, class T1>
inline void LineaDiccionario<T, T1>::setItem1(const T& item1)
{
	assert(&item1 != nullptr);
	this->item1 = item1;
}
template<class T, class T1>
inline void LineaDiccionario<T, T1>::setItem2(const T1& item2)
{
	assert(&item1 != nullptr);
	this->item1 = item1;
}
template<class T, class T1>
inline void LineaDiccionario<T, T1>::setSiguienteLinea(const LineaDiccionario<T, T1>* siguienteLinea)
{
	this->siguienteLinea = (LineaDiccionario<T, T1>*)siguienteLinea;
}
template<class T, class T1>
inline void LineaDiccionario<T, T1>::setAnteriorLinea(const LineaDiccionario<T, T1>* anteriorLinea)
{
	this->anteriorLinea = (LineaDiccionario<T, T1>*)anteriorLinea;
}
#pragma endregion
#pragma region Comparaciones
template<class T, class T1>
inline bool LineaDiccionario<T, T1>::igual(const LineaDiccionario<T, T1>& other) const
{
	bool temp = false;
	if (&other == nullptr && this == nullptr) temp = true;
	else if (&other != nullptr && this != nullptr)
		if (this->item1 == other.item1)
			if (this->item2 == other.item2)
				temp = true;
	return temp;
}
template<class T, class T1>
inline bool LineaDiccionario<T, T1>::operator==(const LineaDiccionario<T, T1>& other) const
{
	return LineaDiccionario::igual(other);
}
template<class T, class T1>
inline bool LineaDiccionario<T, T1>::operator!=(const LineaDiccionario<T, T1>& other) const
{
	return !LineaDiccionario::igual(other);
}
#pragma endregion
