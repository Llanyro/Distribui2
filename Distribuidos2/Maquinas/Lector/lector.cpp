#include "ServicioLector.h"
#include "../../Herramientas/File.h"
#include "../../Herramientas/List.h"
#include "../../Herramientas/String.h"
#include <iostream>
#include <csignal>
#include <ctime>

using namespace std;

double maxTime = 0.0;

void sigCloseLector(int dummy)
{
	cout << endl << "Cerrando cliente..." << endl;
	ServicioLector::freeInstancia();
	File::freeInstancia();
	exit(0);
}

void sigClosePadre(int value)
{
	cout << "Yo no me muero" << endl;
}
void sigSum(int dummy)
{
	maxTime += 60;
}

int main()
{
	int pid = fork();
	if (pid != 0)
	{
		signal(SIGINT, sigClosePadre);
		signal(SIGUSR1, sigSum);

		double segundo = clock() / (double)CLOCKS_PER_SEC;
		maxTime = segundo + 60;
		while (segundo <= maxTime)
			sleep(1);
		kill(pid, SIGINT);
		sigClosePadre(0);
	}
	else
	{
		signal(SIGINT, sigCloseLector);
		SERVICIOLECTOR;
		List<EstadoServicio> resultado =
			SERVICIOLECTOR->iniciarServicio("Servicio Lector", "./logs/logErrorLector.txt", "./logs/logLector.txt", "127.0.0.1", PUERTOLECTOR);
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
			int newfd = SERVICIOLECTOR->escharSolicitudes();
			kill(getppid(), SIGUSR1);
			//Señal al padre + 60 seg
			SERVICIOLECTOR->resolverSolicitud(newfd);
		}
		sigCloseLector(0);
	}

	return 0;
}
