#ifndef PANTALLA_H
#define PANTALLA_H

#include "mapa2D.h"
#include "InterfazPathfinding.h"
#include "muro.h"
#include <irrlicht.h>

class mapa2D;
class PantallaPathfinding : public IEventReceiver
{
public:
		PantallaPathfinding(IrrlichtDevice * IrrDevice);
		~PantallaPathfinding();
		void pintarPantalla(vector<IDibujable*>*,vector<IDibujable*>*);
		virtual bool OnEvent(const SEvent& event);
private:
	IrrlichtDevice * pantallaDevice;
	mapa2D * mapa;
	InterfazPathfinding * interfazPathfinding;


};
#endif 