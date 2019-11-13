#pragma warning(disable:4244)
#pragma warning(disable:4267)
#include "Cliente.h"
#include "../../Herramientas/socket.h"
#include "../../Herramientas/List.h"
#include "../../Herramientas/File.h"
#include "../../Herramientas/String.h"

#define RED AF_INET

#pragma region Protercted
Cliente::Cliente()
{
	this->sock = -1;
	this->nombre = new String();
	this->logError = new String();
	this->logGeneral = new String();
	Cliente::iniciarCliente("", "", "");
}
Cliente::~Cliente()
{
	if (this->nombre != nullptr) delete this->nombre;
	if (this->logError != nullptr) delete this->logError;
	if (this->logGeneral != nullptr) delete this->logGeneral;
	this->sock = -1;
	this->nombre = nullptr;
	this->logError = nullptr;
	this->logGeneral = nullptr;
}
void Cliente::ClearCliente()
{
	if (this->nombre != nullptr) delete this->nombre;
	if (this->logError != nullptr) delete this->logError;
	if (this->logGeneral != nullptr) delete this->logGeneral;
	this->sock = -1;
	this->nombre = new String();
	this->logError = new String();
	this->logGeneral = new String();
}
#pragma endregion
#pragma region Public
void Cliente::iniciarCliente(const String& nombreCliente, const String& logErrorFileName, const String& logGeneralFileName)
{
	assert(&nombreCliente != nullptr);
	assert(&logErrorFileName != nullptr);
	assert(&logGeneralFileName != nullptr);

	// Nombre del logError donde guarda los errores de las conexiones etc
	if (logErrorFileName.getCount() == 1)
		this->logError->operator=("logError.txt");
	else this->logError->operator=(logErrorFileName);

	// Nombre del log donde guarda el historial de las solicitudes a los servicios
	if (logGeneralFileName.getCount() == 1)
		this->logGeneral->operator=("log.txt");
	else this->logGeneral->operator=(logGeneralFileName);

	// Nombre del cliente
	if (nombreCliente.getCount() == 1)
		this->nombre->operator=("Cliente");
	else this->nombre->operator=(nombreCliente);

}
List<EstadoCliente> Cliente::enviarSolicitud(const String& ipServer, const unsigned short& puerto, const String& solicitud)
{
	assert(&ipServer != nullptr);
	assert(&puerto != nullptr);
	assert(&solicitud != nullptr);
	assert(ipServer.getCount() > 1);

	List<EstadoCliente> listaEstados;
	this->sock = socket(RED, SOCK_STREAM, 0);

	if(sock < 0)
		listaEstados.add(EstadoCliente::ErrorSocketNoDisponible);

	struct sockaddr_in serviceAdress;
	serviceAdress.sin_family = RED;
	serviceAdress.sin_port = htons(puerto);

	if (listaEstados.getCount() == 0)
		if(inet_pton(RED, &ipServer[0], &serviceAdress.sin_addr) <= 0)
			listaEstados.add(EstadoCliente::ErrorIpServer);

	if(listaEstados.getCount() == 0)
		if (connect(sock, (struct sockaddr*)&serviceAdress, sizeof(serviceAdress)) < 0)
			listaEstados.add(EstadoCliente::ErrorConexionFallida);
	
	if (listaEstados.getCount() == 0)
	{
		send(sock, &solicitud[0], solicitud.getCount(), 0);
		listaEstados.add(EstadoCliente::PeticionSolicitada);
	}
	return listaEstados;
}
String Cliente::leerRespuesta()
{
	String resultado;
	if (this->sock > 0)
	{
		resultado = FILE_SINGLETON->leerSocket(sock, '\0');
		#ifdef _WIN32
		closesocket(sock);
		#elif __unix__
		close(sock);
		#endif
		this->sock = -1;
	}
	else resultado = "Socket invalido";
	return resultado;
}
#pragma endregion
