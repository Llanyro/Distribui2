#include "../Herramientas/List.h"
#include "String.h"

#include <iostream>
#include <signal.h>

using namespace std;

void sigClose3(int dummy)
{
	cout << endl << "Cerrando cliente..." << endl;
	//MsgClient::freeInstancia();
	exit(0);
}

int falseMain()
{
	//signal(SIGINT, sigClose);
	//ECHO_CLIENT;

	//List<EstadoCliente> resultado = ECHO_CLIENT->enviarSolicitud("192.168.0.103", 8080, "Hola desde el cliente");

	//for (size_t i = 0; i < resultado.getCount(); i++)
	//{
	//	switch (resultado[i])
	//	{
	//		case EstadoCliente::PeticionSolicitada:
	//			cout << "Peticion solicitada con exito" << endl;
	//			break;
	//		case EstadoCliente::ErrorSocketNoDisponible:
	//			cout << "Error Socket no disponible" << endl;
	//			break;
	//		case EstadoCliente::ErrorIpServer:
	//			cout << "Error Ip no valida" << endl;
	//			break;
	//		case EstadoCliente::ErrorConexionFallida:
	//			cout << "Error conexion fallida" << endl;
	//			break;
	//	}
	//}

	sigClose3(0);
	return 0;
}
