#include "ServicioSumador.h"
#include "../../Herramientas/File.h"
#include "../../Herramientas/List.h"
#include "../../Herramientas/String.h"
#include <iostream>
#include <csignal>
#include <ctime>

#ifdef _WIN32

#elif __unix__
#include <unistd.h>
#endif // _WIN32

#define SUMASEGUNDOS 30

using namespace std;

double maxTime = 0.0;
int pid = 0;

void sigCloseSumador(int dummy)
{
	cout << endl << "Cerrando cliente..." << endl;
	ServicioSumador::freeInstancia();
	File::freeInstancia();
	exit(0);
}
void sigClosePadre(int value)
{
	cout << "Mas " << SUMASEGUNDOS << " segundos" << endl;
	kill(pid, SIGINT);
	exit(0);
}
void sigSum(int dummy)
{
	cout << "Mas " << SUMASEGUNDOS << " segundos al sumador" << endl;
	maxTime = (clock() / (int)CLOCKS_PER_SEC) + SUMASEGUNDOS;
}
int main()
{
	pid = fork();
	if (pid != 0)
	{
		cout << "Padre sumador" << endl;
		signal(SIGINT, sigClosePadre);
		signal(SIGUSR1, sigSum);

		int segundo = clock() / (int)CLOCKS_PER_SEC;
		maxTime = segundo + SUMASEGUNDOS;
		while (segundo <= maxTime)
		{
			sleep(1);
			segundo = clock() / (int)CLOCKS_PER_SEC;
		}
		sigClosePadre(0);
	}
	else
	{
		cout << "Hijo sumador" << endl;
		signal(SIGINT, sigCloseSumador);
		SERVICIOSUMADOR;

		List<EstadoServicio> resultado =
			SERVICIOSUMADOR->iniciarServicio("Servicio Sumador", "./logs/logErrorSumador.txt", "./logs/logSumador.txt", "127.0.0.1", PUERTOSUMADOR);
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
			int newfd = SERVICIOSUMADOR->escharSolicitudes();
			kill(getppid(), SIGUSR1);
			SERVICIOSUMADOR->resolverSolicitud(newfd);
		}
		sigCloseSumador(0);
	}
	return 0;
}
