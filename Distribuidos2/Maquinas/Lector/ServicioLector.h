#pragma once
#include "../Plantillas/Servicio.h"
#include "../../Herramientas/Singleton.h"

#define SERVICIOLECTOR ServicioLector::getInstancia()
#define PUERTOLECTOR 8081

class ServicioLector : public Servicio, public Singleton <ServicioLector>
{
	protected:
		ServicioLector();
		~ServicioLector();
		friend class Singleton <ServicioLector>;
		// Devuelve true si el servicio esta iniciado
		bool comprobarServicio(const String& nombre, const unsigned short& puerto) const;
	public:
		virtual void resolverSolicitud(const int& newsock_fd) const override;
};
