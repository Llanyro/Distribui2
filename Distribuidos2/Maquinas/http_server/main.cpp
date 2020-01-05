#include "httpserver.h"
#include <iostream>
#include <signal.h>
#include "../Puertos.h"

using namespace std;

httpServer* server = nullptr;

void sigClose(int dummy)
{
    delete server;
    cout << endl << "Cerrando programa" << endl;
    exit(0);
}

int main()
{
	string ip;
    cout << "Introduce la ip del servidor db" << endl;
    cin >> ip;

    bool temp = false;
    server = new httpServer(PUERTOHTTPSERVER, "/home/lubuntu/share/Distribuidos2/Maquinas/http_server", ip, "root", "Password1");
    signal(SIGINT, sigClose);

    if(server->isConectedToDataBase())
    {
        temp = true;
        cout << "Connected to DB" << endl;
    }
    else
        cout << "Not connected to DB" << endl << "El servidor se apagará, comprueba los valores de la DB y si esta esta encendida." << endl;

    while(temp)
    {
        int newfd = server->waitForConnections();
        server->resolveRequests(newfd);
    }
}
