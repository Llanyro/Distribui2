#include "ServicioSumador.h"
#include "../../Herramientas/File.h"
#include "../../Herramientas/List.h"
#include "../../Herramientas/String.h"
#include <iostream>
#include <signal.h>
#include <ctime>

using namespace std;

void sigCloseSumador(int dummy)
{
	cout << endl << "Cerrando cliente..." << endl;
	ServicioSumador::freeInstancia();
	File::freeInstancia();
	exit(0);
}

int main()
{
	signal(SIGINT, sigCloseSumador);
	SERVICIOSUMADOR;

	List<EstadoServicio> resultado =
		SERVICIOSUMADOR->iniciarServicio("Servicio Sumador", "./logs/logErrorSumador.txt", "./logs/logSumador.txt", "127.0.0.1", PUERTOSUMADOR);
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
		int newfd = SERVICIOSUMADOR->escharSolicitudes();
		SERVICIOSUMADOR->resolverSolicitud(newfd);
		segundo = clock() / (double)CLOCKS_PER_SEC;
	}

	sigCloseSumador(0);
	return 0;
}
