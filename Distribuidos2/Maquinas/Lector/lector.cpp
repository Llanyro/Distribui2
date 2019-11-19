#pragma warning(disable:26451)
#include "ServicioLector.h"
#include "../../Herramientas/File.h"
#include "../../Herramientas/List.h"
#include "../../Herramientas/String.h"
#include <iostream>
#include <csignal>
#include <ctime>

#ifdef _WIN32
#define SIGUSR1 SIGABRT_COMPAT
#elif __unix__
#include <unistd.h>
#endif // _WIN32

#define SUMASEGUNDOS 30

using namespace std;

double maxTime = 0.0;
int pid = 0;

void sigCloseLector(int dummy)
{
	cout << endl << "Cerrando cliente..." << endl;
	ServicioLector::freeInstancia();
	File::freeInstancia();
	exit(0);
}
void sigClosePadre(int value)
{
	cout << endl << "Matando hijo lector y me suicido" << endl;
	#ifdef _WIN32

	#elif __unix__
	kill(pid, SIGINT);
	#endif // _WIN32
	exit(0);
}
void sigSum(int dummy)
{
	cout << "Mas " << SUMASEGUNDOS << " segundos al lector" << endl;
	maxTime = (clock() / (int)CLOCKS_PER_SEC) + SUMASEGUNDOS;
}
int main()
{
	#ifdef _WIN32

	#elif __unix__
	pid = fork();
	#endif // _WIN32
	if (pid == 0)
	{
		cout << "Hijo lector" << endl;
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
			#ifdef _WIN32

			#elif __unix__
			kill(getppid(), SIGUSR1);
			#endif
			SERVICIOLECTOR->resolverSolicitud(newfd);
		}
		#ifdef _WIN32

		#elif __unix__
		kill(getppid(), SIGINT);
		#endif
	}
	else
	{
		cout << "Padre lector" << endl;
		signal(SIGINT, sigClosePadre);
		signal(SIGUSR1, sigSum);

		int segundo = clock() / (int)CLOCKS_PER_SEC;
		maxTime = segundo + SUMASEGUNDOS;
		while (segundo <= maxTime)
			segundo = clock() / (int)CLOCKS_PER_SEC;
		sigClosePadre(0);
	}
	return 0;
}
