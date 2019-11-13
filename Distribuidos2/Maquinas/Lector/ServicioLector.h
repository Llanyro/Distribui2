#pragma once
#include "../Puertos.h"
#include "../Plantillas/Servicio.h"
#include "../../Herramientas/Singleton.h"

#define SERVICIOLECTOR ServicioLector::getInstancia()

class ServicioLector : public Servicio, public Singleton <ServicioLector>
{
	protected:
		ServicioLector();
		~ServicioLector();
		friend class Singleton <ServicioLector>;
	public:
		virtual void resolverSolicitud(const int& newsock_fd) const override;
};
