#include "httpserver.h"
#include <iostream>
#include <signal.h>

using namespace std;

httpServer* server = nullptr;

void sigClose(int dummy)
{
    server->closeServer();
    delete server;
    cout << endl << "Cerrando programa" << endl;
    exit(0);
}

int main()
{
    string path, ip, user, pass;
    unsigned short port = 8080;
    cout << "Introduce la carpeta del servidor https(Ej: /home/ubuntu/http_server): " << endl;
    cin >> path;
    cout << "Introduce la ip del servidor db" << endl;
    cin >> ip;
    cout << "Introduce el usuario de la db" << endl;
    cin >> user;
    cout << "Introduce la password del user de la db" << endl;
    cin >> pass;
    cout << "Introduce el puerto de escucha del servidor http" << endl;
    cin >> port;

    bool temp = false;
    server = new httpServer(port, path, ip, user, pass);
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
