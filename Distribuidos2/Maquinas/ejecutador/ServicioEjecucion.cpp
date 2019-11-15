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
bool ServicioEjecucion::comprobarServicio(const String& nombre, const unsigned short& puerto) const
{
	// Hacemos una request vacia al servidor del lector
	List<EstadoCliente> listClientResult = CLIENTEEJECUCION->enviarSolicitud("127.0.0.1", puerto, "vivo");
	// Si no devuelve nada
	if (listClientResult.getCount() == 0)
		assert(false);
	// Si devuelve algo lo analizamos
	else
	{
		// Por cada codigo vemos que hacemos
		for (size_t i = 0; i < listClientResult.getCount(); i++)
		{
			switch (listClientResult[i])
			{
				// Si el cliente esta apagado lo iniciamos
				case EstadoCliente::ErrorConexionFallida:
					if (fork() == 0)
						execl("/usr/bin/xterm", "xterm", &nombre[0], NULL);
					else
					{
						sleep(5);
						system("echo Despierto!");
					}
			}
		}
	}
	String basura = CLIENTEEJECUCION->leerRespuesta();
	return true;
}
#pragma endregion
void ServicioEjecucion::resolverSolicitud(const int& newsock_fd) const
{
	//Resultado de la peticion
	String resultado;
	// Leemos la peticion y la guardamos
	String peticion = FILE_SINGLETON->leerSocket(newsock_fd, '\0');
	// Guardamos en el log la peticion recibida
	FILE_SINGLETON->escribirFicheroAlFinal(*this->logGeneral, peticion);

	// Si la peticion es el proceso lector
	if (peticion.similar("LeeR"))
	{
		// Si el servicio esta OK
		if (ServicioEjecucion::comprobarServicio("./serv_lector", PUERTOLECTOR))
		{
			// Si la peticion al servicio va bien
			if (CLIENTEEJECUCION->enviarSolicitud("127.0.0.1", PUERTOLECTOR, peticion)[0] == EstadoCliente::PeticionSolicitada)
				resultado = CLIENTEEJECUCION->leerRespuesta();
			// Si la peticion ha devuelto algun error
			else resultado = "Error internal server lector";
		}
		// Si este o el otro servicio no esta OK
		else resultado = "Error internal server ejecutor";
	}
	// Si la peticion es el proceso suma
	else if (peticion.similar("SuMa"))
	{
		// Si el servicio esta OK
		if (ServicioEjecucion::comprobarServicio("./serv_sumador", PUERTOSUMADOR))
		{
			// Si la peticion al servicio va bien
			if (CLIENTEEJECUCION->enviarSolicitud("127.0.0.1", PUERTOSUMADOR, peticion).getCount() > 0)
				resultado = CLIENTEEJECUCION->leerRespuesta();
			// Si la peticion ha devuelto algun error
			else resultado = "Error internal server sumador";
		}
		// Si este o el otro servicio no esta OK
		else resultado = "Error internal server ejecutor";
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
