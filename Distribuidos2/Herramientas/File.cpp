#include "File.h"
#include "List.h"
#include "String.h"
#include <fstream>

#ifdef _WIN32
#include <winsock2.h>
#include <Ws2tcpip.h>

#elif __unix__
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

#define SIZE_BUFFER 128

using namespace std;

#pragma region Constructores
File::File() { }
File::~File() { }
#pragma endregion
#pragma region Public
String File::leerFichero(const String& fileName)
{
	assert(&fileName != nullptr);
	assert(fileName.getCount() > 1);
	ifstream file(&fileName[0], ifstream::in);
	String str;
	size_t i = 0;
	char* buff = new char[SIZE_BUFFER];

	while (file.get(buff[i]))
	{
		if (i == SIZE_BUFFER - 2)
		{
			buff[i + 1] = '\0';
			i = 0;
			str += buff;
		}
		else i++;
	}

	// Si salimos del blucle y no hemos llenado el buffer
	// Ponemos un \0 y lo añadimos todo al string
	if (i != 0)
	{
		buff[i] = '\0';
		str += buff;
	}

	//Liberamos memoria y cerramos el fichero
	file.close();
	delete[] buff;

	return str;
}
bool File::escribirFichero(const String& fileName, const String& asciiText) const
{
	assert(&fileName != nullptr);
	assert(&asciiText != nullptr);
	assert(fileName.getCount() > 1);
	ofstream file(&fileName[0], ifstream::out);
	bool temp = false;
	if (file.is_open())
	{
		file << &asciiText[0] << endl;
		temp = true;
		file.close();
	}
	return temp;
}
bool File::escribirFichero(List<String>& list) const
{
	assert(&list != nullptr);
	assert(list.getCount() > 1);
	ofstream file(&list[0][0], ifstream::out);
	bool temp = false;
	if (file.is_open())
	{
		for (size_t i = 1; i < list.getCount(); i++)
			file << &list[i][0];
		temp = true;
		file.close();
	}
	return temp;
}
bool File::escribirFichero(List<String>& list, const char& caracterFinal) const
{
	assert(&list != nullptr);
	assert(list.getCount() > 2);
	ofstream file(&list[0][0], ifstream::out);
	bool temp = false;
	if (file.is_open())
	{
		for (size_t i = 1; i < list.getCount(); i++)
			file << &list[i][0] << caracterFinal;
		temp = true;
		file.close();
	}
	return temp;
}
bool File::escribirFicheroAlFinal(const String& fileName, const String& asciiText) const
{
	assert(&fileName != nullptr);
	assert(&asciiText != nullptr);
	assert(fileName.getCount() > 1);
	ofstream file(&fileName[0], ifstream::app);
	bool temp = false;
	if (file.is_open())
	{
		file << &asciiText[0] << endl;
		temp = true;
		file.close();
	}
	return temp;
}
bool File::escribirFicheroAlFinal(List<String>& list) const
{
	assert(&list != nullptr);
	assert(list.getCount() > 1);
	ofstream file(&list[0][0], ifstream::app);
	bool temp = false;
	if (file.is_open())
	{
		for (size_t i = 1; i < list.getCount(); i++)
			file << &list[i][0];
		temp = true;
		file.close();
	}
	return temp;
}
bool File::escribirFicheroAlFinal(List<String>& list, const char& caracterFinal) const
{
	assert(&list != nullptr);
	assert(list.getCount() > 1);
	ofstream file(&list[0][0], ifstream::app);
	bool temp = false;
	if (file.is_open())
	{
		for (size_t i = 1; i < list.getCount(); i++)
			file << &list[i][0] << caracterFinal;
		temp = true;
		file.close();
	}
	return temp;
}
String File::leerSocket(const int& nuevoSocket, const char& finalPeticion) const
{
	String peticion;
	size_t i = 0;
	char* buff = new char[SIZE_BUFFER];

	// Copiamos al buffer y cuando este lleno lo pasamos al string
	char c = ' ';
	while (c != finalPeticion)
	{
		recv(nuevoSocket, &c, 1, 0);
		if (c != finalPeticion)
		{
			buff[i] = c;
			if (i == SIZE_BUFFER - 1)
			{
				i = 0;
				peticion += buff;
			}
			else i++;
		}
	}

	// Si salimos del blucle y no hemos llenado el buffer
	// Ponemos un \0 y lo añadimos todo al string
	if (i != 0)
	{
		buff[i] = '\0';
		peticion += buff;
	}
	//Liberamos memoria
	delete[] buff;

	return peticion;
}
#pragma endregion
#pragma region Sokets_HTTP
void File::readLine(const int& socket, List<String*>* line) const
{
	String* str = new String();
	char c = ' ';
	while (c != '\n')
	{
		recv(socket, &c, 1, 0);
		if (c == ' ' || c == '\n')
		{
			if (str->getCount() > 1)
			{
				line->add(str);
				str = new String();
			}
		}
		else if (c != '\r')
			str->operator+=(c);
	}
}
void File::readLines(int socket, List<List<String*>*>* lines) const
{
	List<String*>* line;
	do {
		line = new List<String*>();
		readLine(socket, line);
		lines->add(line);
	} while (line->getCount() != 0);
}
void File::deleteLines(List<List<String*>*>* lines) const
{
	for (size_t i = 0; i < lines->getCount(); i++)
	{
		List<String*>* temp = lines->operator[](i);
		for (size_t e = 0; e < temp->getCount(); e++)
		{
			delete temp->operator[](e);
		}
		delete temp;
	}
}
void File::readPostLine(int socket, List<String*>* line, int length)
{
	String* str = new String();
	char c = ' ';
	int pos = 0;
	while (pos != length)
	{
		recv(socket, &c, 1, 0);
		if (c == '&')
		{
			line->add(str);
			str = new String("");
			pos++;
		}
		else if (pos == (length - 1))
		{
			str->operator+=(c);
			line->add(str);
			pos = length;
		}
		else
		{
			str->operator+=(c);
			pos++;
		}
	}
}
String File::getFromPost(List<String*>& postLine, String param) const
{
	String result;
	for (size_t i = 0; i < postLine.getCount(); i++)
	{
		List<String> temp = postLine[i]->stringCat('=');
		if (temp[0].compare(param) == 0)
			result = temp[1];
	}
	return result;
}
#pragma endregion
