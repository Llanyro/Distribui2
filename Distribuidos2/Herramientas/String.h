#pragma once
#ifdef __unix__
#include <cstddef>
#elif _WIN32

#endif // __linux__

template<class T>
class List;

/*
	String V1
	No posee funciones tales como trim o substring (Disponible en siguientes versiones)
*/
class String
{
	protected:
		char* vector;
		size_t count;
		bool caracteresSimilares(const char& value1, const char& value2) const;
		void iniciarString();
		// Nos dice si un caracter es mayuscula o no (1) o (-1)
		// Si no es ninguna de las dos devuelve 0
		// Complejidad temporal y espacial: O(1) y M(1)
		int IsMayus(const char& value);											///OK
		// Nos comprueva si es minuscula y lo tranforma en mayuscula
		// Retorno: True si ha cambiado la clase a minuscula
		// Complejidad temporal y espacial: O(1) y M(1)
		bool CambiarMayus(char& value);											///OK
		// Nos comprueva si es minuscula y lo tranforma en mayuscula
		// Retorno: True si ha cambiado la clase a minuscula
		// Complejidad temporal y espacial: O(1) y M(1)
		bool CambiarMinus(char& value);											///OK
		void semiClear();
	public:
		#pragma region Constructores
		String();											/// OK
		String(const char& character);						///	OK
		String(const char other[]);							///	OK
		String(const String& other);						///	OK
		String(List<char>& list);							///	OK
		String(List<String>& list);							///	OK
		String(List<String>& list, const char& separador);	///	OK
		String(const char* block, const size_t& size);		/// OK
		~String();											/// OK
		bool operator=(const char& character);				/// OK
		bool operator=(const char other[]);					/// OK
		bool operator=(const String& other);				/// OK
		bool operator=(List<char>& list);					/// OK
		bool operator=(List<String>& list);					/// OK
		#pragma endregion
		#pragma region Getters
		// Devuelve el numero de caracteres del string
		// Complejidad temporal y espacial: O(1) y M(1)
		size_t getCount() const;
		#pragma endregion
		#pragma region Operators con strings
		bool operator+=(const char& character);			/// OK
		bool operator+=(const char other[]);			/// OK
		bool operator+=(const String& other);			/// OK
		bool operator+=(List<char>& list);				/// OK
		bool operator+=(const size_t& value);
		bool operator+=(const double& value);
		String operator+(const char& character) const;	/// OK
		String operator+(const char other[]) const;		/// OK
		String operator+(const String& other) const;	/// OK
		String operator+(List<char>& list) const;		/// OK
		String operator+(const double& value) const;	/// OK
		String operator+(const size_t& value) const;	/// OK
		#pragma endregion
		#pragma region Compares
		bool similar(const char& character) const;
		bool similar(const char other[]) const;
		bool similar(const String& other) const;
		bool similar(List<char>& list) const;
		bool operator==(const char& character) const;
		bool operator==(const char other[]) const;
		bool operator==(const String& other) const;
		bool operator==(List<char>& list) const;
		bool operator!=(const char& character) const;
		bool operator!=(const char other[]) const;
		bool operator!=(const String& other) const;
		bool operator!=(List<char>& list) const;
		int compare(const String& other) const;
		#pragma endregion
		#pragma region SubStrings
		String substring(const size_t& inicio, const size_t& end) const;
		String stringCensurado() const;
		String subStringCensurado(const size_t& inicio, const size_t& end) const;
		#pragma endregion
		#pragma region Modificadores
		// Convierte todos los caracteres en letras mayúsculas.
		// Devuelve el número de caracteres que han sido cambiados a mayúsculas. 
		// Se usa la funcion
		// Complejidad temporal y espacial: O(this->count) y M(1)
		size_t toUpper();																	///OK
		// Convierte todos los caracteres en letras minúsculas.
		// Devuelve el número de caracteres que han sido cambiados a minúsculas.
		// Se permite usar tolower de C
		// Mayus to minus
		// Complejidad temporal y espacial: O(this->count) y M(1)
		size_t toLower();																	///OK
		#pragma endregion
		#pragma region Traductores
		size_t toSize_T() const;
		double toDouble() const;
		#pragma endregion
		#pragma region Otros
		List<size_t> contains(List<char>& listaCaracteres) const;
		size_t contains(const char& caracter) const;
		size_t contains(const String& other) const;
		#pragma endregion
		#pragma region Otras funciones
		void clear();									/// OK
		char& operator[](const size_t& posicion) const;	/// OK
		List<String> stringCat(const char& separador) const;
		List<String> stringCat(const List<char>& listaSeparadores) const;
		List<String> stringCat(const String& separador) const;
		#pragma endregion
};
