#pragma once
#include "../Plantillas/Cliente.h"
#include "../../Herramientas/Singleton.h"

#define CLIENTEEJECUCION ClienteEjecutador::getInstancia()

class ClienteEjecutador : public Cliente, public Singleton <ClienteEjecutador>
{
	protected:
		ClienteEjecutador();
		~ClienteEjecutador();
		friend class Singleton <ClienteEjecutador>;
	public:

};
