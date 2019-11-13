#include "ServicioEjecucion.h"
#include "ClienteEjecutacion.h"
#include "../../Herramientas/File.h"
#include "../../Herramientas/List.h"
#include "../../Herramientas/String.h"
#include <iostream>
#include <signal.h>

using namespace std;

void sigCloseEjecutador(int dummy)
{
	cout << endl << "Cerrando cliente..." << endl;
	ServicioEjecucion::freeInstancia();
	ClienteEjecutacion::freeInstancia();
	File::freeInstancia();
	exit(0);
}

int main()
{
	signal(SIGINT, sigCloseEjecutador);
	SERVICIOEJECUCION;

	List<EstadoServicio> resultado =
		SERVICIOEJECUCION->iniciarServicio("Servicio Ejecutador", "./logs/logErrorEjecutador.txt", "./logs/logEjecutador.txt", "127.0.0.1", PUERTOEJECUCION);
	bool continuar = false;
	
	for (size_t i = 0; i < resultado.getCount(); i++)
	{
		switch (resultado[i])
		{
			case EstadoServicio::Iniciado:
			case EstadoServicio::AnteriormenteIniciado:
				cout << "Ok, Servidor iniciado correctamente." << endl;
				continuar = true;
				break;
			case EstadoServicio::ErrorSocketNoDisponible:
				cout << "Error:  Socket no disponible." << endl;
				break;
			case EstadoServicio::ErrorOnBinding:
				cout << "Error on Binding." << endl;
				break;
			case EstadoServicio::ErrorNoEscuchando:
				cout << "Error no escuchando puerto." << endl;
				break;
		}
	}
	
	while (continuar)
	{
		int newfd = SERVICIOEJECUCION->escharSolicitudes();
		SERVICIOEJECUCION->resolverSolicitud(newfd);
	}

	sigCloseEjecutador(0);
	return 0;
}
