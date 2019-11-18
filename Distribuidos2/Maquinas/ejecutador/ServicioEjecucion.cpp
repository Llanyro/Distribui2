#pragma warning(disable:4267)
#include "ServicioEjecucion.h"
#include "../../Herramientas/socket.h"
#include "../../Herramientas/List.h"
#include "../../Herramientas/File.h"
#include "../../Herramientas/String.h"
#include "ClienteEjecutacion.h"
#include <cstdlib>

#pragma region Protected
ServicioEjecucion::ServicioEjecucion() {}
ServicioEjecucion::~ServicioEjecucion() {}
#pragma endregion
void ServicioEjecucion::resolverSolicitud(const int& newsock_fd) const
{
	//Resultado de la peticion
	String resultado;
	// Leemos la peticion y la guardamos
	String peticion = FILE_SINGLETON->leerSocket(newsock_fd, '\0');
	// Guardamos en el log la peticion recibida
	FILE_SINGLETON->escribirFicheroAlFinal(*this->logGeneral, peticion);

	if (peticion.similar("iniciar leer"))
	{
		if (CLIENTEEJECUCION->enviarSolicitud("127.0.0.1", PUERTOLECTOR, "vivo")[0] != EstadoCliente::PeticionSolicitada)
			system("./serv_lector &");
		resultado = "OK";
	}
	else if (peticion.similar("iniciar suma"))
	{
		if (CLIENTEEJECUCION->enviarSolicitud("127.0.0.1", PUERTOSUMADOR, "vivo")[0] != EstadoCliente::PeticionSolicitada)
			system("./serv_sumador &");
		resultado = "OK";
	}
	// Si la peticion es el proceso lector
	else if (peticion.similar("LeeR"))
	{
		// Si la peticion al servicio va bien
		if (CLIENTEEJECUCION->enviarSolicitud("127.0.0.1", PUERTOLECTOR, peticion)[0] == EstadoCliente::PeticionSolicitada)
			resultado = CLIENTEEJECUCION->leerRespuesta();
		// Si la peticion ha devuelto algun error
		else resultado = "Error internal server lector";
	}
	// Si la peticion es el proceso suma
	else if (peticion.similar("SuMa"))
	{
		// Si la peticion al servicio va bien
		if (CLIENTEEJECUCION->enviarSolicitud("127.0.0.1", PUERTOSUMADOR, peticion)[0] == EstadoCliente::PeticionSolicitada)
			resultado = CLIENTEEJECUCION->leerRespuesta();
		// Si la peticion ha devuelto algun error
		else resultado = "Error internal server sumador";
	}
	else
		resultado = "Invalid request";

	//Enviamos el resultado
	send(newsock_fd, &resultado[0], resultado.getCount(), 0);

	//Cerramos el socket
	#ifdef _WIN32
	closesocket(newsock_fd);
	#elif __unix__
	close(newsock_fd);
	#endif
}
