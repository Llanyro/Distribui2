#pragma once

template <class T>
class List;
class String;

// Lista de estados al intentar establecer conexion con un servidor
enum class EstadoCliente
{
	PeticionSolicitada,

	//Errores
	ErrorSocketNoDisponible,
	ErrorIpServer,
	ErrorConexionFallida

};

/*
	Padre o plantilla de todos los clientes
	Al heredar se pueden modificar las funciones a gusto
	No se puede usar la clase directamente como un cliente
	es decir, hay que heredarla de otra clase que sea un singleton<T>
	Pd: Esta clase no se debe de modificar
	Pd: Los sockets no estan testeado en windows, solo en unix
*/
class Cliente
{
	protected:
		String* nombre;				// Nombre dado al servicio
		String* logError;			// Nombre del log error
		String* logGeneral;			// Nombre del log general
		int sock;
		#pragma region Protected
		Cliente();
		~Cliente();
		void ClearCliente();
		#pragma endregion
	public:
		#pragma region Public
		virtual void iniciarCliente(
			const String& nombreCliente,
			const String& logErrorFileName,
			const String& logGeneralFileName);
		virtual List<EstadoCliente> enviarSolicitud(
			const String& ipServer,
			const unsigned short& puerto,
			const String& solicitud);
		virtual String leerRespuesta();
		#pragma endregion
};
