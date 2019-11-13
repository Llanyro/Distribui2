#pragma once

template <class T>
class List;
class String;
struct sockaddr_in;

// Lista de estados al iniciar el servicio
enum class EstadoServicio
{
	Iniciado,
	AnteriormenteIniciado,
	
	
	// Errores
	ErrorSocketNoDisponible,
	ErrorOnBinding,
	ErrorNoEscuchando


};

/*
	Padre o plantilla de todos los servicios
	Al heredar se pueden modificar las funciones a gusto
	No se puede usar la clase directamente como un servicio:
	es decir, hay que heredarla de otra clase que sea un singleton
	Pd: Esta clase no se debe de modificar
	Pd: Los sockets no estan testeado en windows, solo en unix
*/
class Servicio
{
	protected:
		String* nombre;				// Nombre dado al servicio
		String* logError;			// Nombre del log error
		String* logGeneral;			// Nombre del log general
		sockaddr_in* direccionIP;	// Estructura de la direccion ip del servidor
		int socket_fd;				// Puerto de escucha (socket file descriptor)
		bool servicioIniciado;		// Si se ha iniciado el servicio
		const char option = 1;		// Suele estar seteado a 1
		#pragma region Protected
		Servicio();
		~Servicio();
		void ClearServicio();
		#pragma endregion
	public:
		#pragma region Public
		virtual void resolverSolicitud(const int& newsock_fd) const;
		virtual int escharSolicitudes() const;
		virtual List<EstadoServicio> iniciarServicio(
			const String& nombre,
			const String& logErrorFileName,
			const String& logGeneralFileName,
			const String& direccionIP,
			const unsigned short& puertoEscucha);
		#pragma endregion
};
