#ifndef PANTALLA_PATHFINDING_H
#define PANTALLA_PATHFINDING_H

#include <irrlicht.h>
#include "pantalla.h"
#include "mapa2D.h"
#include "InterfazPathfinding.h"
#include "muro.h"


class mapa2D;
class PantallaPathfinding : public Pantalla
{
public:
		PantallaPathfinding(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine);
		~PantallaPathfinding();
		void pintarPantalla(vector<IDibujable*>*,vector<IDibujable*>*);
		virtual bool OnEvent(const SEvent& event);
private:
	IrrlichtDevice * pantallaDevice;
	mapa2D * mapa;
	InterfazPathfinding * interfazPathfinding;


};
#endif 