#pragma once
#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#ifdef _WIN32
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <string>
#pragma comment(lib, "Ws2_32.lib")
#elif __unix__
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#endif

#include <vector>
#include <map>

struct st_mysql;
class String;
template<class T, class T1>
class Diccionario;
template<class T>
class List;
class String;

typedef enum httpRequest_t
{
	GET,
	HEAD,
	POST,
	PUT,
	DELETE_2,
	CONNECT,
	OPTIONS,
	TRACE
}httpRequest_t;

class httpServer
{
	private:
		st_mysql* serverPointer;
		int sock_fd;
		int sessionID;
		std::string files_path="/home/lubuntu/share/http_server/html_dir";
		std::map<std::string,std::string> mimeTypes;
		Diccionario<String, String>* diccionarioIP;

		#pragma region Private
		void recogerIPServiciosDisponibles() const;
		bool isConectedToDataBase() const;

		#pragma endregion


	public:
		#pragma region Constructores
		httpServer(unsigned short port);
		httpServer(unsigned short port, std::string path, std::string ipDB, std::string user, std::string pass);
		~httpServer();
		#pragma endregion


		int  waitForConnections();
		void resolveRequests(int newsock_fd);
		void sendContent(int newsock_fd,char* httpHeader,unsigned long int headerLen, char* content, unsigned long int contentLen);
		void sendFile(int newsock_fd, const char* file);
		void generarResultadoHtml(const String& resultadoLeer, const String& resultadoSuma) const;
		std::string getmimeType(const char* file);
		void buildMimetypeTable();
		int getHTTPParameter(std::vector<std::vector<std::string*>*> *lines,std::string parameter);
		bool validatePassword(std::string username, std::string password);
};
#endif // HTTPSERVER_H
