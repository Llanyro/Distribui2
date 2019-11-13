#pragma once
#include "../Plantillas/Servicio.h"
#include "../../Herramientas/Singleton.h"

#define SERVICIOEJECUCION ServicioEjecucion::getInstancia()
#define PUERTOLECTOR 8081
#define PUERTOSUMADOR 8082


class ServicioEjecucion : public Servicio, public Singleton <ServicioEjecucion>
{
	protected:
		ServicioEjecucion();
		~ServicioEjecucion();
		friend class Singleton <ServicioEjecucion>;
		// Devuelve true si el servicio esta iniciado
		bool comprobarServicio(const String& nombre, const unsigned short& puerto) const;
	public:
		virtual void resolverSolicitud(const int& newsock_fd) const override;
};
