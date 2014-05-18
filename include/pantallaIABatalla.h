#ifndef PANTALLA_IABATALLA_H
#define PANTALLA_IABATALLA_H

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <irrlicht.h>
#include "pantalla.h"
#include "mapa2D.h"
#include "DebugMenu.h"

using namespace irr;
using namespace video;
using namespace std;
using namespace core;

class mapa2D;
class PantallaIABatalla : public Pantalla
{
public:

		PantallaIABatalla(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa, int tipo);
		~PantallaIABatalla();
		void pintarPantalla(vector<shared_ptr<IDibujable>>*,vector<shared_ptr<IDibujable>>*,vector<shared_ptr<IDibujable>>*);
		virtual bool OnEvent(const SEvent& event);
private:
	DebugMenu* debug;
};
#endif 
