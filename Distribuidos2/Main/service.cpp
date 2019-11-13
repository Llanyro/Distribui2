#include "../Herramientas/List.h"
#include "String.h"

#include <iostream>
#include <signal.h>

using namespace std;

void sigClose2(int dummy)
{
	cout << endl << "Cerrando servicio..." << endl;
	//MsgService::freeInstancia();
	exit(0);
}

int main2()
{
	//signal(SIGINT, sigClose2);
	//ECHO_SERVICE;
	//
	//List<EstadoServicio> resultado = ECHO_SERVICE->iniciarServicio("ServicioEcho", "logErrorServ.txt", "logServ.txt", "localhost", 8080);
	//bool continuar = false;
	//
	//for (size_t i = 0; i < resultado.getCount(); i++)
	//{
	//	switch (resultado[i])
	//	{
	//		case EstadoServicio::Iniciado:
	//		case EstadoServicio::AnteriormenteIniciado:
	//			cout << "Ok, Servidor iniciado correctamente." << endl;
	//			continuar = true;
	//			break;
	//		case EstadoServicio::ErrorSocketNoDisponible:
	//			cout << "Error:  Socket no disponible." << endl;
	//			break;
	//		case EstadoServicio::ErrorOnBinding:
	//			cout << "Error on Binding." << endl;
	//			break;
	//		case EstadoServicio::ErrorNoEscuchando:
	//			cout << "Error no escuchando puerto." << endl;
	//			break;
	//	}
	//}
	//
	//while (continuar)
	//{
	//	int newfd = ECHO_SERVICE->escharSolicitudes();
	//	ECHO_SERVICE->resolverSolicitud(newfd);
	//}

	sigClose2(0);
	return 0;
}
