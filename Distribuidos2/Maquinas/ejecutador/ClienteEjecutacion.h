#pragma once
#include "../Plantillas/Cliente.h"
#include "../../Herramientas/Singleton.h"

#define CLIENTEEJECUCION ClienteEjecutacion::getInstancia()

class ClienteEjecutacion : public Cliente, public Singleton <ClienteEjecutacion>
{
	protected:
		ClienteEjecutacion();
		~ClienteEjecutacion();
		friend class Singleton <ClienteEjecutacion>;
};
