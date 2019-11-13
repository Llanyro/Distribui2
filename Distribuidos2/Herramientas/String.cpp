#pragma warning(disable:4996)
#include "String.h"
#include "List.h"
#include <cstring>
#include <string>

#define SIZE_BUFFER 128

#pragma region Protected
bool String::caracteresSimilares(const char& value1, const char& value2) const
{
	bool temp = false;

	if (&value1 == nullptr && &value2 == nullptr) temp = true;
	else if (&value1 != nullptr && &value2 != nullptr)
		if (value1 == value2) temp = true;
		else
		{
			if (64 < value1 && value1 < 91)
			{
				if (64 < value2 && value2 < 91)
				{
					if (value1 == value2)
						temp = true;
				}
				else if (96 < value2 && value2 < 123)
				{
					if (value1 + 32 == value2)
						temp = true;
				}
			}
			else if (96 < value1 && value1 < 123)
			{
				if (64 < value2 && value2 < 91)
				{
					if (value1 -32 == value2)
						temp = true;
				}
				else if (96 < value2 && value2 < 123)
				{
					if (value1 == value2)
						temp = true;
				}
			}
		}
	return temp;
}
void String::iniciarString()
{
	this->vector = new char('\0');
	this->count = 1;
}
int String::IsMayus(const char& value)
{
	int result = 0;
	if (value > 64 && value < 91) result = 1;
	else if (value > 96 && value < 123) result = -1;
	return result;
}
bool String::CambiarMayus(char& value)
{
	assert(&value != nullptr);
	bool temp = true;
	if (String::IsMayus(value) == -1) value -= 32;
	else temp = false;
	return temp;
}
bool String::CambiarMinus(char& value)
{
	assert(&value != nullptr);

	bool temp = true;
	if (String::IsMayus(value) == 1) (value) += 32;
	else temp = false;
	return temp;
}
void String::semiClear()
{
	if (this->vector != nullptr)
		delete(this->vector);
	this->count = 0;
}
#pragma endregion
#pragma region Constructores
#pragma region 1
String::String()
{
	String::iniciarString();
}
String::String(const char& character)
{
	assert(&character != nullptr);
	String::iniciarString();
	bool temp = String::operator=(character);
	assert(temp);
}
String::String(const char other[])
{
	assert(&other != nullptr);
	String::iniciarString();
	bool temp = String::operator=(other);
	assert(temp);
}
String::String(const String& other)
{
	assert(&other != nullptr);
	String::iniciarString();
	bool temp = String::operator=(other);
	assert(temp);
}
String::String(List<char>& list)
{
	assert(&list != nullptr);
	String::iniciarString();
	bool temp = String::operator=(list);
	assert(temp);
}
String::String(List<String>& list)
{
	assert(&list != nullptr);
	String::iniciarString();
	bool temp = String::operator=(list);
	assert(temp);
}
String::String(List<String>& list, const char& separador)
{
	assert(&list != nullptr);
	String::iniciarString();
	assert(&list != nullptr);
	String::clear();
	for (size_t i = 0; i < list.getCount(); i++)
	{
		String::operator+=(list[i]);
		String::operator+=(separador);
	}
}
String::String(const char* other, const size_t& size) : String()
{
	assert(other != nullptr);
	assert(&size != nullptr);
	assert(size >= 0);
	this->vector = new char[size + 1];
	this->count = size;
	for (size_t i = 0; i < size; i++)
		this->vector[i] = other[i];
	this->vector[size] = '\0';
}
String::~String()
{
	String::clear();
}
#pragma endregion
#pragma region Operators
bool String::operator=(const char& character)
{
	assert(&character != nullptr);
	String::semiClear();
	this->count = 2;
	this->vector = new char[this->count];
	this->vector[0] = character;
	this->vector[1] = '\0';
	return true;
}
bool String::operator=(const char other[])
{
	assert(&other != nullptr);
	String::semiClear();
	this->count = strlen(other) + 1;
	this->vector = new char[this->count];
	strcpy(this->vector, other);
	return true;
}
bool String::operator=(const String& other)
{
	assert(&other != nullptr);
	String::semiClear();
	this->count = other.count;
	if (this->count == 0)
		this->vector = nullptr;
	else
	{
		this->vector = new char[this->count];
		strcpy(this->vector, other.vector);
	}
	return true;
}
bool String::operator=(List<char>& list)
{
	assert(&list != nullptr);
	String::semiClear();
	this->count = list.getCount() + 1;
	this->vector = new char[this->count];
	for (size_t i = 0; i < this->count - 1; i++)
		this->vector[i] = list[i];
	this->vector[this->count - 1] = '\0';
	return true;
}
bool String::operator=(List<String>& list)
{
	assert(&list != nullptr);
	String::clear();
	for (size_t i = 0; i < list.getCount(); i++)
	{
		String::operator+=(list[i]);
		String::operator+=(' ');
	}
	return true;
}
#pragma endregion
#pragma endregion
#pragma region Getters
size_t String::getCount() const
{
	return this->count;
}
#pragma endregion
#pragma region Operators con strings
bool String::operator+=(const char& character)
{
	assert(&character != nullptr);
	String temp = this->operator+(character);
	return this->operator=(temp);
}
bool String::operator+=(const char other[])
{
	assert(&other != nullptr);
	String temp = this->operator+(other);
	return this->operator=(temp);
}
bool String::operator+=(const String& other)
{
	assert(&other != nullptr);
	String temp = this->operator+(other);
	return this->operator=(temp);
}
bool String::operator+=(List<char>& list)
{
	assert(&list != nullptr);
	String temp = this->operator+(list);
	return this->operator=(temp);
}
bool String::operator+=(const size_t& value)
{
	assert(&value != nullptr);
	String temp = this->operator+(value);
	return this->operator=(temp);
}
bool String::operator+=(const double& value)
{
	assert(&value != nullptr);
	String temp = this->operator+(value);
	return this->operator=(temp);
}
String String::operator+(const char& character) const
{
	assert(&character != nullptr);
	String result;
	result.semiClear();
	result.count = this->count + 1;
	result.vector = new char[result.count];
	strcpy(result.vector, this->vector);
	result.vector[result.count - 2] = character;
	result.vector[result.count - 1] = '\0';
	return result;
}
String String::operator+(const char other[]) const
{
	assert(&other != nullptr);
	String result;
	result.count = this->count + strlen(other);
	result.vector = new char[result.count];
	strcpy(result.vector, this->vector);
	strcpy((result.vector + this->count - 1), other);
	return result;
}
String String::operator+(const String& other) const
{
	assert(&other != nullptr);
	String result;
	result.count = this->count + other.count - 1;
	result.vector = new char[result.count];
	strcpy(result.vector, this->vector);
	strcpy((result.vector + this->count - 1), other.vector);
	return result;
}
String String::operator+(List<char>& list) const
{
	assert(&list != nullptr);
	String result;
	result.count = this->count + list.getCount();
	result.vector = new char[result.count];
	strcpy(result.vector, this->vector);
	for (size_t i = 0; i < list.getCount(); i++)
		result.vector[i + this->count - 1] = list[i];
	result.vector[result.count - 1] = '\0';
	return result;
}
String String::operator+(const double& value) const
{
	assert(&value != nullptr);
	std::string s = std::to_string(value);
	String valueToString(&s[0]);
	return String::operator+(valueToString);
}
String String::operator+(const size_t& value) const
{
	assert(&value != nullptr);
	std::string s = std::to_string(value);
	String valueToString(&s[0]);
	return String::operator+(valueToString);
}
#pragma endregion
#pragma region Compares
bool String::similar(const char& character) const
{
	bool temp = false;
	if (&character != nullptr)
		if (String::caracteresSimilares(this->vector[0], character))
			temp = true;
	return temp;
}
bool String::similar(const char other[]) const
{
	bool temp = false;
	if (&other != nullptr)
		if (this->count - 1 == strlen(other))
		{
			bool salir = false;
			for (size_t i = 0; i < this->count && !salir; i++)
			{
				if (!String::caracteresSimilares(this->vector[i], other[i]))
					salir = true;
			}
			temp = !salir;
		}
	return temp;
}
bool String::similar(const String& other) const
{
	bool temp = false;
	if (&other != nullptr)
		if (this->count == other.count)
		{
			bool salir = false;
			for (size_t i = 0; i < this->count && !salir; i++)
			{
				if (!String::caracteresSimilares(this->vector[i], other.vector[i]))
					salir = true;
			}
			temp = !salir;
		}
	return temp;
}
bool String::similar(List<char>& list) const
{
	return false;
}
bool String::operator==(const char& character) const
{
	bool temp = false;
	if (&character != nullptr)
		if (this->count == 2)
			if (this->vector[0] == character)
				temp = true;
	return temp;
}
bool String::operator==(const char other[]) const
{
	bool temp = false;
	if(&other != nullptr)
		if (this->count - 1 == strlen(other))
			if (strcmp(this->vector, other) == 0)
				temp = true;
	return temp;
}
bool String::operator==(const String& other) const
{
	bool temp = false;
	if (&other != nullptr)
		if (this->count == other.count)
			if (strcmp(this->vector, other.vector) == 0)
				temp = true;
	return temp;
}
bool String::operator==(List<char>& list) const
{
	bool temp = false;
	if (&list != nullptr)
		if (String::operator==(String(list)))
			temp = true;
	return temp;
}
bool String::operator!=(const char& character) const
{
	return !String::operator==(character);
}
bool String::operator!=(const char other[]) const
{
	return !String::operator==(other);
}
bool String::operator!=(const String& other) const
{
	return !String::operator==(other);
}
bool String::operator!=(List<char>& list) const
{
	return !String::operator==(list);
}
int String::compare(const String& other) const
{
	assert(&other != nullptr);
	return strcmp(this->vector, other.vector);
}
#pragma endregion
#pragma region SubStrings
String String::substring(const size_t& inicio, const size_t& end) const
{
	assert(&inicio != nullptr);
	assert(&end != nullptr);
	assert(inicio < end);
	assert(end < this->count);

	String resultado;
	resultado.semiClear();
	resultado.count = (end - inicio) + 1;
	resultado.vector = new char[resultado.count];
	for (size_t i = 0; i < resultado.count - 1; i++)
		resultado.vector[i] = this->vector[i + inicio];
	resultado.vector[resultado.count - 1] = '\0';

	return resultado;
}
String String::stringCensurado() const
{
	String resultado = *this;
	for (size_t i = 0; i < resultado.count - 1; i++)
	{
		if (resultado.vector[i] != ' ')
			resultado.vector[i] = '*';
	}
	return resultado;
}
String String::subStringCensurado(const size_t& inicio, const size_t& end) const
{
	assert(&inicio != nullptr);
	assert(&end != nullptr);
	assert(inicio < end);
	assert(end < this->count);
	String resultado = *this;
	for (size_t i = inicio; i < end; i++)
		resultado.vector[i] = '*';
	return resultado;
}
#pragma endregion
#pragma region Modificadores
size_t String::toUpper()
{
	unsigned int cambios = 0;
	for (unsigned int i = 0; i < this->count; i++)
		if (String::CambiarMayus((this->operator[](i))))
			cambios++;
	return cambios;
}
size_t String::toLower()
{
	unsigned int cambios = 0;
	for (unsigned int i = 0; i < this->count; i++)
		if (String::CambiarMinus(this->operator[](i)))
			cambios++;
	return cambios;
}
#pragma endregion
#pragma region Traductores
size_t String::toSize_T() const
{
	return atoi(this->vector);
}
double String::toDouble() const
{
	return atof(this->vector);
}
#pragma endregion
#pragma region Otros
List<size_t> String::contains(List<char>& listaCaracteres) const
{
	assert(&listaCaracteres != nullptr);
	assert(listaCaracteres.getCount() > 1);

	List<size_t> listaCoincidencias;
	for (size_t i = 0; i < listaCaracteres.getCount(); i++)
		listaCoincidencias.add(String::contains(listaCaracteres[i]));
	
	return listaCoincidencias;
}
size_t String::contains(const char& caracter) const
{
	assert(&caracter != nullptr);
	size_t coincidencias = 0;
	for (size_t i = 0; i < this->count; i++)
	{
		if (caracter == this->vector[i])
			coincidencias++;
	}
	return coincidencias;
}
size_t String::contains(const String& other) const
{
	assert(&other != nullptr);
	assert(other.getCount() > 2);
	size_t coincidencias = 0;
	for (size_t i = 0; i < this->count; i++)
	{
		for (size_t e = 0; e < other.count - 1; e++)
		{
			if (this->vector[i + e] == other.vector[e])
			{
				if (e == other.count - 2)
					coincidencias++;
			}
			else e = other.count;
		}
	}
	return coincidencias;
}
#pragma endregion
#pragma region Otras funciones
void String::clear()
{
	if (this->vector != nullptr)
		delete(this->vector);
	String::iniciarString();
}
char& String::operator[](const size_t& posicion) const
{
	assert(&posicion != nullptr);
	assert(posicion >= 0 && posicion < this->count);
	return this->vector[posicion];
}
List<String> String::stringCat(const char& separador) const
{
	assert(&separador != nullptr);
	size_t i = 0;	// Contador posicion buffer
	char* buff = new char[SIZE_BUFFER];
	String strBuff;
	List<String> result;

	for (size_t e = 0; e < this->count; e++)
	{
		// Si el caracter a guardar no es el separador
		if (separador != this->vector[e])
		{
			// Guardamos el caracter en un buffer
			buff[i] = this->vector[e];
			// Si el buffer le queda 1 posicion para estar lleno
			if (i == SIZE_BUFFER - 2)
			{
				// Le colocamos un final de linea
				buff[i + 1] = '\0';
				i = 0;
				// Lo guardamos en el stringBuffer que puede contener inf caracteres
				strBuff += buff;
			}
			// Si no continuamos sin mas
			else i++;
		}
		// Si lo es
		else
		{
			// Le colocamos un final de linea
			buff[i] = '\0';
			i = 0;
			// Lo guardamos en el stringBuffer que puede contener inf caracteres
			strBuff += buff;
			// Añadimos el string cortado a la lista
			result.add(strBuff);
			// Limpiamos el stringBuffer para reutilizarlo
			strBuff.clear();
		}
	}

	// Si salimos del blucle y no hemos llenado el buffer
	// Ponemos un \0 y lo añadimos todo al string
	if (i != 0)
	{
		// Le colocamos un final de linea
		buff[i] = '\0';
		// Lo guardamos en el stringBuffer que puede contener inf caracteres
		strBuff += buff;
		// Añadimos el string cortado a la lista
		result.add(strBuff);
	}

	//Liberamos memoria
	delete[] buff;

	return result;
}
List<String> String::stringCat(const List<char>& listaSeparadores) const
{
	assert(&listaSeparadores != nullptr);
	assert(listaSeparadores.getCount() > 1);
	size_t i = 0;	// Contador posicion buffer
	char* buff = new char[SIZE_BUFFER];
	String strBuff;
	List<String> result;

	for (size_t e = 0; e < this->count; e++)
	{
		// Si el caracter es alguno de la lista
		if (listaSeparadores.estaEnLista(this->vector[e]))
		{
			// Le colocamos un final de linea
			buff[i] = '\0';
			i = 0;
			// Lo guardamos en el stringBuffer que puede contener inf caracteres
			strBuff += buff;
			// Añadimos el string cortado a la lista
			result.add(strBuff);
			// Limpiamos el stringBuffer para reutilizarlo
			strBuff.clear();
		}
		// Si lo es
		else
		{
			// Guardamos el caracter en un buffer
			buff[i] = this->vector[e];
			// Si el buffer le queda 1 posicion para estar lleno
			if (i == SIZE_BUFFER - 2)
			{
				// Le colocamos un final de linea
				buff[i + 1] = '\0';
				i = 0;
				// Lo guardamos en el stringBuffer que puede contener inf caracteres
				strBuff += buff;
			}
			// Si no continuamos sin mas
			else i++;
		}
	}

	// Si salimos del blucle y no hemos llenado el buffer
	// Ponemos un \0 y lo añadimos todo al string
	if (i != 0)
	{
		// Le colocamos un final de linea
		buff[i] = '\0';
		// Lo guardamos en el stringBuffer que puede contener inf caracteres
		strBuff += buff;
		// Añadimos el string cortado a la lista
		result.add(strBuff);
	}

	//Liberamos memoria
	delete[] buff;

	return result;
}
List<String> String::stringCat(const String& separador) const
{
	assert(&separador != nullptr);
	assert(separador.getCount() > 2);
	size_t i = 0;	// Contador posicion buffer
	char* buff = new char[SIZE_BUFFER];
	String strBuff;
	List<String> result;

	for (size_t e = 0; e < this->count; e++)
	{
		// Si el caracter actual coincide con el primero del separador
		if (this->vector[e] == separador[0])
		{
			for (size_t r = 0; r < separador.count - 1; r++)
			{
				// Si coincide el caracter actual + r con el caracter del separador + r 
				if (this->vector[e + r] == separador.vector[r])
				{
					if (r == separador.count - 2)
					{
						// Le colocamos un final de linea
						buff[i] = '\0';
						i = 0;
						// Lo guardamos en el stringBuffer que puede contener inf caracteres
						strBuff += buff;
						// Añadimos el string cortado a la lista
						result.add(strBuff);
						// Limpiamos el stringBuffer para reutilizarlo
						strBuff.clear();
						// Avanzamos tanas posiciones como caracteres coincidan
						e += r;
					}
				}
				// Si no
				else
				{
					// Guardamos el caracter en un buffer
					buff[i] = this->vector[e];

					// Salimos del bucle
					r = separador.count;

					// Si el buffer le queda 1 posicion para estar lleno
					if (i == SIZE_BUFFER - 2)
					{
						// Le colocamos un final de linea
						buff[i + 1] = '\0';
						i = 0;
						// Lo guardamos en el stringBuffer que puede contener inf caracteres
						strBuff += buff;
					}
					// Si no continuamos sin mas
					else i++;
				}
			}
		}
		// Si no coincide
		else
		{
			// Guardamos el caracter en un buffer
			buff[i] = this->vector[e];
			// Si el buffer le queda 1 posicion para estar lleno
			if (i == SIZE_BUFFER - 2)
			{
				// Le colocamos un final de linea
				buff[i + 1] = '\0';
				i = 0;
				// Lo guardamos en el stringBuffer que puede contener inf caracteres
				strBuff += buff;
			}
			// Si no continuamos sin mas
			else i++;
		}
	}

	// Si salimos del blucle y no hemos llenado el buffer
	// Ponemos un \0 y lo añadimos todo al string
	if (i != 0)
	{
		// Le colocamos un final de linea
		buff[i] = '\0';
		// Lo guardamos en el stringBuffer que puede contener inf caracteres
		strBuff += buff;
		// Añadimos el string cortado a la lista
		result.add(strBuff);
	}

	//Liberamos memoria
	delete[] buff;

	return result;
}
/*List<String> String::stringCat(const String& separador) const
{
	assert(&separador != nullptr);
	assert(separador.getCount() > 2);

	String buffer;
	List<String> result;
	for (size_t i = 0; i < this->count - 1; i++)
	{
		if (this->vector[i] == separador[0])
		{
			for (size_t e = 0; e < separador.count - 1; e++)
			{
				if (this->vector[i + e] == separador.vector[e])
				{
					if (e == separador.count - 2)
					{
						result.add(buffer);
						buffer.clear();
						i += e;
					}
				}
				else
				{
					buffer += this->vector[i];
					e = separador.count;
				}
			}
		}
		else
			buffer += this->vector[i];
	}
	result.add(buffer);
	return result;
}*/
#pragma endregion
