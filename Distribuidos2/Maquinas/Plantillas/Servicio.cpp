#pragma warning(disable:4267)
#pragma warning(disable:4244)
#include "Servicio.h"
#include "../../Herramientas/socket.h"
#include "../../Herramientas/List.h"
#include "../../Herramientas/File.h"
#include "../../Herramientas/String.h"

#define RED AF_INET

#pragma region Protercted
Servicio::Servicio()
{
	this->nombre = new String();
	this->logError = new String();
	this->logGeneral = new String();
	this->direccionIP = new sockaddr_in();
	this->socket_fd = -1;
	this->servicioIniciado = false;
}
Servicio::~Servicio()
{
	if (this->nombre != nullptr) delete this->nombre;
	if (this->logError != nullptr) delete this->logError;
	if (this->logGeneral != nullptr) delete this->logGeneral;
	if (this->direccionIP != nullptr) delete this->direccionIP;
	this->nombre = nullptr;
	this->logError = nullptr;
	this->logGeneral = nullptr;
	this->direccionIP = nullptr;
	this->socket_fd = 0;
	this->servicioIniciado = false;
}
void Servicio::ClearServicio()
{
	if (this->nombre != nullptr) delete this->nombre;
	if (this->logError != nullptr) delete this->logError;
	if (this->logGeneral != nullptr) delete this->logGeneral;
	if (this->direccionIP != nullptr) delete this->direccionIP;
	this->nombre = new String();
	this->logError = new String();
	this->logGeneral = new String();
	this->direccionIP = new sockaddr_in();
	this->socket_fd = -1;
	this->servicioIniciado = false;
}
#pragma endregion
#pragma region Public
void Servicio::resolverSolicitud(const int& newsock_fd) const
{
	String peticion = FILE_SINGLETON->leerSocket(newsock_fd, '\0');
	FILE_SINGLETON->escribirFicheroAlFinal(*this->logGeneral, peticion);
	send(newsock_fd, &peticion[0], peticion.getCount(), 0);

	#ifdef _WIN32
    closesocket(newsock_fd);
    #elif __unix__
    close(newsock_fd);
    #endif
}
int Servicio::escharSolicitudes() const
{
	struct sockaddr_in cli_addr;
	socklen_t clilen = sizeof(cli_addr);
	return accept(this->socket_fd, (struct sockaddr*)&cli_addr, &clilen);
}
List<EstadoServicio> Servicio::iniciarServicio(const String& nombre, const String& logErrorFileName, const String& logGeneralFileName, const String& direccionIP, const unsigned short& puertoEscucha)
{
	assert(&nombre != nullptr);
	assert(&logErrorFileName != nullptr);
	assert(&logGeneralFileName != nullptr);
	assert(&direccionIP != nullptr);
	assert(&puertoEscucha != nullptr);

	assert(nombre.getCount() > 1);
	assert(direccionIP.getCount() > 1);

	List<EstadoServicio> listaEstados;
	// Si el servicio no esta inicializado
	if (!this->servicioIniciado)
	{
		#pragma region Seleccion de puerto
		// Creamos un socket
		this->socket_fd = socket(RED, SOCK_STREAM, 0);
		if (this->socket_fd < 0)
			listaEstados.add(EstadoServicio::ErrorSocketNoDisponible);

		// Iniciamos el socket en el puerto 8080
		#ifdef _WIN32
		setsockopt(this->socket_fd, SOL_SOCKET, SO_BROADCAST, &this->option, sizeof(option));
		#elif __unix__
		setsockopt(this->socket_fd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), &option, sizeof(option));
		#endif

		// Creamos una estructura con el puerto de escucha
		this->direccionIP->sin_family = RED;
		this->direccionIP->sin_addr.s_addr = INADDR_ANY;
		this->direccionIP->sin_port = htons(puertoEscucha);

		// Asignamos el socket al puerto de la estructura creada
		if(bind(this->socket_fd, (struct sockaddr*)this->direccionIP, sizeof(*this->direccionIP)) < 0)
			listaEstados.add(EstadoServicio::ErrorOnBinding);

		// Empezamos a escuchar el puerto
		if(listen(this->socket_fd, 3) < 0)
			listaEstados.add(EstadoServicio::ErrorNoEscuchando);
		#pragma endregion

		// Si hasta aqui no hay errores completamos la clase
		if (listaEstados.getCount() == 0)
		{
			listaEstados.add(EstadoServicio::Iniciado);
			this->servicioIniciado = true;

			// Nombre del logError donde guarda los errores de las conexiones etc
			if (logErrorFileName.getCount() == 1)
				this->logError->operator=("logError.txt");
			else this->logError->operator=(logErrorFileName);

			// Nombre del log donde guarda el historial de las solicitudes de los clientes
			if (logGeneralFileName.getCount() == 1)
				this->logGeneral->operator=("log.txt");
			else this->logGeneral->operator=(logGeneralFileName);

			// Nombre del servidor
			this->nombre->operator=(nombre);
		}
		// Si no, limpiamos los cambios
		else
			Servicio::ClearServicio();
	}
	// Si lo esta
	else listaEstados.add(EstadoServicio::AnteriormenteIniciado);

	return listaEstados;
}
#pragma endregion
