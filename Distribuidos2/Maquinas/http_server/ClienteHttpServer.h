#pragma once
#include "../Plantillas/Cliente.h"
#include "../../Herramientas/Singleton.h"

#define CLIENTEHTTPSERVER ClienteHttpServer::getInstancia()

class ClienteHttpServer : public Cliente, public Singleton <ClienteHttpServer>
{
	protected:
		ClienteHttpServer();
		~ClienteHttpServer();
		friend class Singleton <ClienteHttpServer>;
};
