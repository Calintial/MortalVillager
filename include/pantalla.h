#ifndef PANTALLA_H
#define PANTALLA_H

#include "hud.h"
#include "mapa2D.h"

class mapa2D;

class Pantalla : public IEventReceiver
{
public:
		Pantalla(IrrlichtDevice * IrrDevice);
		~Pantalla();
		int pintarPantalla(IDibujable**,IDibujable**);
		virtual bool OnEvent(const SEvent& event);
private:
	IrrlichtDevice * pantallaDevice;
	hud * hudmapa;
	mapa2D * mapa;


};
#endif 