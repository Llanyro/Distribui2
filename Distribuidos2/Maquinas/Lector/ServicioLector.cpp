#include "ServicioLector.h"
#include "../../Herramientas/socket.h"
#include "../../Herramientas/List.h"
#include "../../Herramientas/File.h"
#include "../../Herramientas/String.h"

#pragma region Protected
ServicioLector::ServicioLector() {}
ServicioLector::~ServicioLector() {}
#pragma endregion
void ServicioLector::resolverSolicitud(const int& newsock_fd) const
{
	String peticion = FILE_SINGLETON->leerSocket(newsock_fd, '\0');
	FILE_SINGLETON->escribirFicheroAlFinal(*this->logGeneral, peticion);
	String resultado;
	if (peticion.similar("vivo"))
		resultado = "Yay";
	else if (peticion.similar("leer"))
		resultado = FILE_SINGLETON->leerFichero("./Hola.txt");
	else
		resultado = "Invalid request lector";

	send(newsock_fd, &resultado[0], resultado.getCount(), 0);
	#ifdef _WIN32
	closesocket(newsock_fd);
	#elif __unix__
	close(newsock_fd);
	#endif
}
