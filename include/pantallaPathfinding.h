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

		PantallaPathfinding(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa, int tipo);
		~PantallaPathfinding();
		void pintarPantalla(vector<shared_ptr<IDibujable>>*,vector<shared_ptr<IDibujable>>*,vector<shared_ptr<IDibujable>>*);
		virtual bool OnEvent(const SEvent& event);
private:
	InterfazPathfinding* interfazPathfinding;


};
#endif 
