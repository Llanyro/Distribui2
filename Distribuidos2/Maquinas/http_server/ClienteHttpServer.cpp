#include "ClienteHttpServer.h"
#include "../../Herramientas/socket.h"

#pragma region Protercted
ClienteHttpServer::ClienteHttpServer() {}
ClienteHttpServer::~ClienteHttpServer() {}
#pragma endregion
void ClienteHttpServer::cerrarSocket()
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
