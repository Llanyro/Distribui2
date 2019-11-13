#pragma once
#include "../Puertos.h"
#include "../Plantillas/Servicio.h"
#include "../../Herramientas/Singleton.h"

#define SERVICIOSUMADOR ServicioSumador::getInstancia()

class ServicioSumador : public Servicio, public Singleton <ServicioSumador>
{
	protected:
		ServicioSumador();
		~ServicioSumador();
		friend class Singleton <ServicioSumador>;
	public:
		virtual void resolverSolicitud(const int& newsock_fd) const override;
};
