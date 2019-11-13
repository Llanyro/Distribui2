#pragma once
#include "Singleton.h"

#define FILE_SINGLETON File::getInstancia()

template <class T>
class List;
class String;

class File : public Singleton<File>
{
	private:
		#pragma region Constructores
		friend class Singleton<File>;
		File();
		~File();
		#pragma endregion
	public:
		// Lee el fichero recibido escrito escrito en ascii y lo devuelve en string
		String leerFichero(const String& fileName);
		// Escribe en un fichero en ascii un string dado
		bool escribirFichero(const String& fileName, const String& asciiText) const;
		/*
			Escribe una lista de strings en un fichero
			Si el fichero existe o no no importa (Lo limpia igual)
			El nombre del fichero esta incluido en la primera linea de la lista
			No incluye un salto de linea al final de cada string
		*/
		bool escribirFichero(List<String>& list) const;
		/*
			Escribe una lista de strings en un fichero
			Si el fichero existe o no no importa (Lo limpia igual)
			El nombre del fichero esta incluido en la primera linea de la lista
			El caracterFinal se coloca despues de colocar cada string
		*/
		bool escribirFichero(List<String>& list, const char& caracterFinal) const;
		// Escribe al final de un fichero en ascii un string dado
		bool escribirFicheroAlFinal(const String& fileName, const String& asciiText) const;
		/* 
			Escribe una lista de strings en un fichero usando append
			El nombre del fichero esta incluido en la primera linea de la lista
			No incluye un salto de linea al final de cada string
		*/
		bool escribirFicheroAlFinal(List<String>& list) const;
		/*
			Escribe una lista de strings en un fichero usando append
			El nombre del fichero esta incluido en la primera linea de la lista
			El caracterFinal se coloca despues de colocar cada string
		*/
		bool escribirFicheroAlFinal(List<String>& list, const char& caracterFinal) const;
		// Lee el string recibido de un socket dado
		String leerSocket(const int& nuevoSocket, const char& finalPeticion) const;
		#pragma region Otros
		void readLine(const int& socket, List<String*>* line) const;
		void readLines(int socket, List<List<String*>*>* lines) const;
		void deleteLines(List<List<String*>*>* lines) const;
		void readPostLine(int socket, List<String*>* line, int length);
		String getFromPost(List<String*>& postLine, String param) const;
		#pragma endregion
};
