#pragma once
#include "../Puertos.h"
#include "../Plantillas/Servicio.h"
#include "../../Herramientas/Singleton.h"

#define SERVICIOEJECUCION ServicioEjecucion::getInstancia()

class ServicioEjecucion : public Servicio, public Singleton <ServicioEjecucion>
{
	protected:
		ServicioEjecucion();
		~ServicioEjecucion();
		friend class Singleton <ServicioEjecucion>;
	public:
		virtual void resolverSolicitud(const int& newsock_fd) const override;
};
