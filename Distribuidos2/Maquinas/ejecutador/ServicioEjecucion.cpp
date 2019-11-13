#include "ServicioEjecucion.h"
#include "../../Herramientas/socket.h"
#include "../../Herramientas/List.h"
#include "../../Herramientas/File.h"
#include "../../Herramientas/String.h"
#include "ClienteEjecutador.h"

#pragma region Protected
ServicioEjecucion::ServicioEjecucion() {}
ServicioEjecucion::~ServicioEjecucion() {}
bool ServicioEjecucion::comprobarServicio(const String& nombre, const unsigned short& puerto) const
{
	bool resultado = false;
	// Hacemos una request vacia al servidor del lector
	List<EstadoCliente> listClientResult = CLIENTEEJECUCION->enviarSolicitud("localhost", puerto, "vivo");
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
					system(&nombre[0]);
				case EstadoCliente::PeticionSolicitada:
					resultado = true;
					break;
			}
		}
	}
	String basura = CLIENTEEJECUCION->leerRespuesta();
	return resultado;
}
#pragma endregion
void ServicioEjecucion::resolverSolicitud(const int& newsock_fd) const
{
	String resultado;

	// Leemos la peticion y la guardamos
	String peticion = FILE_SINGLETON->leerSocket(newsock_fd, '\0');
	// Guardamos en el log la peticion recibida
	FILE_SINGLETON->escribirFicheroAlFinal(*this->logGeneral, peticion);

	// Si la peticion es el proceso lector
	if (peticion.similar("LeeR"))
	{
		// Si el servicio esta OK
		if (ServicioEjecucion::comprobarServicio("./lector", PUERTOLECTOR))
		{
			// Si la peticion al servicio va bien
			if (CLIENTEEJECUCION->enviarSolicitud("localhost", PUERTOLECTOR, "leer")[0] == EstadoCliente::PeticionSolicitada)
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
		if (ServicioEjecucion::comprobarServicio("./sumador", PUERTOSUMADOR))
		{
			// Si la peticion al servicio va bien
			if (CLIENTEEJECUCION->enviarSolicitud("localhost", PUERTOSUMADOR, "sumar").getCount() > 0)
				resultado = CLIENTEEJECUCION->leerRespuesta();
			// Si la peticion ha devuelto algun error
			else resultado = "Error internal server sumador";
		}
		// Si este o el otro servicio no esta OK
		else resultado = "Error internal server ejecutor";
	}
	else
		resultado = "Invalid request";
	send(newsock_fd, &resultado[0], resultado.getCount(), 0);
	#ifdef _WIN32
	closesocket(newsock_fd);
	#elif __unix__
	close(newsock_fd);
	#endif
}
