#include "ClienteEjecutacion.h"
#include "../../Herramientas/socket.h"

#pragma region Protercted
ClienteEjecutacion::ClienteEjecutacion() {}
ClienteEjecutacion::~ClienteEjecutacion() {}
#pragma endregion
void ClienteEjecutacion::cerrarSocket()
{
	if (this->sock > 0)
	{
		#ifdef _WIN32
		closesocket(sock);
		#elif __unix__
		close(sock);
		#endif
		this->sock = -1;
	}
}
