#include "ServicioSumador.h"
#include "../../Herramientas/socket.h"
#include "../../Herramientas/List.h"
#include "../../Herramientas/File.h"
#include "../../Herramientas/String.h"

#pragma region Protected
ServicioSumador::ServicioSumador() {}
ServicioSumador::~ServicioSumador() {}
#pragma endregion
void ServicioSumador::resolverSolicitud(const int& newsock_fd) const
{
	String peticion = FILE_SINGLETON->leerSocket(newsock_fd, '\0');
	FILE_SINGLETON->escribirFicheroAlFinal(*this->logGeneral, peticion);
	String resultado;
	if (peticion.similar("vivo"))
		resultado = "Yay";
	else if (peticion.similar("suma"))
		resultado = (String("") + (size_t)(10 + 20));
	else
		resultado = "Invalid request sumador";

	send(newsock_fd, &resultado[0], resultado.getCount(), 0);
	#ifdef _WIN32
	closesocket(newsock_fd);
	#elif __unix__
	close(newsock_fd);
	#endif
}
