#include "ServicioLector.h"
#include "../../Herramientas/File.h"
#include "../../Herramientas/List.h"
#include "../../Herramientas/String.h"
#include <iostream>
#include <signal.h>
#include <ctime>

using namespace std;

void sigCloseLector(int dummy)
{
	cout << endl << "Cerrando cliente..." << endl;
	ServicioLector::freeInstancia();
	File::freeInstancia();
	exit(0);
}

int main()
{
	signal(SIGINT, sigCloseLector);
	SERVICIOLECTOR;

	List<EstadoServicio> resultado =
		SERVICIOLECTOR->iniciarServicio("Servicio Lector", "./logs/logErrorLector.txt", "./logs/logLector.txt", "127.0.0.1", PUERTOLECTOR);
	bool continuar = false;
	double segundo = clock() / (double)CLOCKS_PER_SEC;
	double maxTime = segundo + 60;

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
	
	while (continuar && segundo <= maxTime)
	{
		int newfd = SERVICIOLECTOR->escharSolicitudes();
		SERVICIOLECTOR->resolverSolicitud(newfd);
		segundo = clock() / (double)CLOCKS_PER_SEC;
	}

	sigCloseLector(0);
	return 0;
}
